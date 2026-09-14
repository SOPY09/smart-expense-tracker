#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
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
        cout << "  " << left << setw(5) << index
             << setw(24) << title.substr(0, 22)
             << setw(18) << category.substr(0, 16)
             << "Rs." << right << setw(10)
             << fixed << setprecision(2) << amount << left << "\n";
    }
};

class ExpenseTracker {
private:
    vector<Expense> expenses;

    void setColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void resetColor() {
        setColor(7);
    }

    void printLine(char ch = '=', int width = 70) {
        cout << string(width, ch) << "\n";
    }

    void printTitle(string title) {
        setColor(11);
        printLine();
        cout << "                    " << title << "\n";
        printLine();
        resetColor();
    }

public:
    void pauseScreen() {
        setColor(8);
        cout << "\nPress Enter to continue...";
        resetColor();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

private:
    void clearScreen() {
        system("cls");
    }

public:
    void showHeader() {
        setColor(11);
        cout << "\n";
        cout << "======================================================================\n";
        cout << "                     SMART EXPENSE TRACKER\n";
        cout << "                     Personal Finance Manager\n";
        cout << "======================================================================\n";
        resetColor();
    }

    void showMenu() {
        setColor(14);
        cout << "\n";
        cout << "  +--------------------------------------------------------------+\n";
        cout << "  |                         MAIN MENU                            |\n";
        cout << "  +--------------------------------------------------------------+\n";
        resetColor();

        setColor(10);
        cout << "  |  [1]  Add Expense                                            |\n";
        cout << "  |  [2]  View Expenses                                          |\n";
        cout << "  |  [3]  Search by Category                                     |\n";
        cout << "  |  [4]  Calculate Total                                         |\n";
        cout << "  |  [5]  Find Highest Expense                                   |\n";
        cout << "  |  [6]  Save Expenses                                          |\n";
        resetColor();

        setColor(12);
        cout << "  |  [7]  Exit                                                    |\n";
        resetColor();

        setColor(14);
        cout << "  +--------------------------------------------------------------+\n";
        resetColor();
        cout << "\n  Select an option: ";
    }

    void addExpense() {
        clearScreen();
        showHeader();
        printTitle("ADD NEW EXPENSE");

        string title, category;
        double amount;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n  Expense title : ";
        getline(cin, title);

        cout << "  Category      : ";
        getline(cin, category);

        cout << "  Amount        : Rs.";
        cin >> amount;

        if (amount <= 0) {
            setColor(12);
            cout << "\n  [X] Invalid amount. Please enter a positive value.\n";
            resetColor();
            pauseScreen();
            return;
        }

        expenses.push_back(Expense(title, category, amount));

        setColor(10);
        cout << "\n  [OK] Expense added successfully!\n";
        resetColor();

        pauseScreen();
    }

    void viewExpenses() {
        clearScreen();
        showHeader();

        if (expenses.empty()) {
            setColor(14);
            cout << "\n  No expenses found.\n";
            resetColor();
            pauseScreen();
            return;
        }

        printTitle("YOUR EXPENSES");

        cout << "\n  " << left
             << setw(5) << "#"
             << setw(24) << "TITLE"
             << setw(18) << "CATEGORY"
             << "AMOUNT\n";

        setColor(8);
        cout << "  --------------------------------------------------------------------\n";
        resetColor();

        for (int i = 0; i < expenses.size(); i++) {
            expenses[i].display(i + 1);
        }

        setColor(11);
        cout << "\n  Total Records: " << expenses.size() << "\n";
        resetColor();

        pauseScreen();
    }

    void calculateTotal() {
        clearScreen();
        showHeader();
        printTitle("SPENDING SUMMARY");

        double total = 0;

        for (Expense e : expenses) {
            total += e.getAmount();
        }

        setColor(14);
        cout << "\n  Total Amount Spent\n";
        resetColor();

        setColor(10);
        cout << "\n                 Rs." << fixed << setprecision(2) << total << "\n";
        resetColor();

        cout << "\n  Number of Expenses: " << expenses.size() << "\n";

        if (!expenses.empty()) {
            cout << "  Average Expense   : Rs."
                 << fixed << setprecision(2)
                 << total / expenses.size() << "\n";
        }

        pauseScreen();
    }

    void findHighestExpense() {
        clearScreen();
        showHeader();

        if (expenses.empty()) {
            setColor(14);
            cout << "\n  No expenses found.\n";
            resetColor();
            pauseScreen();
            return;
        }

        printTitle("HIGHEST EXPENSE");

        int index = 0;

        for (int i = 1; i < expenses.size(); i++) {
            if (expenses[i].getAmount() > expenses[index].getAmount()) {
                index = i;
            }
        }

        setColor(12);
        cout << "\n  Highest spending item:\n\n";
        resetColor();

        cout << "  Title    : " << expenses[index].getTitle() << "\n";
        cout << "  Category : " << expenses[index].getCategory() << "\n";

        setColor(10);
        cout << "  Amount   : Rs."
             << fixed << setprecision(2)
             << expenses[index].getAmount() << "\n";
        resetColor();

        pauseScreen();
    }

    void searchByCategory() {
        clearScreen();
        showHeader();

        if (expenses.empty()) {
            setColor(14);
            cout << "\n  No expenses found.\n";
            resetColor();
            pauseScreen();
            return;
        }

        printTitle("SEARCH BY CATEGORY");

        string category;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n  Enter category: ";
        getline(cin, category);

        bool found = false;

        cout << "\n  " << left
             << setw(5) << "#"
             << setw(24) << "TITLE"
             << setw(18) << "CATEGORY"
             << "AMOUNT\n";

        setColor(8);
        cout << "  --------------------------------------------------------------------\n";
        resetColor();

        for (int i = 0; i < expenses.size(); i++) {
            if (expenses[i].getCategory() == category) {
                expenses[i].display(i + 1);
                found = true;
            }
        }

        if (!found) {
            setColor(12);
            cout << "\n  [X] No expenses found in this category.\n";
            resetColor();
        }

        pauseScreen();
    }

    void saveExpenses() {
        ofstream file("expenses.txt");

        if (!file) {
            setColor(12);
            cout << "\n  [X] Unable to open file.\n";
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
        system("cls");
        tracker.showHeader();
        tracker.showMenu();

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
                tracker.showHeader();
                tracker.pauseScreen();
                break;

            case 7:
                tracker.saveExpenses();
                system("cls");
                tracker.showHeader();
                cout << "\n  Thank you for using Smart Expense Tracker!\n\n";
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
