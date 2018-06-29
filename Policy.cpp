/*
 * Policy.cpp
 *
 *  Created on: Jun 25, 2018
 *      Author: Eddie L
 */

#include "Policy.h"
#include <iostream>

int Policy::policyNo = 8000;

Policy::Policy(const double value, const std::shared_ptr<CommissionPlan>& cp)
	: m_faceAmount(value), m_commPlan(cp), m_uniquePolicyNo(++Policy::policyNo) {
		std::cout << "Policy no. " << getUniqueId()
			<< " with face value " << getFaceAmount()
			<< " created." << std::endl;
	}

Policy::~Policy() = default;

double Policy::getFaceAmount() const {
	return m_faceAmount;
}
int Policy::getUniqueId() const {
	return m_uniquePolicyNo;
}

void Policy::recordSellingAgent(const std::shared_ptr<Agent>& agent) {
	m_sellingAgent = agent;
}

void Policy::recordSuperAgent(const std::shared_ptr<Agent>& agent) {
	m_superAgents.push_back(agent);
}

void Policy::calculateCommissions() {
	std::cout << "Commissions for policy plan no: " << getUniqueId()
		<< "    Face value: " << getFaceAmount()
		<< std::endl;

	// Sanity check for valid commission rates.
	if ((*m_commPlan).size() == 0) {
		std::cout << "No commission rates recorded." << std::endl;
		return;
	}

	float totalCommissions = (*m_commPlan)[0] * m_sellingAgent->getCommissionRate() * m_faceAmount;
	std::cout << "Selling agent commission <" << m_sellingAgent->getName()
		<< "> : " << totalCommissions << std::endl;

	for (std::size_t i = 1; i < (*m_commPlan).size() || i <= m_superAgents.size(); ++i) {
		float rate = i < (*m_commPlan).size() ? (*m_commPlan)[i] : 0;
		totalCommissions = rate * m_superAgents[i-1]->getCommissionRate() * m_faceAmount;
		std::cout << "Super agent " << i << " commission <" << m_superAgents[i-1]->getName()
			<< "> : " << totalCommissions << std::endl;
	}
	std::cout << std::endl;
}
