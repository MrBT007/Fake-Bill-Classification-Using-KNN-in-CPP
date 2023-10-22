#include <vector>
#include <limits>
#include <cmath>
#include <sstream>  // For ostringstream
#include <cstdlib>  // For system()
#include "bill.h"


extern double calculate_accuracy(const std::vector<Bill> &train_data, const std::vector<Bill> &test_data, int k);

// Determine the best k using the elbow method
int find_best_k(const std::vector<Bill> &train_data, const std::vector<Bill> &test_data) {
    std::vector<double> accuracies;

    int max_k = std::round(std::sqrt(train_data.size()));
    double max_accuracy = 0.0;
    int best_k = 1;

    
    for (int k = 1; k <= max_k; k++) {
        double accuracy = calculate_accuracy(train_data, test_data, k);

        if(accuracy>=max_accuracy)
        {
            max_accuracy = accuracy;
            best_k = k;
        }
        accuracies.push_back(accuracy);
    }

    std::ostringstream cmd;
    cmd << "python plot_k_values.py";
    for (double error : accuracies) {
        cmd << " " << error;
    }
    system(cmd.str().c_str());

    return best_k;
}
