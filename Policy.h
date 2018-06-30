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

#include <cstdint>

class Policy {
public:
    using PolicyNo = std::uint32_t;
    // Class variable to generate a unique id for each policy instance.
    static PolicyNo policyNo;

    Policy(const double);

    ~Policy();

    double getFaceAmount() const;

    PolicyNo getUniqueId() const;

private:
    double m_faceAmount;
    PolicyNo m_uniquePolicyNo;
};

#endif /* POLICY_H_ */
