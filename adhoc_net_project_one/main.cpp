//
//  main.cpp
//  adhoc_net_project_one
//
//  Created by Karimul Hasan on 2023-10-22.
//
//  Uncomment the valid lines of codes to get result

#include "simulator.cpp"

int main() {
    
    // Problem 2
    //Simulator smu = Simulator();
    // Question 1
    //smu.queueSimulation();
    // Question 2
    //smu.queueSimulationP2Q2(12000, 1000000);
    
    // Problem 1
    RandomVarGenerator rvg = RandomVarGenerator(75.0);
    rvg.generateExponentialRVQ1();
    
    return 0;
}



