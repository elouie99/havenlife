/*
 * CommissionPlan.cpp
 *
 *  Created on: Jun 25, 2018
 *      Author: Eddie L
 */

#include "CommissionPlan.h"
#include <iostream>

CommissionPlan::CommPlanId CommissionPlan::planId = 5000;

CommissionPlan::CommissionPlan(const std::string& name)
    : m_planName(name), m_uniquePlanId(++CommissionPlan::planId) {}

CommissionPlan::CommissionPlan(const std::string& name, std::initializer_list<float> rates)
    : m_planName(name), m_uniquePlanId(++CommissionPlan::planId) {
    for (auto rate : rates) {
        m_commissionPlanRates.push_back(rate);
    }
}

CommissionPlan::~CommissionPlan() = default;

float CommissionPlan::operator[](std::size_t index) {
    return m_commissionPlanRates[index];
}

std::size_t CommissionPlan::size() const {
    return m_commissionPlanRates.size();
}

void CommissionPlan::addCommissions(std::initializer_list<float> rates) {
    for (auto rate : rates) {
        m_commissionPlanRates.push_back(rate);
    }
}

void CommissionPlan::updateCommission(std::size_t agentIndex, float rate) {
    if (agentIndex <= m_commissionPlanRates.size()) {
        m_commissionPlanRates[agentIndex] = rate;
        return;
    }

    std::cout << "Invalid agent index to update: " << agentIndex << std::endl;
}

void CommissionPlan::listCommissionRates() const {
    // Sanity check for valid commission rates.
    if (m_commissionPlanRates.size() == 0) {
        std::cout << "No commission rates recorded." << std::endl;
        return;
    }

    std::cout << "Selling agent rate: " << m_commissionPlanRates[0] << std::endl;
    for (std::size_t i = 1; i < m_commissionPlanRates.size(); ++i) {
        std::cout << "Super agent "<< i << " rate: " << m_commissionPlanRates[i]
            << std::endl;
    }
}

std::string CommissionPlan::getPlanName() const {
    return m_planName;
}

CommissionPlan::CommPlanId CommissionPlan::getUniqueId() const {
    return m_uniquePlanId;
}
