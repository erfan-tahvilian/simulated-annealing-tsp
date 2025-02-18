# Simulated Annealing for Travelling Salesman Problem - C++

## Overview

This project is an implementation of the **Simulated Annealing (SA) algorithm** for solving the **Travelling Salesman Problem (TSP)** using **C++**. The objective is to find an approximate solution to the TSP by simulating the annealing process, where a search is performed over possible paths while gradually lowering the temperature to optimize the solution.

## Features

- **Simulated Annealing Algorithm:** Uses SA to approximate the optimal solution for TSP.
- **Dynamic Parameter Adjustment:** Allows users to modify:
  - Initial Temperature
  - Minimum Temperature
  - Cooling Rate
  - Number of Iterations
- **Province Selection:** Users can manually select a starting province or choose a random one.
- **CSV Data Handling:** The program reads inter-province distances from a CSV file (`distances.csv`).
- **Path Cost Calculation:** Computes and displays:
  - The best-found path.
  - The associated costs for each step.
  - The total path cost.
- **Interactive CLI Menu:** User-friendly interface for configuring and running simulations.

## Capabilities

1. **Manually Select a Starting Province** - Users can pick a source province or opt for random selection.
2. **CSV File Handling** - Reads inter-province distances from `distances.csv`.
3. **Simulated Annealing Execution** - Runs the SA algorithm to find an optimized route.
4. **Modify Simulation Parameters** - Users can adjust temperature, iterations, and cooling rate.
5. **Path Visualization** - Displays results in a structured table.
6. **Performance Evaluation** - Computes and presents path costs.

## Installation

### Prerequisites

- **C++ Compiler** (e.g., g++, clang++)
- **Windows Operating System** (required due to Windows-specific libraries used)

### Build and Run

```sh
# Clone the repository
git clone https://github.com/erfan-tahvilian/simulated-annealing-tsp.git
cd simulated-annealing-tsp

# Compile the project
g++ -o sa-tsp.exe main.cpp -std=c++17

# Run the program
sa-tsp.exe
```

## Usage

1. **Select an option** from the main menu:
   - `[1] Solve New Travelling Salesman Problem With Simulated Annealing Algorithm` → Select a province and run SA.
   - `[2] Resolve Travelling Salesman Problem With Simulated Annealing Algorithm for "Selected Province"` → Re-run the algorithm for the last chosen province.
   - `[3] Change Initial Temperature` → Modify the starting temperature.
   - `[4] Change Minimum Temperature` → Set the stopping temperature.
   - `[5] Change Cooling Rate` → Adjust how quickly temperature decreases.
   - `[6] Change Number of Iterations` → Set the iteration count for SA.
   - `[7] Exit` → Close the application.
2. **If a new problem is being solved (Option 1), select a source province:**
   - Choose a province from the displayed table.
   - Or enter `R` to select a random province.
3. **View results:**
   - **Path Cost Table:** Displays step-by-step movement and cost accumulation.
   - **Final Path Cost:** Shows the computed total travel cost.

## License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for more details.

## Support & Donations

If you find this project useful and would like to support further development, you can donate via:

- **Tron (TRX) Address:** `TL8WyZLLGu8UraHAT8dCoeMsnzGpX2oAYn`
- **Binance Coin (BNB - BEP20) Address:** `0xeC4F61F21238685cC842bC236D86684e5fc2Bc57`
- **Bitcoin (BTC) Address:** `bc1q2y9m8y02fqgsr4c6533duwmqtmrhadc8k8mkt4`

Your support is greatly appreciated! 🚀