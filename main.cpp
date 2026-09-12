#include <bits/stdc++.h>
using namespace std;

class Expense {
private:
    string title;
    string category;
    double amount;

public:
    Expense() {
        title = "";
        category = "";
        amount = 0;
    }

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
             << category << " | Rs"
             << fixed << setprecision(2) << amount << endl;
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

        cout << "Enter amount: Rs";
        cin >> amount;

        if (amount <= 0) {
            cout << "Invalid amount!\n";
            return;
        }

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

    void calculateTotal() {
        double total = 0;

        for (Expense e : expenses) {
            total += e.getAmount();
        }

        cout << "\nTotal spending: Rs"
             << fixed << setprecision(2)
             << total << endl;
    }

    void findHighestExpense() {
        if (expenses.empty()) {
            cout << "No expenses found.\n";
            return;
        }

        int index = 0;

        for (int i = 1; i < expenses.size(); i++) {
            if (expenses[i].getAmount() > expenses[index].getAmount()) {
                index = i;
            }
        }

        cout << "\n------ Highest Expense ------\n";
        expenses[index].display(index + 1);
    }

    void searchByCategory() {
        if (expenses.empty()) {
            cout << "No expenses found.\n";
            return;
        }

        string category;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter category: ";
        getline(cin, category);

        bool found = false;

        cout << "\n------ Search Results ------\n";

        for (int i = 0; i < expenses.size(); i++) {
            if (expenses[i].getCategory() == category) {
                expenses[i].display(i + 1);
                found = true;
            }
        }

        if (!found) {
            cout << "No expenses found in this category.\n";
        }
    }

    void saveExpenses() {
        ofstream file("expenses.txt");

        if (!file) {
            cout << "Unable to open file.\n";
            return;
        }

        for (Expense e : expenses) {
            file << e.getTitle() << "|"
                 << e.getCategory() << "|"
                 << e.getAmount() << endl;
        }

        file.close();

        cout << "Expenses saved successfully.\n";
    }

    void loadExpenses() {
        ifstream file("expenses.txt");

        if (!file) {
            return;
        }

        string title, category, amount;

        while (getline(file, title, '|') &&
               getline(file, category, '|') &&
               getline(file, amount)) {

            expenses.push_back(
                Expense(title, category, stod(amount))
            );
        }

        file.close();
    }
};

int main() {
    ExpenseTracker tracker;

    tracker.loadExpenses();

    int choice;

    do {
        cout << "\n================================\n";
        cout << "       SMART EXPENSE TRACKER\n";
        cout << "================================\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Search by Category\n";
        cout << "4. Calculate Total\n";
        cout << "5. Find Highest Expense\n";
        cout << "6. Save Expenses\n";
        cout << "7. Exit\n";
        cout << "================================\n";
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
                tracker.searchByCategory();
                break;

            case 4:
                tracker.calculateTotal();
                break;

            case 5:
                tracker.findHighestExpense();
                break;

            case 6:
                tracker.saveExpenses();
                break;

            case 7:
                tracker.saveExpenses();
                cout << "Thank you for using Smart Expense Tracker!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}