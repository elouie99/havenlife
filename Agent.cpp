/*
 * Agent.cpp
 *
 *  Created on: Jun 25, 2018
 *      Author: Eddie L
 */


#include "Agent.h"

int Agent::agentId = 1000;

Agent::Agent(const std::string& name, const float commRate)
	: m_commissionRate(commRate), m_agentName(name),
	  m_uniqueAgentId(++Agent::agentId) {
	
	std::cout << "Agent <" << std::left << name
		<< "> with commission rate " << commRate
		<< " added." << std::endl;
}

Agent::~Agent() = default;

Agent::Agent(Agent&& rhs) = default;
Agent& Agent::operator=(Agent&& rhs) = default;

void Agent::setCommissionRate(const float commRate) {
	m_commissionRate = commRate;
}

float Agent::getCommissionRate() const {
	return m_commissionRate;
}

int Agent::getUniqueId() const {
	return m_uniqueAgentId;
}

std::string Agent::getName() const {
	return m_agentName;
}
