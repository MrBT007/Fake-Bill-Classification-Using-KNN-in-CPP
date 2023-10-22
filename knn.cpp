#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include "bill.h"


// Function to calculate Euclidean distance between two bills
double euclidean_distance(const Bill &a, const Bill &b) {
    return std::sqrt(
        std::pow(a.diagonal - b.diagonal, 2) +
        std::pow(a.height_left - b.height_left, 2) +
        std::pow(a.height_right - b.height_right, 2) +
        std::pow(a.margin_low - b.margin_low, 2) +
        std::pow(a.margin_up - b.margin_up, 2) +
        std::pow(a.length - b.length, 2)
    );
}

// KNN prediction
double knn_predict(const std::vector<Bill> &train_data, const Bill &test_bill, int k) {
    std::vector<std::pair<double, double>> distances; // <distance, label>

    for (const auto &train_bill : train_data) {
        double dist = euclidean_distance(train_bill, test_bill);
        distances.push_back({dist, train_bill.is_genuine});
    }

    std::sort(distances.begin(), distances.end());

    std::map<double, int> frequency;
    for (int i = 0; i < k; i++) {
        frequency[distances[i].second]++; //counts of class
    }

    double prediction = 0; //default label
    int max_count = 0;
    for (const auto &f : frequency) {
        if (f.second > max_count) {
            max_count = f.second;
            prediction = f.first;
        }
    }

    return prediction;
}

// Calculate accuracy
double calculate_accuracy(const std::vector<Bill> &train_data, const std::vector<Bill> &test_data, int k) {
    int correct_predictions = 0;
    for (const auto &test_bill : test_data) {
        double prediction = knn_predict(train_data, test_bill, k);
        if (prediction == test_bill.is_genuine) {
            correct_predictions++;
        }
    }
    return static_cast<double>(correct_predictions) / test_data.size();
}

// Calculate confusion matrix
std::map<std::pair<double, double>, int> confusion_matrix(const std::vector<Bill> &train_data, const std::vector<Bill> &test_data, int k) {
    std::map<std::pair<double, double>, int> matrix; // <actual, predicted>, count

    // Initialize matrix with zeros for all possible combinations
    matrix[{0.0, 0.0}] = 0;
    matrix[{0.0, 1.0}] = 0;
    matrix[{1.0, 0.0}] = 0;
    matrix[{1.0, 1.0}] = 0;

    for (const auto &test_bill : test_data) {
        double prediction = knn_predict(train_data, test_bill, k);
        matrix[{test_bill.is_genuine, prediction}]++;
    }

    return matrix;
}

