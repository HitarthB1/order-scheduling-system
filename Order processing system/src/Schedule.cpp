/*
 * External help used for assignment:
 * - https://cplusplus.com/reference/iomanip/setprecision/
 * - https://www.w3schools.com/cpp/cpp_files.asp
 * - Section 1.1: PC cost calculation
 * - Section 1.2: Profit formulas (used example with Order 115 as reference)
 * - Section 1.3: Penalty calculation (3% of order value)
 * - Section 1.4: CPU discount rules ($18 per 500 units)
 * - Constant.h: All component costs and PC requirements
 * - https://cplusplus.com/forum/beginner/122574/ (for parsing)
 * - https://www.w3schools.com/cpp/cpp_ref_fstream.asp
 */



#include <iostream>
#include <fstream>
#include "../include/Schedule.h"
#include <sstream>
#include <array>
#include <iomanip>
using namespace std;

void Schedule::loadOrders(const std::string &filename)
{
    std::ifstream inFile(filename);
    if (!inFile)
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        if (line.empty())
            continue;
        if (!line.empty() && line.front() == '[')
            line.erase(0, 1);
        if (!line.empty() && line.back() == ']')
            line.pop_back();
        for (char &c : line)
            if (c == ',')
                c = ' ';
        std::stringstream ss(line);
        int oid, pid, qty, rate;
        if (!(ss >> oid >> pid >> qty >> rate))

        // Used Cplusplus parsing tutorial.
        {
            std::cerr << "failed to parse line: " << line << std::endl;
            continue;
        }
        Order newOrder(oid, pid, qty, rate);
        orders.push_back(newOrder);
    }
    inFile.close();
    TotalOrders = orders.size();
};

void Schedule::processOrders()
{
    AllCyclesUsed = 0;
    AcceptedOrders = 0;
    CancelledOrders = 0;
    TotalPenalty = 0;
    TotalProfit = 0;
    TotalAcceptedUnits = 0;
    acceptedOrders.clear();   
    cancelledOrders.clear();
    pcCount.fill(0);
    compCount.fill(0);

    for (int i = 0; i < orders.size(); i++) 
    {
        int pcId = orders[i].getPcId();
        int qty = orders[i].getQuantity();
        int requiredCycles = PCIdReqCyc[pcId] * qty;
        array<int, 4> comps = {PCIdReqComp[pcId][0], PCIdReqComp[pcId][1], PCIdReqComp[pcId][2], PCIdReqComp[pcId][3]};
        Product p(pcId, comps, PCIdReqCyc[pcId]);
        double pcCost = p.calculatePCCost(CompIdCost);
        double unitProfit = pcCost * orders[i].getProfitRate() / 100;
        double orderProfit = unitProfit * qty;

        if (AllCyclesUsed + requiredCycles <= AVAIL_PROD_CYCLES)
        {
            AllCyclesUsed += requiredCycles;
            AcceptedOrders++;
            TotalProfit += orderProfit;
            TotalAcceptedUnits += qty;
            
        acceptedOrders.push_back(orders[i]);  
        pcCount[pcId] += qty; 
        for (int j = 0; j < 4; j++) {
        compCount[comps[j]] += qty;
        }
         
    }
        else
        {
            CancelledOrders++;
            double orderValue = pcCost * qty;
            double penalty = orderValue * ORDER_CANCEL_PENALTY / 100.0;
            TotalPenalty += penalty;
            cancelledOrders.push_back(orders[i]);
        } 
        
    }
    
}

void Schedule::printSummary() const
{
    //Used Cplusplus tuturiol on setprecison to assist in this part and other parts in the assignment.
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total orders: " << TotalOrders << "\n"
              << "Accepted: " << AcceptedOrders << " | Cancelled: " << CancelledOrders << "\n"
              << "Total cycles used: " << AllCyclesUsed << " / " << AVAIL_PROD_CYCLES << "\n"
              << "Total profit (accepted orders): $" << TotalProfit << "\n"
              << "Total cancellation penalty: $" << TotalPenalty << "\n"
              << "Net (before the CPU discount): $" << (TotalProfit - TotalPenalty) << "\n";
    int Discount = TotalAcceptedUnits / 500;
    double totalDiscount = Discount * DISCOUNT_PER_500_UNITS;
    double netProfit = TotalProfit - TotalPenalty - totalDiscount;
    std::cout << "Total accepted units: " << TotalAcceptedUnits << "\n";
    std::cout << "Discount applied: $" << totalDiscount << "\n";
    std::cout << "Net profit after discounts: $" << netProfit<< "\n";
}

void Schedule::printFiles() const
{

    std::ofstream File1("Orders.txt");
    File1 << "\nSummary\n ";
    File1 << "Total Orders: " << TotalOrders << "\n";
    File1 << "Accepted: " << AcceptedOrders << " | Cancelled: " << CancelledOrders << "\n";
    File1 << "Total accepted units: " << TotalAcceptedUnits << "\n";
    File1 << "Discount applied: $" << (TotalAcceptedUnits / 500) * DISCOUNT_PER_500_UNITS << "\n";
    File1 << "Net profit after discounts: $" << TotalProfit - TotalPenalty - ((TotalAcceptedUnits / 500) * DISCOUNT_PER_500_UNITS) << "\n";
    File1 << "ALL ORDERS RECEIVED " << std::endl;
    File1 << "Total Orders: " << TotalOrders << std::endl
          << std::endl;
    for (int i = 0; i < orders.size(); i++)
    {
        File1 << "Order ID: " << std::setw(3) << orders[i].getOrderId()
              << " | PC ID: " << std::setw(2) << orders[i].getPcId()
              << " | Quantity: " << std::setw(2) << orders[i].getQuantity()
              << " | Profit Rate: " << orders[i].getProfitRate() << "%" << std::endl;
    }
    File1.close();
    std::ofstream File2("accepted_orders.txt");
    File2 << "Total Accepted Orders: " << AcceptedOrders << std::endl;
    for (int i = 0; i < acceptedOrders.size(); i++)
    {
        File2 << "Order ID: " << acceptedOrders[i].getOrderId() << ", PC ID: " << acceptedOrders[i].getPcId() << ", Quantity: " << acceptedOrders[i].getQuantity() << std::endl;
    }
    File2.close();
    std::ofstream File3("cancelled_orders.txt");
    File3 << "Total Cancelled Orders:  " << CancelledOrders << std::endl;
    for (int i = 0; i < cancelledOrders.size(); i++)
    {
        File3 << "Order ID: " << cancelledOrders[i].getOrderId() << ", PC ID: " << cancelledOrders[i].getPcId() << ", Quantity: " << cancelledOrders[i].getQuantity() << std::endl;
    }
    File3.close(); 
    std::ofstream File4("pc_production.txt");
    File4 << "Pc Production Count: " << std::endl;
    for (int i = 0; i < NUMBER_PC_MODELS; i++)
    {
        if (pcCount[i] > 0)
        {
            File4 << "PC ID " << i << ": " << pcCount[i] << " units" << std::endl;
        }
    }
    File4.close();
    std::ofstream File5("component_requirement.txt");
    File5 << "Component Requirements " << std::endl
          << std::endl;
    for (int i = 0; i < NUMBER_COMP; i++)
    {
        if (compCount[i] > 0)
        {
            File5 << "Component ID " << i << ": " << compCount[i] << " units" << std::endl;
        }
    }
    File5.close();
    std::ofstream File6("summary_report.txt");
    File6 << std::fixed << std::setprecision(2);
    File6 << "PRODUCTION SUMMARY " << std::endl
          << std::endl;
    File6 << "Total orders received: " << TotalOrders << std::endl;
    File6 << "Orders accepted: " << AcceptedOrders << std::endl;
    File6 << "Orders cancelled: " << CancelledOrders << std::endl;
    File6 << "Total cycles used: " << AllCyclesUsed << " / " << AVAIL_PROD_CYCLES << std::endl;
    File6 << std::fixed << std::setprecision(2);
    File6 << "Total profit (accepted): $" << TotalProfit << "\n";
    File6 << "Total penalty (cancelled): $" << TotalPenalty << std::endl;
    File6 << "Net profit (before discount): $" << (TotalProfit - TotalPenalty) << std::endl;
    File6.close();
}
