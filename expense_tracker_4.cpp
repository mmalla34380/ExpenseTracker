#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <limits> // Added for std::numeric_limits

// Struct to represent an expense
struct Expense {
    std::string date;     // Format: YYYY-MM-DD
    double amount;
    std::string category;
    std::string description;
};

// Vector to store expenses
std::vector<Expense> expenses;

// Function to parse date string to integers for comparison
bool parseDate(const std::string& dateStr, int& year, int& month, int& day) {
    std::istringstream iss(dateStr);
    char dash1, dash2;
    if (!(iss >> year >> dash1 >> month >> dash2 >> day) || dash1 != '-' || dash2 != '-') {
        return false;
    }
    return true;
}

// Function to compare two dates (returns true if date1 <= date2)
bool dateLessOrEqual(const std::string& date1, const std::string& date2) {
    int y1, m1, d1, y2, m2, d2;
    if (!parseDate(date1, y1, m1, d1) || !parseDate(date2, y2, m2, d2)) {
        return false;
    }
    if (y1 != y2) return y1 < y2;
    if (m1 != m2) return m1 < m2;
    return d1 <= d2;
}

void addExpense() {
    Expense exp;
    std::cout << "Enter date (YYYY-MM-DD): ";
    std::getline(std::cin, exp.date); // Use getline for date
    // Basic validation
    int y, m, d;
    if (!parseDate(exp.date, y, m, d)) {
        std::cout << "Invalid date format. Please use YYYY-MM-DD." << std::endl;
        return;
    }
    
    std::cout << "Enter amount: ";
    std::cin >> exp.amount;
    if (std::cin.fail()) {
        std::cout << "Invalid amount. Please enter a number." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear newline after amount
    std::cout << "Enter category: ";
    std::getline(std::cin, exp.category); // Use getline for category
    std::cout << "Enter description: ";
    std::getline(std::cin, exp.description); // Use getline for description
    
    expenses.push_back(exp);
    std::cout << "Expense added successfully." << std::endl;
}

void viewExpenses(const std::string& filterDateStart = "", const std::string& filterDateEnd = "", const std::string& filterCategory = "") {
    std::vector<Expense> filtered = expenses;
    
    if (!filterDateStart.empty()) {
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&](const Expense& e) {
            return !dateLessOrEqual(filterDateStart, e.date);
        }), filtered.end());
    }
    if (!filterDateEnd.empty()) {
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&](const Expense& e) {
            return !dateLessOrEqual(e.date, filterDateEnd);
        }), filtered.end());
    }
    if (!filterCategory.empty()) {
        filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&](const Expense& e) {
            return e.category != filterCategory;
        }), filtered.end());
    }
    
    if (filtered.empty()) {
        std::cout << "No expenses found." << std::endl;
        return;
    }
    
    std::cout << "\nExpenses:" << std::endl;
    for (const auto& e : filtered) {
        std::cout << "Date: " << e.date << ", Amount: " << std::fixed << std::setprecision(2) << e.amount
                  << ", Category: " << e.category << ", Description: " << e.description << std::endl;
    }
}

void summary() {
    if (expenses.empty()) {
        std::cout << "No expenses to summarize." << std::endl;
        return;
    }
    
    double total = 0.0;
    std::map<std::string, double> categories;
    
    for (const auto& e : expenses) {
        total += e.amount;
        categories[e.category] += e.amount;
    }
    
    std::cout << "\nOverall Total: " << std::fixed << std::setprecision(2) << total << std::endl;
    std::cout << "Totals by Category:" << std::endl;
    for (const auto& pair : categories) {
        std::cout << pair.first << ": " << std::fixed << std::setprecision(2) << pair.second << std::endl;
    }
}

int main() {
    while (true) {
        std::cout << "\nExpense Tracker Menu:" << std::endl;
        std::cout << "1. Add Expense" << std::endl;
        std::cout << "2. View All Expenses" << std::endl;
        std::cout << "3. Filter Expenses by Date Range" << std::endl;
        std::cout << "4. Filter Expenses by Category" << std::endl;
        std::cout << "5. View Summary" << std::endl;
        std::cout << "6. Exit" << std::endl;
        
        std::cout << "Enter choice: ";
        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please enter a number." << std::endl;
            continue;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear newline after choice

        if (choice == 1) {
            addExpense();
        } else if (choice == 2) {
            viewExpenses();
        } else if (choice == 3) {
            std::string start, end;
            std::cout << "Enter start date (YYYY-MM-DD): ";
            std::getline(std::cin, start);
            std::cout << "Enter end date (YYYY-MM-DD): ";
            std::getline(std::cin, end);
            // Basic validation
            int y1, m1, d1, y2, m2, d2;
            if (!parseDate(start, y1, m1, d1) || !parseDate(end, y2, m2, d2)) {
                std::cout << "Invalid date format." << std::endl;
            } else {
                viewExpenses(start, end);
            }
        } else if (choice == 4) {
            std::string category;
            std::cout << "Enter category: ";
            std::getline(std::cin, category);
            viewExpenses("", "", category);
        } else if (choice == 5) {
            summary();
        } else if (choice == 6) {
            break;
        } else {
            std::cout << "Invalid choice. Please select a number between 1 and 6." << std::endl;
        }
    }
    return 0;
}