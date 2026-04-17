#include <iostream>
#include <fstream>
#include <iomanip>
#include <unordered_map>
using namespace std;

// Node for Linked List
class Expense {
public:
    string date, category;
    float amount;
    Expense* next;

    Expense(string d, string c, float a) {
        date = d;
        category = c;
        amount = a;
        next = NULL;
    }
};

// Manager using Linked List
class ExpenseManager {
private:
    Expense* head;

public:
    ExpenseManager() {
        head = NULL;
    }

    void addExpense() {
        string date, category;
        float amount;

        cout << "Enter date (DD/MM/YYYY): ";
        cin >> date;
        cin.ignore();

        cout << "Enter category: ";
        getline(cin, category);

        cout << "Enter amount: ";
        cin >> amount;

        Expense* newNode = new Expense(date, category, amount);

        if (head == NULL) {
            head = newNode;
        } else {
            Expense* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }

        cout << "Expense added successfully!\n";
    }

    void viewExpenses() {
        if (head == NULL) {
            cout << "No expenses found.\n";
            return;
        }

        cout << "\n---------------------------------------------\n";
        cout << left << setw(15) << "Date"
             << setw(20) << "Category"
             << setw(10) << "Amount" << endl;
        cout << "---------------------------------------------\n";

        Expense* temp = head;
        while (temp != NULL) {
            cout << left << setw(15) << temp->date
                 << setw(20) << temp->category
                 << setw(10) << temp->amount << endl;
            temp = temp->next;
        }
    }

    void totalExpense() {
        float total = 0;
        Expense* temp = head;

        while (temp != NULL) {
            total += temp->amount;
            temp = temp->next;
        }

        cout << "Total Expense: " << total << endl;
    }

    void searchByCategory() {
        string cat;
        cin.ignore();
        cout << "Enter category: ";
        getline(cin, cat);

        bool found = false;
        Expense* temp = head;

        while (temp != NULL) {
            if (temp->category == cat) {
                cout << temp->date << "\t" << temp->category << "\t" << temp->amount << endl;
                found = true;
            }
            temp = temp->next;
        }

        if (!found) cout << "No records found.\n";
    }

    // HASH MAP USED HERE
    void categorySummary() {
        unordered_map<string, float> summary;

        Expense* temp = head;
        while (temp != NULL) {
            summary[temp->category] += temp->amount;
            temp = temp->next;
        }

        cout << "\n===== Category Summary =====\n";
        for (auto &p : summary) {
            cout << p.first << ": " << p.second << endl;
        }
    }

    void saveToFile() {
        ofstream file("expenses.txt");

        Expense* temp = head;
        while (temp != NULL) {
            file << temp->date << "|" << temp->category << "|" << temp->amount << endl;
            temp = temp->next;
        }

        file.close();
        cout << "Data saved!\n";
    }

    void loadFromFile() {
        ifstream file("expenses.txt");
        if (!file) return;

        string date, category;
        float amount;

        while (getline(file, date, '|')) {
            getline(file, category, '|');
            file >> amount;
            file.ignore();

            Expense* newNode = new Expense(date, category, amount);

            if (head == NULL) {
                head = newNode;
            } else {
                Expense* temp = head;
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = newNode;
            }
        }

        file.close();
    }
};

// Login
void login() {
    string pass;
    int attempts = 3;

    while (attempts--) {
        cout << "Enter password: ";
        cin >> pass;

        if (pass == "1234") return;

        cout << "Wrong password!\n";
    }

    cout << "Access denied!\n";
    exit(0);
}

// Menu
void showMenu() {
    cout << "\n=====================================\n";
    cout << "     DAILY EXPENSE TRACKER SYSTEM\n";
    cout << "=====================================\n";
    cout << "1. Add Expense\n";
    cout << "2. View Expenses\n";
    cout << "3. Total Expense\n";
    cout << "4. Search by Category\n";
    cout << "5. Category Summary\n";
    cout << "6. Save & Exit\n";
    cout << "=====================================\n";
    cout << "Enter your choice: ";
}

// Main
int main() {
    ExpenseManager manager;
    int choice;

    login();
    manager.loadFromFile();

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: manager.addExpense(); break;
            case 2: manager.viewExpenses(); break;
            case 3: manager.totalExpense(); break;
            case 4: manager.searchByCategory(); break;
            case 5: manager.categorySummary(); break;
            case 6:
                manager.saveToFile();
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
