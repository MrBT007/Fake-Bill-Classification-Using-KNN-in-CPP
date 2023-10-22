#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include "bill.h"

extern std::vector<Bill> read_csv(const std::string &filename);
extern void fill_with_mean(std::vector<Bill> &bills);
extern void train_test_split(const std::vector<Bill> &bills, std::vector<Bill> &train_data, std::vector<Bill> &test_data, double test_size=0.2);
extern double calculate_accuracy(const std::vector<Bill> &train_data, const std::vector<Bill> &test_data, int k);
extern int find_best_k(const std::vector<Bill> &train_data, const std::vector<Bill> &test_data);
extern double knn_predict(const std::vector<Bill> &train_data, const Bill &test_bill, int k);
extern std::map<std::pair<double, double>, int> confusion_matrix(const std::vector<Bill> &train_data, const std::vector<Bill> &test_data, int k);

using namespace std;

Bill get_input_bill() {
    Bill bill;
    std::cout << "Enter bill features:" << std::endl;
    std::cout << "Diagonal: ";
    std::cin >> bill.diagonal;
    std::cout << "Height left: ";
    std::cin >> bill.height_left;
    std::cout << "Height right: ";
    std::cin >> bill.height_right;
    std::cout << "Margin low: ";
    std::cin >> bill.margin_low;
    std::cout << "Margin up: ";
    std::cin >> bill.margin_up;
    std::cout << "Length: ";
    std::cin >> bill.length;
    return bill;
}

void print_confusion_matrix(const std::map<std::pair<double, double>, int> &confusion_matrix) {
    std::cout << "Confusion Matrix:\n";
    std::cout << std::left << std::setw(10) << "  | Actual" << std::setw(12) << "| Predicted" << "|\n";
    std::cout << "--|--------|-----------|\n";

    for (const auto &row : confusion_matrix) {
        std::cout << "  | " << std::left << std::setw(8) << row.first.first << " | " << std::setw(10) << row.first.second << "| " << row.second << " |\n";
    }
}

int main() {
    // Read CSV
    std::vector<Bill> bills = read_csv("dataset/fake_bills.csv");

    system("python visualize.py");

    // Data preprocessing
    fill_with_mean(bills);

    cout<<"Total Rows : "<<bills.size()<<"\n";

    // Split data
    std::vector<Bill> train_data, test_data;
    train_test_split(bills, train_data, test_data,0.3);

    // Determine best k using elbow method
    int best_k = find_best_k(train_data, test_data);
    std::cout << "Best value for k: " << best_k << std::endl;

    // Calculate accuracy using best k
    double accuracy = calculate_accuracy(train_data, test_data, best_k);
    std::cout << "Accuracy using best k: " << accuracy << std::endl;

    map<pair<double, double>, int> confusionMatrix = confusion_matrix(train_data,test_data,best_k);
    print_confusion_matrix(confusionMatrix);

    char choice;
    std::cout << "Do you want to predict a bill? (y/n): ";
    std::cin >> choice;
    while (choice == 'y' || choice == 'Y'){
        Bill input_bill = get_input_bill();
        double prediction = knn_predict(train_data, input_bill, best_k);
        if (prediction == 1.0) {
            std::cout << "The bill is predicted to be genuine." << std::endl;
        } else {
            std::cout << "The bill is predicted to be fake." << std::endl;
        }
        std::cout << "Do you want to predict another bill? (y/n): ";
        std::cin >> choice;
    }

    return 0;
}
