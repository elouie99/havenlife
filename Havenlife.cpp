/*
 * Havenlife.cpp
 *
 *  Created on: Jun 25, 2018
 *      Author: Eddie L
 */

#include "Agency.h"

int main() {

	// Set up an agency
	std::unique_ptr<Agency> agency = std::make_unique<Agency>();

	// Add two commission plans
	auto commPlanA = agency->addCommissionPlan("Plan A", {0.50, 0.05, 0.0, 0.0});
	auto commPlanB = agency->addCommissionPlan("Plan B", {0.70, 0.08, 0.04, 0.0});
	auto commPlanC = agency->addCommissionPlan("Plan C", {0.4, 0.08, 0.02, 0.015});

	std::cout << std::endl;
	// List commission plans added
	agency->listCommissionPlans();

	std::cout << std::endl;
	// Add agents to agency
	auto agentBob = agency->addAgent("Bob", 0.02);
	auto agentJanet = agency->addAgent("Janet", 0.025);
	auto agentPeter = agency->addAgent("Peter", 0.0325);
	auto agentFiona = agency->addAgent("Fiona", 0.0225);
	auto agentLisa = agency->addAgent("Lisa", 0.045);
	auto agentTony = agency->addAgent("Tony", 0.05);

	std::cout << std::endl;
	// List agents added
	agency->listAgents();

	std::cout << std::endl;
	// Originate policies for sale
	auto policy1 = agency->createPolicy(100000, commPlanA);
	auto policy2 = agency->createPolicy(100000, commPlanB);
	auto policy3 = agency->createPolicy(250000, commPlanC);

	// Record selling agents
	agency->recordSellingAgent(policy1, agentBob);
	agency->recordSuperAgents(policy1, {agentJanet, agentPeter, agentFiona});

	agency->recordSellingAgent(policy2, agentBob);
	agency->recordSuperAgents(policy2, {agentJanet, agentPeter, agentFiona});

	agency->recordSellingAgent(policy3, agentLisa);
	agency->recordSuperAgents(policy3, {agentTony, agentBob, agentJanet, agentFiona, agentPeter});

	// Record sale of policy
	agency->recordPolicySale(policy1);
	agency->recordPolicySale(policy2);
	agency->recordPolicySale(policy3);

	std::cout << std::endl;
	// Calculate agent commissions for each policy sold.
	agency->calculateCommissions();

	std::cout << "Complete!" << std::endl;
	return 0;
}


