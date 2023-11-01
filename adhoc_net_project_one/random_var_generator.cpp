//
//  random_var_generator.cpp
//  adhoc_net_project_one
//
//  Created by Karimul Hasan on 2023-10-31.
//

#include "random_var_generator.hpp"

class RandomVarGenerator {
private:
    double lambda;
public:
    RandomVarGenerator(double l){
        lambda = l;
    }
    
    void generateExponentialRVQ1(){
        const int numSamples = 1000;
        std::vector<double> samples;
        
        // Seed for random number generation
        std::srand(static_cast<unsigned>(std::time(0)));
        
        for (int i = 0; i < numSamples; ++i) {
            // Generate a random number U from U(0,1)
            double U = static_cast<double>(rand()) / RAND_MAX;
            double x = 0;
            // Generate exponential random variable using inverse transform method
            x = -(1/lambda) * log(1 - U);
            
            // Store the generated sample
            samples.push_back(x);
            
            // Output the generated sample
            std::cout << "Sample " << i + 1 << ": " << x << std::endl;
            
        }
        
        // Calculate mean
        double sum = 0;
        for (double sample : samples) {
            sum += sample;
        }
        double mean = sum / numSamples;
        
        // Calculate variance
        double variance = 0;
        for (double sample : samples) {
            variance = pow(sample - mean, 2);
        }
        variance /= numSamples;
        
        // Output mean and variance
        std::cout << "Mean: " << mean << std::endl;
        std::cout << "Variance: " << variance << std::endl;
        
    }
    
    double generateExponentialRVQ2(double lambdaQ2){
        // Seed for random number generation
        std::srand(static_cast<unsigned>(std::time(0)));
        // Generate a random number U from U(0,1)
        double U = static_cast<double>(rand()) / RAND_MAX;
        double x = 0;
        // Generate exponential random variable using inverse transform method
        x = -(1/lambdaQ2) * log(1 - U);
        return x;
    }
};

