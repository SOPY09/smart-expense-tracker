#include <bits/stdc++.h>
using namespace std;

class Expense {
private:
    string title;
    string category;
    double amount;

public:
    Expense(string t, string c, double a) {
        title = t;
        category = c;
        amount = a;
    }

    string getTitle() {
        return title;
    }

    string getCategory() {
        return category;
    }

    double getAmount() {
        return amount;
    }

    void display(int index) {
        cout << index << ". "
             << title << " | "
             << category << " | ₹"
             << fixed << setprecision(2)
             << amount << endl;
    }
};

class ExpenseTracker {
private:
    vector<Expense> expenses;

public:
    void addExpense() {
        string title, category;
        double amount;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter expense title: ";
        getline(cin, title);

        cout << "Enter category: ";
        getline(cin, category);

        cout << "Enter amount: ₹";
        cin >> amount;

        expenses.push_back(Expense(title, category, amount));

        cout << "Expense added successfully!\n";
    }

    void viewExpenses() {
        if (expenses.empty()) {
            cout << "No expenses found.\n";
            return;
        }

        cout << "\n------ All Expenses ------\n";

        for (int i = 0; i < expenses.size(); i++) {
            expenses[i].display(i + 1);
        }
    }
};

int main() {
    ExpenseTracker tracker;

    int choice;

    do {
        cout << "\n==============================\n";
        cout << "    SMART EXPENSE TRACKER\n";
        cout << "==============================\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                tracker.addExpense();
                break;

            case 2:
                tracker.viewExpenses();
                break;

            case 3:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 3);

    return 0;
}