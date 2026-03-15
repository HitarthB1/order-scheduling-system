// Compiler/IDE: MinGW g++ 6.3.0 on Windows 10, edited in Visual Studio Code
#include <iostream>
#include "../include/Product.h"
#include "../include/Order.h"
#include "../include/Constant.h"
#include "../include/Schedule.h"
/*I hold a copy of this assignment that I can produce if the original is lost or damaged.
I hereby certify that no part of this assignment has been copied from any other student’s work or
from any other source except where due acknowledgement is made in the assignment. No part
of this assignment has been written/produced for me by another person except where such
collaboration has been authorised by the subject lecturer concerned.*/

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

