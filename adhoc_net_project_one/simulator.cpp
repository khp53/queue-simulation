//
//  simulator.cpp
//  adhoc_net_project_one
//
//  Created by Karimul Hasan on 2023-10-31.
//

#include "simulator.hpp"
#include "random_var_generator.cpp"

class Simulator {
private:
    double lambda = 0; // Arrival rate (packets per second)
    const double L = 12000.0;    // L1ength of a packet in bits
    const double C = 1000000.0; // Transmission rate
    double rho = 0.25; // rho for calculating lambda
public:
    void queueSimulation() {
        RandomVarGenerator rvg = RandomVarGenerator(lambda); // just for initializing class
        
        double T = 10000.0; // Simulation time in seconds
        int Na = 0; // Number of packet arrivals
        int Nd = 0; // Number of packet departures
        int No = 0; // Number of observations
        double totalTimeInQueue = 0.0; // Total time packets spend in the queue
        double totalIdleTime = 0.0; // Total idle time of the server
        double totalLossCount = 0.0; // Total number of packet losses
        
        double simulationTime = 0.0; // Current simulation time
        double observerEventTime = rvg.generateExponentialRVQ2(3 * ((rho * C) / L)); // First observer event time
        double totalQueueLength = 0.0; // Total quqe length
        // calculate lambda based on rho, L and C
        lambda = (rho * C) / L;
        
        // Simulation loop
        while (simulationTime < T) {
            // Generate packet arrival event
            double initialArrivalTime = rvg.generateExponentialRVQ2(lambda);
            simulationTime += initialArrivalTime;
            // Record arrival event
            Na++;
            double serviceTime = L / C;
            // Calculate departure time based on queue state
            double departureTime = simulationTime; // Initialize departure time as arrival time
            if (totalQueueLength > 0) {
                // Queue has packets, so departure time is the previous departure time + transmission time
                departureTime = departureTime + serviceTime;
            }
            
            // Record departure event
            Nd++;
            
            // Update total queue length and total time in queue
            totalQueueLength++;
            totalTimeInQueue += serviceTime;
            
            // Generate observer events
            while (simulationTime >= No * (1.0 / (3*lambda))) {
                No++;
                // Calculate performance metrics at observer events
                double averageQueueLength = totalTimeInQueue / simulationTime;
                double serverUtilization = totalTimeInQueue / (simulationTime - totalIdleTime);
                double packetLossProbability = totalLossCount / Na;
                
                // Output performance metrics at observer events
                std::cout << "Observer Event: " << No << " == ";
                std::cout << "Average Queue Length: " << averageQueueLength << ", ";
                std::cout << "Server Utilization: " << serverUtilization << ", ";
                std::cout << "Packet Loss Probability: " << packetLossProbability << std::endl;
                // Calculate observer even time
                observerEventTime += rvg.generateExponentialRVQ2(3 * lambda);
            }
            
            std::cout << "arrival time" << "-----" << "departure time" << "-----" << "observer time" << std::endl;
            std::cout << simulationTime << "-----" << departureTime << "-----" <<
            observerEventTime<<std::endl;
            std::cout << "" << std::endl;
            
            // Update total idle time if the server is idle
            if (departureTime > simulationTime) {
                totalIdleTime += (departureTime - simulationTime);
            }
            // Calculate average number of packets in the queue (E[N]) and PIDLE
            double En = simulationTime / T;
            double pidle = totalIdleTime / (T * (departureTime - simulationTime));
            std::cout << "Average number of packets in queue: " << En << ", ";
            std::cout << "The proportion of time the server is idle: " << pidle << std::endl;
            std::cout << "" << std::endl;
            
            // Update simulation time for the next event
            simulationTime = departureTime;
        }
    }
    
    void queueSimulationP2Q2(double l, double c) {
        RandomVarGenerator rvg = RandomVarGenerator(lambda); // just for initializing class
        
        // Simulation parameters
        double T = 10000.0; // Simulation time in seconds
        int Na = 0; // Number of packet arrivals
        int Nd = 0; // Number of packet departures
        int No = 0; // Number of observations
        double totalTimeInQueue = 0.0; // Total time packets spend in the queue
        double totalIdleTime = 0.0; // Total idle time of the server
        double totalLossCount = 0.0; // Total number of packet losses
        
        double simulationTime = 0.0; // Current simulation time
        double totalQueueLength = 0.0;
        
        for (rho = 0.25; rho <= 0.95; rho += 0.1) {
            // Calculate lambda based on phro, C and L
            lambda = (rho * c) / l;
            double observerEventTime = rvg.generateExponentialRVQ2(3 * ((rho * C) / L)); // First observer event time
            // ----------------------
            // Simulation loop
            while (simulationTime < T) {
                // Generate packet arrival event
                double initialArrivalTime = rvg.generateExponentialRVQ2(lambda);
                simulationTime += initialArrivalTime;
                Na++;
                double serviceTime = L / C;
                // Generate packet departure event
                // Calculate departure time based on queue state
                double departureTime = simulationTime; // Initialize departure time as arrival time
                if (totalQueueLength > 0) {
                    // Queue has packets, so departure time is the previous departure time + transmission time
                    departureTime = departureTime + serviceTime;
                }
                
                // Record departure event
                Nd++;
                
                // Update total queue length
                totalQueueLength++;
                totalTimeInQueue += serviceTime;
                
                // Update total idle time if the server is idle
                if (departureTime > simulationTime) {
                    totalIdleTime += (departureTime - simulationTime);
                }
                // Calculate average number of packets in the queue (E[N]) and PIDLE
                double En = simulationTime / T;
                double pidle = totalIdleTime / (T * (departureTime - simulationTime));
                std::cout << "Average number of packets in queue: " << En << ", ";
                std::cout << "The proportion of time the server is idle: " << pidle << std::endl;
                std::cout << "" << std::endl;
                
                // Update simulation time for the next event
                simulationTime = departureTime;
            }
        }
    }
};
