#ifndef Order_h
#define Order_h
#include "Product.h"
#include <iostream>

class Order
{
private:
    int orderId;
    int pcId;
    int quantity;
    int unitProfitRate;
    double unitPrice;
    double totalProfit;
    double unitCost;
    double totalCost;

public:
    Order(int oid = 0, int pid = 0, int qua = 0, int UPR = 0)
    {
        orderId = oid;
        pcId = pid;
        quantity = qua;
        unitProfitRate = UPR;
        unitCost = unitPrice = totalCost = totalProfit = 0;
    }
    void compute(const Product &product)
    {
        unitCost = product.calculatePCCost(CompIdCost);
        unitPrice = unitCost * (1 + unitProfitRate / 100.0);
        totalProfit = (unitPrice - unitCost) * quantity;
    }
    int getOrderId() const
    {
        return orderId;
    }
    int getPcId() const
    {
        return pcId;
    }
    int getQuantity() const
    {
        return quantity;
    }
    double getUnitPrice() const
    {
        return unitPrice;
    }
    double getTotalProfit() const
    {
        return totalProfit;
    }
    double getUnitCost() const
    {
        return unitCost;
    }
    double getTotalCost() const
    {
        return totalCost;
    }
    int getProfitRate() const
    {
        return unitProfitRate;
    }

    bool operator<(const Order &other) const
    {
        return totalProfit < other.totalProfit;
    }
    void printSummary() const
    {
        std::cout << "Order " << orderId << " | Pc Model: " << pcId << " | Qty: " << quantity << " | Profit rate: " << unitProfitRate << "%" << " | Total profit: $ " << totalProfit << std::endl;
    }
};

#endif