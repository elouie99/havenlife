/*
 * Agency.h
 *
 *  Created on: Jun 25, 2018
 *      Author: Eddie L
 *
 *  Represents an insurance agency.
 *  Each agency can add a list of insurance agents.
 *  Each agency can create one or more commission plans.
 *  Each agency stores a list of policies sold.
 */

#ifndef AGENCY_H_
#define AGENCY_H_

#include "Agent.h"
#include "CommissionPlan.h"
#include "Policy.h"
#include <memory>

// Agency interface
//class IAgency {
//public:
//  IAgency() {}
//  virtual ~IAgency() {}
//  virtual Agent::AgentId addAgent(const std::string name, float commission) = 0;
//  virtual bool removeAgent(const Agent::AgentId) = 0;
//  virtual void listAgents() const = 0;
//  virtual CommissionPlan::CommPlanId addCommissionPlan(const std::string&, std::initializer_list<float>) = 0;
//  virtual void addNewCommissionRatesToPlan(const CommissionPlan::CommPlanId, std::initializer_list<float>) = 0;
//  virtual void listCommissionPlans() const = 0;
//  virtual Policy::PolicyNo createPolicy(const double, const CommissionPlan::CommPlanId) = 0;
//  virtual void recordSellingAgent(const Policy::PolicyNo, const Agent::AgentId) = 0;
//  virtual void recordSuperAgents(const Policy::PolicyNo, const std::initializer_list<Agent::AgentId>&) = 0;
//  virtual void recordPolicySale(const Policy::PolicyNo) = 0;
//  virtual void calculateCommissions() = 0;
//};

class Agency {
public:
    // Default constructor
    Agency();

    // Default destructor
    ~Agency();

    // Move constructor
    Agency(Agency&& rhs);

    // Move operator=
    Agency& operator=(Agency&& rhs);

    // Copy constructor
    Agency(const Agency& rhs);

    // Copy operator=
    Agency& operator=(const Agency& rhs);

    // Add an agent to agency.
    Agent::AgentId addAgent(const std::string name, float commission);

    // Remove an agent from agency;
    bool removeAgent(const Agent::AgentId agentId);

    // List all agents in the agency.
    void listAgents() const;

    // Add a commission plan to the agency.
    // The list of commission rates are ordered with first rate for selling agent,
    // second rate for first super agent, third rate for second super agent, etc.
    CommissionPlan::CommPlanId addCommissionPlan(const std::string& planName, std::initializer_list<float> rates);

    // Add additional commission rates to an existing plan.
    void addNewCommissionRatesToPlan(const CommissionPlan::CommPlanId planId, std::initializer_list<float> rates);

    // List all the commission plans for agency. Each plan has a unique plan id
    // that is used to create an insurance policy.
    void listCommissionPlans() const;

    // Create an insurance policy with given face value and associated commission plan id.
    Policy::PolicyNo createPolicy(const double faceValue, const CommissionPlan::CommPlanId commPlanId);

    // Record the selling agent for the policy.
    void recordSellingAgent(const Policy::PolicyNo policy, const Agent::AgentId agentId);

    // Record the list of super agents for the policy.
    void recordSuperAgents(const Policy::PolicyNo policy, const std::initializer_list<Agent::AgentId>& agentIds);

    // Record a policy sale at the agency.
    void recordPolicySale(const Policy::PolicyNo policy);

    // Calculate agent commissions for all policies sold at the agency.
    // We assume there are commission rates for each agent. If not, the
    //corresponding agents will have zero commissions for this policy.
    void calculateCommissions();

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};

#endif /* AGENCY_H_ */
