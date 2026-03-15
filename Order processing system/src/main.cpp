// Compiler/IDE: MinGW g++ 6.3.0 on Windows 10, edited in Visual Studio Code
#include <iostream>
#include "../include/Product.h"
#include "../include/Order.h"
#include "../include/Constant.h"
#include "../include/Schedule.h"


using namespace std;

int main()
{
    cout << "Assignment 2 - Product and Order test" << endl;
    Schedule s;
    s.loadOrders("../src/OrderBundle.txt");
    cout << "Loaded " << s.getOrderCount() << " orders. " << endl;

    s.processOrders();
    s.printSummary();
    s.printFiles();
    return 0;
};

