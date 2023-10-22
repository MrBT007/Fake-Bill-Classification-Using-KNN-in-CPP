#include <vector>
#include <algorithm>
#include <random>
#include "bill.h"


// Function to split data into training and testing sets
void train_test_split(const std::vector<Bill> &bills, std::vector<Bill> &train_data, std::vector<Bill> &test_data, double test_size = 0.3) {
    // Shuffle the dataset
    std::vector<Bill> shuffled_bills = bills;

    //generates non-deterministic random number
    std::random_device rd;

    //generated random number used to generate the random sequence to split the data
    // Ensures each time the new sequence is generated
    std::mt19937 g(rd());

    //shuffules the data
    std::shuffle(shuffled_bills.begin(), shuffled_bills.end(), g);

    // Determine the split point
    int split_point = static_cast<int>(shuffled_bills.size() * (1.0 - test_size));

    // Split the data
    train_data.assign(shuffled_bills.begin(), shuffled_bills.begin() + split_point);
    test_data.assign(shuffled_bills.begin() + split_point, shuffled_bills.end());
}
