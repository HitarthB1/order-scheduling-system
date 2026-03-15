# order-scheduling-system

This project is a C++ simulation of a manufacturing pipeline. It handles the logic of taking raw order data, calculating the feasibility of assembly based on resource constraints (Production Cycles), and generating a full financial and inventory report.

## How it Works

The system operates in a two-step process:

1.  **Data Generation:** Run `BundleGenerator.cpp` first. This simulates a market "burst" by generating a randomized list of PC orders with varying configurations and profit margins.
2.  **Order Processing:** Run `main.cpp`. The system loads the bundle, evaluates each order's cost/benefit, and checks if we have the "Cycles" (time/resources) to build it. 

## Key Technical Logic

-   **Dynamic Costing:** PC costs aren't hardcoded; they are calculated by summing component prices + labor (cycles) defined in `Constant.h`
-   **Business Rules:** The scheduler automatically applies a 3% penalty to cancelled orders and calculates bulk discounts for large component purchases
-   **Resource Management:** With a cap of 10,000 cycles, the system prioritizes orders to maximize net profit within operational limits

## Setup & Configuration
Note on File Paths: The project currently looks for files in `../src/`. If you are running this from a different directory, you will need to update the file path strings in `main.cpp` and `BundleGenerator.cpp` to avoid a "File Not Found" error.
Also once completed you may comment out main.cpp to run the bundle generator and vice versa.

## Important
Also update the file directory in line(s):
- Main.cpp -   s.loadOrders("../src/OrderBundle.txt"); (line 15)
- bundleGenerator.cpp -  ofstream file("../src/OrderBundle.txt"); (line 12)

## Output Reports
After execution, the program generates several detailed logs including:
- `summary_report.txt`: A high-level financial overview.
- `component_requirement.txt`: A "shopping list" for the warehouse based on accepted orders.
- `pc_production.txt`: A breakdown of which models were built.
