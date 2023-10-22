#include <vector>
#include <algorithm>
#include <numeric>
#include "bill.h"

// Function to replace null values (represented by -1) with mean for each feature
void fill_with_mean(std::vector<Bill> &bills) {
    
    double mean_diagonal = 0, mean_height_left = 0, mean_height_right = 0;
    double mean_margin_low = 0, mean_margin_up = 0, mean_length = 0;
    int count_diagonal = 0, count_height_left = 0, count_height_right = 0;
    int count_margin_low = 0, count_margin_up = 0, count_length = 0;

    // calculate sum of each feature, and will be used to fund the mean
    for (const auto &bill : bills) {
        if (bill.diagonal != -1) {
            mean_diagonal += bill.diagonal;
            count_diagonal++;
        }
        if (bill.height_left != -1) {
            mean_height_left += bill.height_left;
            count_height_left++;
        }
        if (bill.height_right != -1) {
            mean_height_right += bill.height_right;
            count_height_right++;
        }
        if (bill.margin_low != -1) {
            mean_margin_low += bill.margin_low;
            count_margin_low++;
        }
        if (bill.margin_up != -1) {
            mean_margin_up += bill.margin_up;
            count_margin_up++;
        }
        if (bill.length != -1) {
            mean_length += bill.length;
            count_length++;
        }
    }

    //mean of each feature
    mean_diagonal /= count_diagonal;
    mean_height_left /= count_height_left;
    mean_height_right /= count_height_right;
    mean_margin_low /= count_margin_low;
    mean_margin_up /= count_margin_up;
    mean_length /= count_length;

    // Replace -1 [NULL] values with means
    for (auto &bill : bills) {
        if (bill.diagonal == -1) bill.diagonal = mean_diagonal;
        if (bill.height_left == -1) bill.height_left = mean_height_left;
        if (bill.height_right == -1) bill.height_right = mean_height_right;
        if (bill.margin_low == -1) bill.margin_low = mean_margin_low;
        if (bill.margin_up == -1) bill.margin_up = mean_margin_up;
        if (bill.length == -1) bill.length = mean_length;
    }
}
