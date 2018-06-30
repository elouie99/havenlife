/*
 * CommissionPlan.h
 *
 *  Created on: Jun 25, 2018
 *  Author: Eddie L
 *
 *  Represents a commission plan with commission rates for a selling agent
 *  and 0 or more super agents.
 *  By convention the first rate, m_commissionPlanRates[0] is given to
 *  selling agent, and subsequent rates are given, in order, to the super
 *  agents.
 *  Commission rates are recorded in fractions, not percentage.
 */

#ifndef COMMISSIONPLAN_H_
#define COMMISSIONPLAN_H_

#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

class CommissionPlan {
public:
    using CommPlanId = std::uint32_t;
    // Class variable to generate a unique id for each commission plan instance.
    static CommPlanId planId;

    CommissionPlan(const std::string& name);

    CommissionPlan(const std::string& planName, std::initializer_list<float> rates);

    // Subscript operator to efficiently return the rate per agent.
    float operator[](std::size_t);

    // Return the number of commission rates specified in this plan.
    std::size_t size() const;

    ~CommissionPlan();

    // Add new commission rates to a plan.
    void addCommissions(std::initializer_list<float> rates);

    // Update commission rate for given agent.
    // Agent           Index
    // -----           -----
    // selling agent   0
    // super agent 1   1
    // super agent 2   2, etc.
    void updateCommission(std::size_t agentIndex, float rate);

    void listCommissionRates() const;

    std::string getPlanName() const;

    CommPlanId getUniqueId() const;

private:
    std::string m_planName;
    CommPlanId m_uniquePlanId;
    std::vector<float> m_commissionPlanRates;
};

#endif /* COMMISSIONPLAN_H_ */
