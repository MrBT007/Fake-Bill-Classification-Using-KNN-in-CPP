#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// struct for a bill
struct Bill {
    double is_genuine;
    double diagonal;
    double height_left;
    double height_right;
    double margin_low;
    double margin_up;
    double length;
};

// Function to read CSV file and return a vector of bills
std::vector<Bill> read_csv(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<Bill> bills;

    // Skip header
    std::getline(file, line);
    int line_number = 1;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string value;
        Bill bill;

        try {
            std::getline(ss, value, ';');
            bill.is_genuine = std::stod(value);
            
            std::getline(ss, value, ';');
            bill.diagonal = value.empty() ? -1 : std::stod(value);
            
            std::getline(ss, value, ';');
            bill.height_left = value.empty() ? -1 : std::stod(value);
            
            std::getline(ss, value, ';');
            bill.height_right = value.empty() ? -1 : std::stod(value);
            
            std::getline(ss, value, ';');
            bill.margin_low = value.empty() ? -1 : std::stod(value);
            
            std::getline(ss, value, ';');
            bill.margin_up = value.empty() ? -1 : std::stod(value);
            
            std::getline(ss, value, ';');
            bill.length = value.empty() ? -1 : std::stod(value);

            bills.push_back(bill);
        } catch (const std::invalid_argument &ia) {
            std::cerr << "Error reading line " << line_number << ": " << line << std::endl;
        }

        line_number++;
    }

    file.close();
    return bills;
}

