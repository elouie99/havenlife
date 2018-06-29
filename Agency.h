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
	int addAgent(const std::string name, float commission);
	
	// Remove an agent from agency;
	bool removeAgent(const int agentId);
	
	std::shared_ptr<Agent> getAgent(const int agentId);
	
	// List all agents in the agency.
	void listAgents() const;
	
	// Add a commission plan to the agency.
	// The list of commission rates are ordered with first rate for selling agent,
	// second rate for first super agent, third rate for second super agent, etc.
	int addCommissionPlan(const std::string& planName, std::initializer_list<float> rates);
	
	// Add additional commission rates to an existing plan.
	void addNewCommissionRatesToPlan(const int planId, std::initializer_list<float> rates);

	// Return a commission plan given its unique plan id.
	std::shared_ptr<CommissionPlan> getCommissionPlan(const int planId);
	
	// List all the commission plans for agency. Each plan has a unique plan id
	// that is used to create an insurance policy.
	void listCommissionPlans() const;

	// Create an insurance policy with given face value and associated commission plan id.
	std::shared_ptr<Policy> createPolicy(const double faceValue, const int commPlanId);
	
	// Record the selling agent for the policy.
	void recordSellingAgent(const std::shared_ptr<Policy>& policy, int agentId);

	// Record the list of super agents for the policy.
	void recordSuperAgents(const std::shared_ptr<Policy>& policy, const std::initializer_list<int>& agentIds);

	// Record a policy sale at the agency.
	void recordPolicySale(const std::shared_ptr<Policy>& policy);

	// Calculate agent commissions for all policies sold at the agency.
	void calculateCommissions();

private:
	struct Impl;
	std::unique_ptr<Impl> pImpl;
};

#endif /* AGENCY_H_ */
