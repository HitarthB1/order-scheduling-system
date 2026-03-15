/*
 * External help used for assignment:
 * - https://cplusplus.com/reference/iomanip/setprecision/
 * - https://www.w3schools.com/cpp/cpp_files.asp
 * - Section 1.1: PC cost calculation
 * - Section 1.2: Profit formulas (used example with Order 115 as reference)
 * - Section 1.3: Penalty calculation (3% of order value)
 * - Section 1.4: CPU discount rules ($18 per 500 units)
 * - Constant.h: All component costs and PC requirements
 */


#ifndef Schedule_h
#define Schedule_h
#include "Constant.h"
#include <vector>
#include "Order.h"
#include <string>
#include <fstream>
#include <iostream>

class Schedule
{
private:
    std::vector<Order> orders;
    std::vector<Order> acceptedOrders;
    std::vector<Order> cancelledOrders;
    std::array<int, NUMBER_PC_MODELS> pcCount;
    std::array<int, NUMBER_COMP> compCount;
    int AllCyclesUsed = 0;
    int TotalOrders = 0;
    int AcceptedOrders = 0;
    int CancelledOrders = 0;
    double TotalProfit = 0.0;
    double TotalPenalty = 0.0;
    int TotalAcceptedUnits = 0;
    double totalDiscount;
    double netProfit;

public:
    Schedule() {};
    void loadOrders(const std::string &filename);
    void processOrders();
    void printSummary() const;
    void printFiles() const;
    int getOrderCount() const
    {
        return orders.size();
    }
};

#endif