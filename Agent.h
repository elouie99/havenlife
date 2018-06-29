/*
 * Agent.h
 *
 *  Created on: Jun 25, 2018
 *      Author: Eddie L
 *
 *  Represents an insurance agent.
 *  Each agent is given a unique id when added to an agency.
 *  An agent is assigned a commission rate.
 */

#ifndef AGENT_H_
#define AGENT_H_

#include <iostream>
#include <memory>

class Agent {
	// Class variable to generate a unique id for each agent instance.
	static int agentId;
public:
	Agent(const std::string&, const float);

	~Agent();

	Agent(Agent&& rhs);
	Agent& operator=(Agent&& rhs);

	void setCommissionRate(const float);

	float getCommissionRate() const;

	int getUniqueId() const;

	std::string getName() const;

private:
	float m_commissionRate;
	std::string m_agentName;
	int m_uniqueAgentId;
};

#endif /* AGENT_H_ */
