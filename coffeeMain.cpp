#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
using namespace std;

const int MAX_ITEMS = 50;
const int MAX_ORDERS = 100;
const int MAX_EMPLOYEES = 20;
const int MAX_FEEDBACKS = 100;

// Global arrays for menu items
int menuIds[MAX_ITEMS];
string menuNames[MAX_ITEMS];
float menuPrices[MAX_ITEMS];
int menuStocks[MAX_ITEMS];
int menuCount = 0;

// Global arrays for orders
int orderIds[MAX_ORDERS];
string orderCustomers[MAX_ORDERS];
string orderItems[MAX_ORDERS];
float orderTotals[MAX_ORDERS];
string orderDates[MAX_ORDERS];
int orderCount = 0;

// Global arrays for employees
int employeeIds[MAX_EMPLOYEES];
string employeeNames[MAX_EMPLOYEES];
string employeePositions[MAX_EMPLOYEES];
float employeeSalaries[MAX_EMPLOYEES];
int employeeCount = 0;

// Global arrays for feedback
string feedbackNames[MAX_FEEDBACKS];
string feedbackComments[MAX_FEEDBACKS];
int feedbackRatings[MAX_FEEDBACKS];
int feedbackCount = 0;

// Function declarations
string who();
void header();
void clearScreen();
void customerMenu();
void adminMenu();
void orderCoffee();
void viewMenu();
void viewOrderHistory();
void loyaltyProgram();
void giveFeedback();
void manageInventory();
void manageMenu();
void viewOrders();
void manageEmployees();
void viewSalesReports();

// File handling functions
void loadData();
void saveMenuData();
void saveOrderData();
void saveEmployeeData();
void saveFeedbackData();

int main()
{
    loadData(); // Load data from files at startup

    while (true)
    {
        string userType = who();
        clearScreen();

        if (userType == "ADMIN")
        {
            while (true)
            {
                adminMenu();
                int choice;
                cin >> choice;
                clearScreen();

                if (choice == 1)
                {
                    manageInventory();
                }
                else if (choice == 2)
                {
                    manageMenu();
                }
                else if (choice == 3)
                {
                    viewOrders();
                }
                else if (choice == 4)
                {
                    manageEmployees();
                }
                else if (choice == 5)
                {
                    viewSalesReports();
                }
                else if (choice == 6)
                {
                    break;
                }
                else
                {
                    cout << "Invalid choice!" << endl;
                }
                clearScreen();
            }
        }
        else if (userType == "CUSTOMER")
        {
            while (true)
            {
                customerMenu();
                int choice;
                cin >> choice;
                clearScreen();

                if (choice == 1)
                {
                    orderCoffee();
                }
                else if (choice == 2)
                {
                    viewMenu();
                }
                else if (choice == 3)
                {
                    viewOrderHistory();
                }
                else if (choice == 4)
                {
                    loyaltyProgram();
                }
                else if (choice == 5)
                {
                    giveFeedback();
                }
                else if (choice == 6)
                {
                    break;
                }
                else
                {
                    cout << "Invalid choice!" << endl;
                }
                clearScreen();
            }
        }
    }

    // Save data before exiting
    saveMenuData();
    saveOrderData();
    saveEmployeeData();
    saveFeedbackData();

    return 0;
}

// File handling implementations
void loadData()
{
    // Load menu data
    fstream menuFile("menu_data.txt", ios::in);
    if (menuFile.is_open())
    {
        menuCount = 0;
        while (menuFile >> menuIds[menuCount] >> menuPrices[menuCount] >> menuStocks[menuCount])
        {
            menuFile.ignore();
            getline(menuFile, menuNames[menuCount]);
            menuCount++;
        }
        menuFile.close();
    }

    // Load order data
    fstream orderFile("order_data.txt", ios::in);
    if (orderFile.is_open())
    {
        orderCount = 0;
        while (orderFile >> orderIds[orderCount] >> orderTotals[orderCount])
        {
            orderFile.ignore();
            getline(orderFile, orderCustomers[orderCount]);
            getline(orderFile, orderItems[orderCount]);
            getline(orderFile, orderDates[orderCount]);
            orderCount++;
        }
        orderFile.close();
    }

    // Load employee data
    fstream empFile("employee_data.txt", ios::in);
    if (empFile.is_open())
    {
        employeeCount = 0;
        while (empFile >> employeeIds[employeeCount] >> employeeSalaries[employeeCount])
        {
            empFile.ignore();
            getline(empFile, employeeNames[employeeCount]);
            getline(empFile, employeePositions[employeeCount]);
            employeeCount++;
        }
        empFile.close();
    }

    // Load feedback data
    fstream feedbackFile("feedback_data.txt", ios::in);
    if (feedbackFile.is_open())
    {
        feedbackCount = 0;
        while (getline(feedbackFile, feedbackNames[feedbackCount]))
        {
            getline(feedbackFile, feedbackComments[feedbackCount]);
            feedbackFile >> feedbackRatings[feedbackCount];
            feedbackFile.ignore();
            feedbackCount++;
        }
        feedbackFile.close();
    }
}

void saveMenuData()
{
    fstream menuFile("menu_data.txt", ios::out);
    if (menuFile.is_open())
    {
        for (int i = 0; i < menuCount; i++)
        {
            menuFile << menuIds[i] << " " << menuPrices[i] << " " << menuStocks[i] << endl;
            menuFile << menuNames[i] << endl;
        }
        menuFile.close();
    }
}

void saveOrderData()
{
    fstream orderFile("order_data.txt", ios::out);
    if (orderFile.is_open())
    {
        for (int i = 0; i < orderCount; i++)
        {
            orderFile << orderIds[i] << " " << orderTotals[i] << endl;
            orderFile << orderCustomers[i] << endl;
            orderFile << orderItems[i] << endl;
            orderFile << orderDates[i] << endl;
        }
        orderFile.close();
    }
}

void saveEmployeeData()
{
    fstream empFile("employee_data.txt", ios::out);
    if (empFile.is_open())
    {
        for (int i = 0; i < employeeCount; i++)
        {
            empFile << employeeIds[i] << " " << employeeSalaries[i] << endl;
            empFile << employeeNames[i] << endl;
            empFile << employeePositions[i] << endl;
        }
        empFile.close();
    }
}

void saveFeedbackData()
{
    fstream feedbackFile("feedback_data.txt", ios::out);
    if (feedbackFile.is_open())
    {
        for (int i = 0; i < feedbackCount; i++)
        {
            feedbackFile << feedbackNames[i] << endl;
            feedbackFile << feedbackComments[i] << endl;
            feedbackFile << feedbackRatings[i] << endl;
        }
        feedbackFile.close();
    }
}

// Customer functions
void orderCoffee()
{
    header();
    cout << "       ORDER COFFEE       " << endl;
    viewMenu();

    if (menuCount == 0)
    {
        cout << "No items available to order." << endl;
        return;
    }

    string customerName;
    cout << "Enter your name: " << endl;
    cin.ignore();
    getline(cin, customerName);

    string itemsOrdered = "";
    float total = 0;
    char moreItems = 'y';

    while (moreItems == 'y' || moreItems == 'Y')
    {
        int itemId, quantity;
        cout << "Enter item ID: ";
        cin >> itemId;

        bool found = false;
        for (int i = 0; i < menuCount; i++)
        {
            if (menuIds[i] == itemId)
            {
                found = true;
                cout << "Enter quantity: ";
                cin >> quantity;

                if (quantity <= menuStocks[i])
                {
                    menuStocks[i] -= quantity;
                    itemsOrdered += to_string(quantity) + "x " + menuNames[i] + ", ";
                    total += quantity * menuPrices[i];
                }
                else
                {
                    cout << "Not enough stock available!" << endl;
                }
                break;
            }
        }

        if (!found)
        {
            cout << "Invalid item ID!" << endl;
        }

        cout << "Add more items? (y/n): ";
        cin >> moreItems;
    }

    // Save the order
    orderIds[orderCount] = orderCount + 1;
    orderCustomers[orderCount] = customerName;
    orderItems[orderCount] = itemsOrdered;
    orderTotals[orderCount] = total;
    orderDates[orderCount] = "2025-05-26"; // You might want to use actual date here
    orderCount++;

    // Save order data to file immediately
    saveOrderData();
    saveMenuData(); // Update stock levels

    cout << "\nOrder placed successfully!\n";
    cout << "Total: $" << total << endl;
}

void viewMenu()
{
    header();
    cout << "      COFFEE MENU     \n\n";
    cout << "ID  Item                Price   Stock\n";
    cout << "------------------------------------\n";

    for (int i = 0; i < menuCount; i++)
    {
        cout << menuIds[i] << "   ";
        cout << menuNames[i];
        for (int s = menuNames[i].length(); s < 18; s++)
            cout << " ";
        cout << "$" << menuPrices[i] << "   ";
        cout << menuStocks[i] << endl;
    }
}

void viewOrderHistory()
{
    header();
    cout << "     ORDER HISTORY     \n\n";

    if (orderCount == 0)
    {
        cout << "No orders found.\n";
        return;
    }

    string customerName;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, customerName);

    bool found = false;
    for (int i = 0; i < orderCount; i++)
    {
        if (orderCustomers[i] == customerName)
        {
            found = true;
            cout << "Order #" << orderIds[i] << " - " << orderDates[i] << "\n";
            cout << "Items: " << orderItems[i] << "\n";
            cout << "Total: $" << orderTotals[i] << "\n\n";
        }
    }

    if (!found)
    {
        cout << "No orders found for " << customerName << ".\n";
    }
}

void loyaltyProgram()
{
    header();
    cout << "    LOYALTY PROGRAM    \n\n";

    string customerName;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, customerName);

    int orderTotal = 0;
    float spentTotal = 0;

    for (int i = 0; i < orderCount; i++)
    {
        if (orderCustomers[i] == customerName)
        {
            orderTotal++;
            spentTotal += orderTotals[i];
        }
    }

    cout << "\nHello, " << customerName << "!\n";
    cout << "You've placed " << orderTotal << " orders with us.\n";
    cout << "Total amount spent: $" << spentTotal << "\n";

    if (orderTotal >= 5)
    {
        cout << "\nCongratulations! You've earned a free coffee on your next visit!\n";
    }
}

void giveFeedback()
{
    header();
    cout << "    CUSTOMER FEEDBACK    \n\n";

    string name;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);

    string comment;
    cout << "Enter your feedback: ";
    getline(cin, comment);

    int rating;
    cout << "Enter rating (1-5): ";
    cin >> rating;

    feedbackNames[feedbackCount] = name;
    feedbackComments[feedbackCount] = comment;
    feedbackRatings[feedbackCount] = rating;
    feedbackCount++;

    // Save feedback to file immediately
    saveFeedbackData();

    cout << "\nThank you for your feedback!\n";
}

// Admin functions
void manageInventory()
{
    header();
    cout << "     INVENTORY MANAGEMENT     \n\n";

    viewMenu();

    int itemId;
    cout << "\nEnter item ID to update stock (0 to cancel): ";
    cin >> itemId;

    if (itemId == 0)
        return;

    bool found = false;
    for (int i = 0; i < menuCount; i++)
    {
        if (menuIds[i] == itemId)
        {
            found = true;
            int newStock;
            cout << "Current stock: " << menuStocks[i] << "\n";
            cout << "Enter new stock quantity: ";
            cin >> newStock;
            menuStocks[i] = newStock;
            cout << "Stock updated successfully!\n";

            // Save updated menu data to file
            saveMenuData();
            break;
        }
    }

    if (!found)
    {
        cout << "Item not found!\n";
    }
}

void manageMenu()
{
    header();
    cout << "     MENU MANAGEMENT     \n\n";
    cout << "1. Add new item\n";
    cout << "2. Remove item\n";
    cout << "3. View current menu\n";
    cout << "4. Back to main menu\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        if (menuCount >= MAX_ITEMS)
        {
            cout << "Maximum number of menu items reached!\n";
            return;
        }

        cout << "Enter item ID: ";
        cin >> menuIds[menuCount];
        cout << "Enter item name: ";
        cin.ignore();
        getline(cin, menuNames[menuCount]);
        cout << "Enter item price: ";
        cin >> menuPrices[menuCount];
        cout << "Enter initial stock: ";
        cin >> menuStocks[menuCount];

        menuCount++;

        // Save updated menu data to file
        saveMenuData();

        cout << "Item added successfully!\n";
    }
    else if (choice == 2)
    {
        viewMenu();
        int itemId;
        cout << "Enter item ID to remove (0 to cancel): ";
        cin >> itemId;

        if (itemId == 0)
            return;

        bool found = false;
        for (int i = 0; i < menuCount; i++)
        {
            if (menuIds[i] == itemId)
            {
                found = true;
                for (int j = i; j < menuCount - 1; j++)
                {
                    menuIds[j] = menuIds[j + 1];
                    menuNames[j] = menuNames[j + 1];
                    menuPrices[j] = menuPrices[j + 1];
                    menuStocks[j] = menuStocks[j + 1];
                }
                menuCount--;

                // Save updated menu data to file
                saveMenuData();

                cout << "Item removed successfully!\n";
                break;
            }
        }

        if (!found)
        {
            cout << "Item not found!\n";
        }
    }
    else if (choice == 3)
    {
        viewMenu();
    }
    else if (choice == 4)
    {
        return;
    }
    else
    {
        cout << "Invalid choice!\n";
    }
}

void viewOrders()
{
    header();
    cout << "     ALL ORDERS     \n\n";

    if (orderCount == 0)
    {
        cout << "No orders found.\n";
        return;
    }

    for (int i = 0; i < orderCount; i++)
    {
        cout << "Order #" << orderIds[i] << " - " << orderDates[i] << "\n";
        cout << "Customer: " << orderCustomers[i] << "\n";
        cout << "Items: " << orderItems[i] << "\n";
        cout << "Total: $" << orderTotals[i] << "\n\n";
    }

    float totalSales = 0;
    for (int i = 0; i < orderCount; i++)
    {
        totalSales += orderTotals[i];
    }
    cout << "Total sales: $" << totalSales << "\n";
}

void manageEmployees()
{
    header();
    cout << "     EMPLOYEE MANAGEMENT     \n\n";
    cout << "1. Add new employee\n";
    cout << "2. View all employees\n";
    cout << "3. Remove employee\n";
    cout << "4. Back to main menu\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        if (employeeCount >= MAX_EMPLOYEES)
        {
            cout << "Maximum number of employees reached!\n";
            return;
        }

        cout << "Enter employee ID: ";
        cin >> employeeIds[employeeCount];
        cout << "Enter employee name: ";
        cin.ignore();
        getline(cin, employeeNames[employeeCount]);
        cout << "Enter position: ";
        getline(cin, employeePositions[employeeCount]);
        cout << "Enter salary: ";
        cin >> employeeSalaries[employeeCount];

        employeeCount++;

        // Save updated employee data to file
        saveEmployeeData();

        cout << "Employee added successfully!\n";
    }
    else if (choice == 2)
    {
        cout << "ID  Name                Position        Salary\n";
        cout << "--------------------------------------------\n";
        for (int i = 0; i < employeeCount; i++)
        {
            cout << employeeIds[i] << "   ";
            cout << employeeNames[i];
            for (int s = employeeNames[i].length(); s < 18; s++)
                cout << " ";
            cout << employeePositions[i];
            for (int s = employeePositions[i].length(); s < 14; s++)
                cout << " ";
            cout << "$" << employeeSalaries[i] << endl;
        }
    }
    else if (choice == 3)
    {
        cout << "Enter employee ID to remove (0 to cancel): ";
        int empId;
        cin >> empId;

        if (empId == 0)
            return;

        bool found = false;
        for (int i = 0; i < employeeCount; i++)
        {
            if (employeeIds[i] == empId)
            {
                found = true;
                for (int j = i; j < employeeCount - 1; j++)
                {
                    employeeIds[j] = employeeIds[j + 1];
                    employeeNames[j] = employeeNames[j + 1];
                    employeePositions[j] = employeePositions[j + 1];
                    employeeSalaries[j] = employeeSalaries[j + 1];
                }
                employeeCount--;

                // Save updated employee data to file
                saveEmployeeData();

                cout << "Employee removed successfully!\n";
                break;
            }
        }

        if (!found)
        {
            cout << "Employee not found!\n";
        }
    }
    else if (choice == 4)
    {
        return;
    }
    else
    {
        cout << "Invalid choice!\n";
    }
}

void viewSalesReports()
{
    header();
    cout << "    SALES REPORTS    \n\n";

    float dailySales = 0;
    for (int i = 0; i < orderCount; i++)
    {
        dailySales += orderTotals[i];
    }

    cout << "Total orders today: " << orderCount << "\n";
    cout << "Total sales today: $" << dailySales << "\n\n";

    cout << "Most popular items:\n";
    for (int i = 0; i < menuCount; i++)
    {
        cout << menuNames[i] << " - Stock left: " << menuStocks[i] << "\n";
    }

    if (feedbackCount > 0)
    {
        cout << "\nRecent customer feedback:\n";
        for (int i = 0; i < feedbackCount && i < 5; i++)
        {
            cout << feedbackNames[i] << ": " << feedbackComments[i] << " (Rating: " << feedbackRatings[i] << "/5)\n";
        }
    }
}

// Common functions
string who()
{
    header();
    cout << "LOGIN (ADMIN/CUSTOMER): ";
    string username;
    cin >> username;
    return username;
}

void header()
{
    system("cls");
    cout << "**********************************************\n";
    cout << "              HALI'S   ODYESSY               \n";
    cout << "*********************************************\n\n";
}

void clearScreen()
{
    cout << "\nPress any key...";
    getch();
    system("cls");
}

void customerMenu()
{
    header();
    cout << "customer menu     \n\n";
    cout << "1. order coffee\n";
    cout << "2. view menu\n";
    cout << "3. order history\n";
    cout << "4. loyalty program\n";
    cout << "5. give feedback\n";
    cout << "6. exit\n";
    cout << "enter choice: ";
}

void adminMenu()
{
    header();
    cout << "admin menu     \n\n";
    cout << "1. coffee inventory\n";
    cout << "2. menu management\n";
    cout << "3. view orders\n";
    cout << "4. employee management\n";
    cout << "5. sales reports\n";
    cout << "6. exit\n";
    cout << "enter choice: ";
}