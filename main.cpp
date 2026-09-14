#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor() {
    setColor(7);
}

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
        cout << "  " << left
             << setw(5) << index
             << setw(25) << title.substr(0, 23)
             << setw(18) << category.substr(0, 16)
             << "Rs." << right << setw(10)
             << fixed << setprecision(2) << amount
             << left << "\n";
    }
};

class ExpenseTracker {
private:
    vector<Expense> expenses;

    void clearScreen() {
        system("cls");
    }

    void printLine(char ch = '=', int width = 72) {
        cout << string(width, ch) << "\n";
    }

    void printSection(string title) {
        setColor(11);
        cout << "\n  +------------------------------------------------------------------+\n";
        cout << "  |  " << left << setw(64) << title << "|\n";
        cout << "  +------------------------------------------------------------------+\n";
        resetColor();
    }

    void printStat(string label, string value, int color) {
        setColor(8);
        cout << "  | ";
        setColor(14);
        cout << left << setw(20) << label;
        setColor(color);
        cout << setw(42) << value;
        setColor(8);
        cout << "|\n";
        resetColor();
    }

    double getTotal() {
        double total = 0;

        for (Expense e : expenses) {
            total += e.getAmount();
        }

        return total;
    }

    int getHighestIndex() {
        if (expenses.empty()) {
            return -1;
        }

        int index = 0;

        for (int i = 1; i < expenses.size(); i++) {
            if (expenses[i].getAmount() > expenses[index].getAmount()) {
                index = i;
            }
        }

        return index;
    }

public:
    void pauseScreen() {
        setColor(8);
        cout << "\n  Press Enter to continue...";
        resetColor();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void showHeader() {
        setColor(11);
        cout << "\n";
        cout << "  ====================================================================\n";
        cout << "  ||                    SMART EXPENSE TRACKER                     ||\n";
        cout << "  ||                     Personal Finance Manager                  ||\n";
        cout << "  ====================================================================\n";
        resetColor();
    }

    void showDashboard() {
        double total = getTotal();
        int highestIndex = getHighestIndex();

        setColor(8);
        cout << "\n  +----------------------+----------------------+----------------------+\n";
        cout << "  | ";
        setColor(14);
        cout << left << setw(20) << "TOTAL SPENDING";
        setColor(8);
        cout << "| ";
        setColor(14);
        cout << left << setw(20) << "TOTAL EXPENSES";
        setColor(8);
        cout << "| ";
        setColor(14);
        cout << left << setw(20) << "HIGHEST EXPENSE";
        setColor(8);
        cout << "|\n";

        cout << "  | ";
        setColor(10);
        cout << left << setw(20) << ("Rs." + to_string((long long)total));
        setColor(8);
        cout << "| ";
        setColor(10);
        cout << left << setw(20) << to_string(expenses.size());
        setColor(8);
        cout << "| ";

        if (highestIndex != -1) {
            setColor(12);
            cout << left << setw(20) << ("Rs." + to_string((long long)expenses[highestIndex].getAmount()));
        } else {
            setColor(8);
            cout << left << setw(20) << "Rs.0";
        }

        setColor(8);
        cout << "|\n";
        cout << "  +----------------------+----------------------+----------------------+\n";
        resetColor();
    }

    void showMenu() {
        setColor(14);
        cout << "\n  +------------------------------------------------------------------+\n";
        cout << "  |                           MAIN MENU                              |\n";
        cout << "  +------------------------------------------------------------------+\n";
        resetColor();

        setColor(10);
        cout << "  |  [1]  Add Expense                                                |\n";
        cout << "  |  [2]  View All Expenses                                          |\n";
        cout << "  |  [3]  Search by Category                                         |\n";
        cout << "  |  [4]  Spending Summary                                           |\n";
        cout << "  |  [5]  Find Highest Expense                                       |\n";
        cout << "  |  [6]  Save Expenses                                              |\n";
        resetColor();

        setColor(12);
        cout << "  |  [7]  Exit                                                       |\n";
        resetColor();

        setColor(14);
        cout << "  +------------------------------------------------------------------+\n";
        resetColor();

        cout << "\n  Select an option [1-7]: ";
    }

    void addExpense() {
        clearScreen();
        showHeader();
        printSection("ADD NEW EXPENSE");

        string title;
        string category;
        double amount;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n  Expense title : ";
        getline(cin, title);

        cout << "  Category      : ";
        getline(cin, category);

        cout << "  Amount        : Rs.";
        cin >> amount;

        if (cin.fail() || amount <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            setColor(12);
            cout << "\n  [X] Invalid amount. Please enter a positive number.\n";
            resetColor();

            pauseScreen();
            return;
        }

        if (title.empty() || category.empty()) {
            setColor(12);
            cout << "\n  [X] Title and category cannot be empty.\n";
            resetColor();

            pauseScreen();
            return;
        }

        expenses.push_back(Expense(title, category, amount));

        setColor(10);
        cout << "\n  [OK] Expense added successfully!\n";
        resetColor();

        setColor(8);
        cout << "  Title    : " << title << "\n";
        cout << "  Category : " << category << "\n";
        cout << "  Amount   : Rs." << fixed << setprecision(2) << amount << "\n";
        resetColor();

        pauseScreen();
    }

    void viewExpenses() {
        clearScreen();
        showHeader();
        printSection("YOUR EXPENSES");

        if (expenses.empty()) {
            setColor(14);
            cout << "\n  No expenses found.\n";
            cout << "  Add your first expense from the main menu.\n";
            resetColor();

            pauseScreen();
            return;
        }

        cout << "\n  " << left
             << setw(5) << "#"
             << setw(25) << "TITLE"
             << setw(18) << "CATEGORY"
             << "AMOUNT\n";

        setColor(8);
        cout << "  --------------------------------------------------------------------\n";
        resetColor();

        for (int i = 0; i < expenses.size(); i++) {
            expenses[i].display(i + 1);
        }

        setColor(11);
        cout << "\n  Total Records : " << expenses.size() << "\n";
        cout << "  Total Spent   : Rs." << fixed << setprecision(2) << getTotal() << "\n";
        resetColor();

        pauseScreen();
    }

    void calculateTotal() {
        clearScreen();
        showHeader();
        printSection("SPENDING SUMMARY");

        double total = getTotal();
        double average = expenses.empty() ? 0 : total / expenses.size();

        cout << "\n";
        printStat("Total Spending", "Rs." + to_string(total), 10);
        printStat("Number of Expenses", to_string(expenses.size()), 11);
        printStat("Average Expense", "Rs." + to_string(average), 14);

        int highestIndex = getHighestIndex();

        if (highestIndex != -1) {
            printStat("Highest Expense",
                      "Rs." + to_string(expenses[highestIndex].getAmount()),
                      12);
        } else {
            printStat("Highest Expense", "Rs.0", 8);
        }

        cout << "\n";
        setColor(10);
        cout << "  Your current total spending is Rs."
             << fixed << setprecision(2) << total << "\n";
        resetColor();

        pauseScreen();
    }

    void findHighestExpense() {
        clearScreen();
        showHeader();
        printSection("HIGHEST EXPENSE");

        int index = getHighestIndex();

        if (index == -1) {
            setColor(14);
            cout << "\n  No expenses found.\n";
            resetColor();

            pauseScreen();
            return;
        }

        setColor(12);
        cout << "\n  Highest spending item\n";
        resetColor();

        setColor(8);
        cout << "\n  +--------------------------------------------------------------+\n";
        cout << "  | Title    : " << left << setw(47)
             << expenses[index].getTitle().substr(0, 47) << "|\n";
        cout << "  | Category : " << left << setw(47)
             << expenses[index].getCategory().substr(0, 47) << "|\n";
        cout << "  | Amount   : ";

        setColor(10);
        cout << "Rs." << fixed << setprecision(2)
             << left << setw(43) << expenses[index].getAmount();
        setColor(8);
        cout << "|\n";
        cout << "  +--------------------------------------------------------------+\n";
        resetColor();

        pauseScreen();
    }

    void searchByCategory() {
        clearScreen();
        showHeader();
        printSection("SEARCH BY CATEGORY");

        if (expenses.empty()) {
            setColor(14);
            cout << "\n  No expenses found.\n";
            resetColor();

            pauseScreen();
            return;
        }

        string category;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n  Enter category: ";
        getline(cin, category);

        bool found = false;
        double categoryTotal = 0;

        cout << "\n  " << left
             << setw(5) << "#"
             << setw(25) << "TITLE"
             << setw(18) << "CATEGORY"
             << "AMOUNT\n";

        setColor(8);
        cout << "  --------------------------------------------------------------------\n";
        resetColor();

        for (int i = 0; i < expenses.size(); i++) {
            if (expenses[i].getCategory() == category) {
                expenses[i].display(i + 1);
                categoryTotal += expenses[i].getAmount();
                found = true;
            }
        }

        if (!found) {
            setColor(12);
            cout << "\n  [X] No expenses found in this category.\n";
            resetColor();
        } else {
            setColor(10);
            cout << "\n  Category Total : Rs."
                 << fixed << setprecision(2) << categoryTotal << "\n";
            resetColor();
        }

        pauseScreen();
    }

    void saveExpenses() {
        ofstream file("expenses.txt");

        if (!file) {
            setColor(12);
            cout << "\n  [X] Unable to open expenses.txt.\n";
            resetColor();
            return;
        }

        for (Expense e : expenses) {
            file << e.getTitle() << "|"
                 << e.getCategory() << "|"
                 << e.getAmount() << endl;
        }

        file.close();

        setColor(10);
        cout << "\n  [OK] Expenses saved successfully.\n";
        resetColor();
    }

    void loadExpenses() {
        ifstream file("expenses.txt");

        if (!file) {
            return;
        }

        string title;
        string category;
        string amount;

        while (getline(file, title, '|') &&
               getline(file, category, '|') &&
               getline(file, amount)) {
            try {
                expenses.push_back(
                    Expense(title, category, stod(amount))
                );
            } catch (...) {
            }
        }

        file.close();
    }
};

int main() {
    ExpenseTracker tracker;

    tracker.loadExpenses();

    int choice;

    do {
        system("cls");
        tracker.showHeader();
        tracker.showDashboard();
        tracker.showMenu();

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            setColor(12);
            cout << "\n  [X] Invalid input. Please enter a number from 1 to 7.\n";
            resetColor();
            Sleep(1000);
            continue;
        }

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
                tracker.pauseScreen();
                break;

            case 7:
                tracker.saveExpenses();
                system("cls");
                tracker.showHeader();

                setColor(10);
                cout << "\n  Thank you for using Smart Expense Tracker!\n";
                cout << "  Your expenses have been saved successfully.\n\n";
                resetColor();
                break;

            default:
                setColor(12);
                cout << "\n  [X] Invalid choice. Please select 1-7.\n";
                resetColor();
                Sleep(1000);
        }

    } while (choice != 7);

    return 0;
}
