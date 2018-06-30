/*
 * Agency.cpp
 *
 *  Created on: Jun 25, 2018
 *      Author: Eddie L
 */

#include "Agency.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <unordered_map>

struct Agency::Impl {
    // Store of all agents working at agency.
    std::unordered_map<Agent::AgentId, std::shared_ptr<Agent>> m_agents;

    // Store of all commission plans created at agency.
    std::unordered_map<CommissionPlan::CommPlanId, std::shared_ptr<CommissionPlan>> m_plans;

    // Store of all policies written at agency.
    std::unordered_map<Policy::PolicyNo, std::shared_ptr<Policy>> m_policies;

    // Record of all  policies sold.
    std::vector<Policy::PolicyNo> m_salesReceipts;

    // Record of all agents who sold given policy. First agent is always selling agent.
    std::unordered_map<Policy::PolicyNo, std::vector<Agent::AgentId>> m_policyAgents;

    // Record of commission plan associated with given policy.
    std::unordered_map<Policy::PolicyNo, CommissionPlan::CommPlanId> m_policyCommissionPlan;

    std::shared_ptr<Agent> getAgent(const Agent::AgentId agentId);

    // Return true if agent is part of agency, otherwise falsel
    bool validateAgent(const Agent::AgentId agentId);

    // Return a commission plan given its unique plan id.
    std::shared_ptr<CommissionPlan> getCommissionPlan(const CommissionPlan::CommPlanId planId);

    // Return true if commission plan is valid, otherwise false;
    bool validateCommissionPlan(const CommissionPlan::CommPlanId planId);

    // Return insurance policy object given policy no.
    std::shared_ptr<Policy> getPolicy(const Policy::PolicyNo policyNo);

    // Return true if policy no is valid, otherwise false.
    bool validatePolicy(const Policy::PolicyNo policyNo);
};

Agency::Agency() : pImpl(std::make_unique<Agency::Impl>()) {}

Agency::~Agency() = default;

Agency::Agency(Agency&& rhs) = default;

Agency& Agency::operator=(Agency&& rhs) = default;

Agency::Agency(const Agency& rhs)
    : pImpl(std::make_unique<Impl>(*rhs.pImpl)) {}

Agency& Agency::operator=(const Agency& rhs) {
    *pImpl = *rhs.pImpl;
    return *this;
}

// Public member implementation

Agent::AgentId Agency::addAgent(const std::string name, float commission) {
    auto agent = std::make_shared<Agent>(name, commission);
    auto res = pImpl->m_agents.insert({agent->getUniqueId(), agent});
    return res.first->second->getUniqueId();
}

bool Agency::removeAgent(const Agent::AgentId agentId) {
    return pImpl->m_agents.erase(agentId) != 0;
}

void Agency::listAgents() const {
    std::for_each(std::begin(pImpl->m_agents), std::end(pImpl->m_agents), [](auto& keyValPair) {
        std::cout << "Agent ID: " << keyValPair.second->getUniqueId()
            << "  Name: " << keyValPair.second->getName()
            << "  Commission: " << keyValPair.second->getCommissionRate()
            << std::endl;
    });
}

CommissionPlan::CommPlanId Agency::addCommissionPlan(const std::string& planName, std::initializer_list<float> rates) {
    auto plan = std::make_shared<CommissionPlan>(planName, rates);
    auto res = pImpl->m_plans.insert({plan->getUniqueId(), plan});
    return res.first->second->getUniqueId();
}

void Agency::addNewCommissionRatesToPlan(const CommissionPlan::CommPlanId planId, std::initializer_list<float> rates) {
    std::shared_ptr<CommissionPlan> commPlan = pImpl->getCommissionPlan(planId);
    if (commPlan) {
        commPlan->addCommissions(rates);
        return;
    }

    std::cout << "Invalid commission plan id specified: " << planId << std::endl;
}

void Agency::listCommissionPlans() const {
    std::for_each(std::begin(pImpl->m_plans), std::end(pImpl->m_plans), [](auto& keyValPair) {
        std::cout << "Commission Plan ID: " << keyValPair.second->getUniqueId()
            << "    Name: " << keyValPair.second->getPlanName()
            << std::endl;
        keyValPair.second->listCommissionRates();
    });
}

Policy::PolicyNo Agency::createPolicy(const double faceValue, const CommissionPlan::CommPlanId commPlanId) {
    if (pImpl->validateCommissionPlan(commPlanId)) {
        auto policy = std::make_shared<Policy>(faceValue);
        pImpl->m_policies.insert({policy->getUniqueId(), policy});
        pImpl->m_policyCommissionPlan.insert({policy->getUniqueId(), commPlanId});
        return policy->getUniqueId();
    }

    std::cout << "Invalid commission plan id specified: " << commPlanId << std::endl;
    return 0;
}

void Agency::recordSellingAgent(const Policy::PolicyNo policy, Agent::AgentId agentId) {
    if (!pImpl->validatePolicy(policy)) {
        std::cout << "Invalid policy provided." << std::endl;
        return;
    }
    if (!pImpl->validateAgent(agentId)) {
        std::cout << "Invalid selling agent provided." << std::endl;
        return;
    }
    pImpl->m_policyAgents[policy].push_back(agentId);
}

void Agency::recordSuperAgents(const Policy::PolicyNo policy, const std::initializer_list<Agent::AgentId>& agentIds) {
    if (!pImpl->validatePolicy(policy)) {
        std::cout << "Invalid policy provided." << std::endl;
        return;
    }
    if (pImpl->m_policyAgents.find(policy) == pImpl->m_policyAgents.end()) {
        std::cout << "No selling agent recorded. Please add a selling agent first." << std::endl;
        return;
    }
    std::for_each(std::begin(agentIds), std::end(agentIds), [this, &policy](auto& agent) {
        if (!pImpl->validateAgent(agent)) {
            std::cout << "Super agent with id <" << agent << "> is invalid. Skipping." << std::endl;
        }
        pImpl->m_policyAgents[policy].push_back((agent));
    });
}

void Agency::recordPolicySale(const Policy::PolicyNo policy) {
    pImpl->m_salesReceipts.push_back(policy);
    std::cout << "Policy no " << policy << " sale recorded." << std::endl;
}

void Agency::calculateCommissions() {
    for (auto &policyNo : pImpl->m_salesReceipts) {
        auto policy = pImpl->getPolicy(policyNo);
        auto commPlan = pImpl->getCommissionPlan(pImpl->m_policyCommissionPlan[policyNo]);

        std::cout << "Commissions for policy plan no: " << policyNo
            << "    Face value: " << policy->getFaceAmount()
            << std::endl;

        // Sanity check for valid commission rates.
        if (commPlan->size() == 0) {
            std::cout << "No commission rates recorded." << std::endl;
            return;
        }

        for (std::size_t i = 0; i < commPlan->size() || i < pImpl->m_policyAgents[policyNo].size(); ++i) {
            if (i < pImpl->m_policyAgents[policyNo].size()) {
                auto agent = pImpl->getAgent(pImpl->m_policyAgents[policyNo][i]);
                float rate = i < commPlan->size() ? (*commPlan)[i] : 0;
                float totalCommissions = rate * agent->getCommissionRate() * policy->getFaceAmount();
                if (i == 0) {
                    std::cout << "Selling agent commission <" << agent->getName()
                                    << "> : " << totalCommissions << std::endl;
                } else {
                    std::cout << "Super agent " << i << " commission <" << agent->getName()
                                    << "> : " << totalCommissions << std::endl;
                }
            }
        }
        std::cout << std::endl;
    }
}

// Private member implementation

std::shared_ptr<Agent> Agency::Impl::getAgent(const Agent::AgentId agentId) {
    auto agent_iter = Agency::Impl::m_agents.find(agentId);
    if (agent_iter != Agency::Impl::m_agents.end())
        return agent_iter->second;
    return nullptr;
}

bool Agency::Impl::validateAgent(const Agent::AgentId agentId) {
    return Agency::Impl::m_agents.find(agentId) != Agency::Impl::m_agents.end();
}

std::shared_ptr<CommissionPlan> Agency::Impl::getCommissionPlan(const CommissionPlan::CommPlanId planId) {
    auto plan_iter = Agency::Impl::m_plans.find(planId);
    if (plan_iter != Agency::Impl::m_plans.end())
        return plan_iter->second;
    return nullptr;
}

bool Agency::Impl::validateCommissionPlan(const CommissionPlan::CommPlanId planId) {
    return Agency::Impl::m_plans.find(planId) != Agency::Impl::m_plans.end();
}

std::shared_ptr<Policy> Agency::Impl::getPolicy(const Policy::PolicyNo policyNo) {
    auto agent_iter = Agency::Impl::m_policies.find(policyNo);
    if (agent_iter != Agency::Impl::m_policies.end())
        return agent_iter->second;
    return nullptr;
}

bool Agency::Impl::validatePolicy(const Policy::PolicyNo policyNo) {
    return Agency::Impl::m_policies.find(policyNo) != Agency::Impl::m_policies.end();
}
