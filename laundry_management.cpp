#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Constants
const int MAX_CUSTOMERS = 100;
const int MAX_ORDERS = 100;

// Customer data
string customerIds[MAX_CUSTOMERS];
string customerNames[MAX_CUSTOMERS];
string customerPhones[MAX_CUSTOMERS];
string customerAddresses[MAX_CUSTOMERS];
int customerCount = 0;

// Order data
string orderNumbers[MAX_ORDERS];
string orderCustomerIds[MAX_ORDERS];
double orderWeights[MAX_ORDERS];
string orderServiceTypes[MAX_ORDERS];
double orderPrices[MAX_ORDERS];
string orderStatuses[MAX_ORDERS];
int orderCount = 0;

// Helper functions
int findCustomerIndexById(string id)
{
    for (int i = 0; i < customerCount; ++i)
    {
        if (customerIds[i] == id)
            return i;
    }
    return -1;
}

int findOrderIndexByNumber(string orderNumber)
{
    for (int i = 0; i < orderCount; ++i)
    {
        if (orderNumbers[i] == orderNumber)
            return i;
    }
    return -1;
}

// Customer Management
void addCustomer()
{
    if (customerCount >= MAX_CUSTOMERS)
    {
        cout << "Customer list is full!\n";
        return;
    }

    cout << "Enter Customer ID: ";
    cin >> customerIds[customerCount];
    cout << "Enter Customer Name: ";
    cin >> customerNames[customerCount];
    cout << "Enter Phone Number: ";
    cin >> customerPhones[customerCount];
    cout << "Enter Address (optional): ";
    cin >> customerAddresses[customerCount];
    customerCount++;
    cout << "Customer added successfully!\n";
}

void viewCustomers()
{
    cout << "\nCustomer List:\n";
    for (int i = 0; i < customerCount; ++i)
    {
        cout << "ID: " << customerIds[i] << ", Name: " << customerNames[i]
             << ", Phone: " << customerPhones[i] << ", Address: " << customerAddresses[i] << "\n";
    }
}

void searchCustomer()
{
    string id;
    cout << "Enter Customer ID to search: ";
    cin >> id;
    int index = findCustomerIndexById(id);
    if (index != -1)
    {
        cout << "Found Customer - ID: " << customerIds[index] << ", Name: " << customerNames[index]
             << ", Phone: " << customerPhones[index] << ", Address: " << customerAddresses[index] << "\n";
    }
    else
    {
        cout << "Customer not found.\n";
    }
}

// Order Management
void addOrder()
{
    if (orderCount >= MAX_ORDERS)
    {
        cout << "Order list is full!\n";
        return;
    }

    cout << "Enter Order Number: ";
    cin >> orderNumbers[orderCount];
    cout << "Enter Customer ID: ";
    cin >> orderCustomerIds[orderCount];
    if (findCustomerIndexById(orderCustomerIds[orderCount]) == -1)
    {
        cout << "Customer not found. Please add the customer first.\n";
        return;
    }
    cout << "Enter Laundry Weight (kg): ";
    cin >> orderWeights[orderCount];

    while (true)
    {
        cout << "Enter Service Type (normal/express): ";
        cin >> orderServiceTypes[orderCount];
        if (orderServiceTypes[orderCount] == "normal" || orderServiceTypes[orderCount] == "express")
        {
            break;
        }
        else
        {
            cout << "Invalid Service Type! Please enter 'normal' or 'express' only.\n";
        }
    }

    cout << "Enter Total Price: ";
    cin >> orderPrices[orderCount];
    orderStatuses[orderCount] = "Diterima";
    orderCount++;
    cout << "Order added successfully!\n";
}

void updateOrderStatus()
{
    string orderNumber;
    cout << "Enter Order Number to update: ";
    cin >> orderNumber;
    int index = findOrderIndexByNumber(orderNumber);
    if (index != -1)
    {
        cout << "Enter new status (Diterima/Dicuci/Selesai): ";
        cin >> orderStatuses[index];
        cout << "Order status updated successfully!\n";
    }
    else
    {
        cout << "Order not found.\n";
    }
}

void printOrderTableHeader()
{
    cout << left << setw(15) << "Order Number"
         << setw(15) << "Customer ID"
         << setw(10) << "Weight(kg)"
         << setw(15) << "Service Type"
         << setw(15) << "Total Price"
         << setw(15) << "Status" << "\n";
    cout << string(75, '-') << "\n";
}

void viewAllOrders()
{
    if (orderCount == 0)
    {
        cout << "No orders available.\n";
        return;
    }

    cout << "\nAll Orders:\n";
    printOrderTableHeader();

    for (int i = 0; i < orderCount; ++i)
    {
        cout << left << setw(15) << orderNumbers[i]
             << setw(15) << orderCustomerIds[i]
             << setw(10) << orderWeights[i]
             << setw(15) << orderServiceTypes[i]
             << setw(15) << fixed << setprecision(2) << orderPrices[i]
             << setw(15) << orderStatuses[i] << "\n";
    }
    cout << string(75, '=') << "\n";
}

void viewActiveOrders()
{
    cout << "\nActive Orders:\n";
    for (int i = 0; i < orderCount; ++i)
    {
        if (orderStatuses[i] != "Selesai")
        {
            cout << "Order Number: " << orderNumbers[i] << ", Customer ID: " << orderCustomerIds[i]
                 << ", Weight: " << orderWeights[i] << "kg, Service Type: " << orderServiceTypes[i]
                 << ", Total Price: " << orderPrices[i] << ", Status: " << orderStatuses[i] << "\n";
        }
    }
}

// Service Operations
void processOrder()
{
    string orderNumber;
    cout << "Enter Order Number to process: ";
    cin >> orderNumber;
    int index = findOrderIndexByNumber(orderNumber);
    if (index != -1)
    {
        cout << "Order processed. Weight: " << orderWeights[index] << "kg, Total Price: " << orderPrices[index] << "\n";
        cout << "Printing receipt...\n";
        cout << "--- Receipt ---\nOrder Number: " << orderNumbers[index] << "\nCustomer ID: " << orderCustomerIds[index]
             << "\nWeight: " << orderWeights[index] << "kg\nTotal Price: " << orderPrices[index] << "\n";
    }
    else
    {
        cout << "Order not found.\n";
    }
}

void viewLaundryQueue()
{
    cout << "\nLaundry Queue:\n";
    for (int i = 0; i < orderCount; ++i)
    {
        if (orderStatuses[i] == "Diterima")
        {
            cout << "Order Number: " << orderNumbers[i] << ", Customer ID: " << orderCustomerIds[i] << "\n";
        }
    }
}

void updateLaundryStatus()
{
    string orderNumber;
    cout << "Enter Order Number to update laundry status: ";
    cin >> orderNumber;
    int index = findOrderIndexByNumber(orderNumber);
    if (index != -1)
    {
        cout << "Enter new laundry status (Diterima/Dicuci/Selesai): ";
        cin >> orderStatuses[index];
        cout << "Laundry status updated successfully!\n";
    }
    else
    {
        cout << "Order not found.\n";
    }
}

// Report Management
void viewDailyReport()
{
    int totalOrders = 0;
    double totalIncome = 0;
    double totalWeight = 0;

    for (int i = 0; i < orderCount; ++i)
    {
        totalOrders++;
        totalIncome += orderPrices[i];
        totalWeight += orderWeights[i];
    }

    cout << "\nDaily Report:\n";
    cout << "Total Orders: " << totalOrders << "\nTotal Income: " << totalIncome << "\nTotal Laundry Weight: " << totalWeight << "kg\n";
}

void checkOrderStatusByCustomer()
{
    string customerId;
    cout << "Enter Customer ID to check order status: ";
    cin >> customerId;

    cout << "\nOrders for Customer ID " << customerId << ":\n";
    for (int i = 0; i < orderCount; ++i)
    {
        if (orderCustomerIds[i] == customerId)
        {
            cout << "Order Number: " << orderNumbers[i] << ", Status: " << orderStatuses[i] << "\n";
        }
    }
}

// Main Menu
void adminMenu()
{
    int choice;
    do
    {
        cout << "\nAdmin Menu:\n";
        cout << "1. Customer Management\n2. Order Management\n3. View All Orders\n4. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            do
            {
                cout << "\nCustomer Management:\n";
                cout << "1. Add Customer\n2. View Customers\n3. Search Customer\n4. Back to Admin Menu\n";
                cout << "Enter your choice: ";
                cin >> choice;
                if (choice == 1)
                    addCustomer();
                else if (choice == 2)
                    viewCustomers();
                else if (choice == 3)
                    searchCustomer();
                else if (choice == 4)
                    adminMenu();
                else
                    cout << "Invalid choice.\n";
            } while (choice != 4);
            break;
        case 2:
            do
            {
                cout << "\nOrder Management:\n";
                cout << "1. Add Order\n2. Update Order Status\n3. View Active Orders\n4. Back to Admin Menu\n";
                cout << "Enter your choice: ";
                cin >> choice;
                if (choice == 1)
                    addOrder();
                else if (choice == 2)
                    updateOrderStatus();
                else if (choice == 3)
                    viewActiveOrders();
                else if (choice == 4)
                    adminMenu();
                else
                    cout << "Invalid choice.\n";
            } while (choice != 4);
            break;
        case 3:
            viewAllOrders();
            break;
        case 4:
            cout << "Returning to Role Selection...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

void staffMenu()
{
    int choice;
    do
    {
        cout << "\nStaff Menu:\n";
        cout << "1. Service Operations\n2. Report Management\n3. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            do
            {
                cout << "\nService Operations:\n";
                cout << "1. Process Order\n2. View Laundry Queue\n3. Update Laundry Status\n4. Back to Staff Menu\n";
                cout << "Enter your choice: ";
                cin >> choice;
                if (choice == 1)
                    processOrder();
                else if (choice == 2)
                    viewLaundryQueue();
                else if (choice == 3)
                    updateLaundryStatus();
                else if (choice == 4)
                    staffMenu();
                else
                    cout << "Invalid choice.\n";
            } while (choice != 4);
            break;
        case 2:
            do
            {
                cout << "\nReport Management:\n";
                cout << "1. View Daily Report\n2. Check Order Status by Customer\n3. Back to Staff Menu\n";
                cout << "Enter your choice: ";
                cin >> choice;
                if (choice == 1)
                    viewDailyReport();
                else if (choice == 2)
                    checkOrderStatusByCustomer();
                else if (choice == 3)
                    staffMenu();
                else
                    cout << "Invalid choice.\n";
            } while (choice != 3);
            break;
        case 3:
            cout << "Returning to Role Selection...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
}

int main()
{
    int role;
    do
    {
        cout << "Welcome to Laundry Management System\n";
        cout << "Select Role:\n1. Admin\n2. Staff\n3. Exit\n";
        cout << "Enter your role: ";
        cin >> role;

        if (role == 1)
        {
            adminMenu();
        }
        else if (role == 2)
        {
            staffMenu();
        }
        else if (role == 3)
        {
            cout << "Exiting system...\n";
        }
        else
        {
            cout << "Invalid role. Please try again.\n";
        }
    } while (role != 3);

    return 0;
}
