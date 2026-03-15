#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "../include/Constant.h"
using namespace std;

int main()
{
    srand(time(0));

    ofstream file("../src/OrderBundle.txt");
    
    if (!file)
    {
        cout << "Error opening file" << endl;
        return 1;
    }
    int numOrders = ORDER_BUNDLE_QUANT_MIN + rand() % (ORDER_BUNDLE_QUANT_MAX - ORDER_BUNDLE_QUANT_MIN + 1);
    file << "Generated " << numOrders << " orders\n";
    int id = 100;
    for (int i = 0; i < numOrders; i++)
    {
        int pc = rand() % NUMBER_PC_MODELS;
        int q = ORDER_QUANT_MIN + rand() % (ORDER_QUANT_MAX - ORDER_QUANT_MIN + 1);
        int r = UNIT_PROFIT_RATE_MIN + rand() % (UNIT_PROFIT_RATE_MAX - UNIT_PROFIT_RATE_MIN + 1);

        file << "[" << id << ", " << pc << ", " << q << ", " << r << "]\n";
        id++;
    }

    file.close();
    cout << "Created " << numOrders << " orders" << endl;

    return 0;
}