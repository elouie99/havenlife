/*
 * Policy.h
 *
 *  Created on: Jun 25, 2018
 *      Author: Eddie L
 *
 *  Represents an insurance policy with a given face value and commission schedule.
 *  Each policy is given a unique number upon generation.
 *  Each policy has a single selling agent and 0 or more super agents.
 */

#ifndef POLICY_H_
#define POLICY_H_

#include <memory>
#include <vector>
#include "CommissionPlan.h"
#include "Agent.h"

class Policy {
	// Class variable to generate a unique id for each policy instance.
	static int policyNo;

public:
	Policy(const double, const std::shared_ptr<CommissionPlan>&);
	
	~Policy();
	
	double getFaceAmount() const;
	
	int getUniqueId() const;
	
	void recordSellingAgent(const std::shared_ptr<Agent>&);
	
	void recordSuperAgent(const std::shared_ptr<Agent>&);

	// Calculate agent commissions for this policy. We assume there
	// are commission rates for each agent. If not, the corresponding
	// agents will have zero commissions for this policy.
	void calculateCommissions();

private:
	double m_faceAmount;
	std::shared_ptr<CommissionPlan> m_commPlan;
	int m_uniquePolicyNo;
	std::shared_ptr<Agent> m_sellingAgent;
	std::vector<std::shared_ptr<Agent>> m_superAgents;
};

#endif /* POLICY_H_ */
