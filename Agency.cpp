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
#include <memory>
#include <unordered_map>

struct Agency::Impl {
	std::unordered_map<int, std::shared_ptr<Agent>> m_agents;
	std::unordered_map<int, std::shared_ptr<CommissionPlan>> m_plans;
	std::vector<std::shared_ptr<Policy>> m_salesReceipts;
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

int Agency::addAgent(const std::string name, float commission) {
	auto agent = std::make_shared<Agent>(name, commission);
	auto res = pImpl->m_agents.insert({agent->getUniqueId(), agent});
	return res.first->second->getUniqueId();
}

std::shared_ptr<Agent> Agency::getAgent(const int agentId) {
	auto agent_iter = pImpl->m_agents.find(agentId);
	if (agent_iter != pImpl->m_agents.end())
		return agent_iter->second;
	return nullptr;
}

bool Agency::removeAgent(const int agentId) {
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

int Agency::addCommissionPlan(const std::string& planName, std::initializer_list<float> rates) {
	auto plan = std::make_shared<CommissionPlan>(planName, rates);
	auto res = pImpl->m_plans.insert({plan->getUniqueId(), plan});
	return res.first->second->getUniqueId();
}

void Agency::addNewCommissionRatesToPlan(const int planId, std::initializer_list<float> rates) {
	std::shared_ptr<CommissionPlan> commPlan = getCommissionPlan(planId);
	if (commPlan) {
		commPlan->addCommissions(rates);
		return;
	}

	std::cout << "Invalid commission plan id specified: " << planId << std::endl;
}

std::shared_ptr<CommissionPlan> Agency::getCommissionPlan(const int planId) {
	auto plan_iter = pImpl->m_plans.find(planId);
	if (plan_iter != pImpl->m_plans.end())
		return plan_iter->second;
	return nullptr;
}

void Agency::listCommissionPlans() const {
	std::for_each(std::begin(pImpl->m_plans), std::end(pImpl->m_plans), [](auto& keyValPair) {
		std::cout << "Commission Plan ID: " << keyValPair.second->getUniqueId()
			<< "    Name: " << keyValPair.second->getPlanName()
			<< std::endl;
		keyValPair.second->listCommissionRates();
	});
}

std::shared_ptr<Policy> Agency::createPolicy(const double faceValue, const int commPlanId) {
	std::shared_ptr<CommissionPlan> commPlan = getCommissionPlan(commPlanId);
	if (commPlan)
		return std::make_shared<Policy>(faceValue, commPlan);
	
	std::cout << "Invalid commission plan id specified: " << commPlanId << std::endl;
	return nullptr;
}

void Agency::recordSellingAgent(const std::shared_ptr<Policy>& policy, int agentId) {
	policy->recordSellingAgent(getAgent(agentId));
}

void Agency::recordSuperAgents(const std::shared_ptr<Policy>& policy, const std::initializer_list<int>& agentIds) {
	std::for_each(std::begin(agentIds), std::end(agentIds), [this, &policy](auto& agent) {
		policy->recordSuperAgent(this->getAgent(agent));
	});
}

void Agency::recordPolicySale(const std::shared_ptr<Policy>& policy) {
	pImpl->m_salesReceipts.emplace_back(policy);
}

void Agency::calculateCommissions() {
	for (auto &policy : pImpl->m_salesReceipts) {
		policy->calculateCommissions();
	}
}
