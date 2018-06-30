/*
 * Policy.cpp
 *
 *  Created on: Jun 25, 2018
 *      Author: Eddie L
 */

#include "Policy.h"
#include <iostream>

Policy::PolicyNo Policy::policyNo = 8000;

Policy::Policy(const double value)
    : m_faceAmount(value), m_uniquePolicyNo(++Policy::policyNo) {
        std::cout << "Policy no. " << getUniqueId()
            << " with face value " << getFaceAmount()
            << " created." << std::endl;
}

Policy::~Policy() = default;

double Policy::getFaceAmount() const {
    return m_faceAmount;
}
Policy::PolicyNo Policy::getUniqueId() const {
    return m_uniquePolicyNo;
}
