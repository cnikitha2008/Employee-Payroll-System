#include "Employee.h"
#include <iostream>

using namespace std;

void Employee::input()
{
    cout << "Enter Employee ID: ";

    while (!(cin >> employeeID) || employeeID <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Enter a valid positive Employee ID: ";
    }

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    while (name.empty())
    {
        cout << "Name cannot be empty. Enter again: ";
        getline(cin, name);
    }

    cout << "Enter Age: ";

    while (!(cin >> age) || age < 18 || age > 100)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Enter a valid age between 18 and 100: ";
    }

    cin.ignore();

    cout << "Enter Gender: ";
    getline(cin, gender);

    cout << "Enter Department: ";
    getline(cin, department);

    while (department.empty())
    {
        cout << "Department cannot be empty. Enter again: ";
        getline(cin, department);
    }

    cout << "Enter Designation: ";
    getline(cin, designation);

    while (designation.empty())
    {
        cout << "Designation cannot be empty. Enter again: ";
        getline(cin, designation);
    }

    cout << "Enter Phone: ";
    getline(cin, phone);

    while (phone.length() != 10)
    {
        cout << "Phone must contain 10 digits. Enter again: ";
        getline(cin, phone);
    }

    cout << "Enter Email: ";
    getline(cin, email);

    while (email.find('@') == string::npos ||
           email.find('.') == string::npos)
    {
        cout << "Enter a valid email address: ";
        getline(cin, email);
    }

    cout << "Enter Basic Salary: ";

    while (!(cin >> basicSalary) || basicSalary <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Enter a valid salary greater than 0: ";
    }
}

void Employee::display()
{
    cout << "Employee ID: " << employeeID << endl;
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Gender: " << gender << endl;
    cout << "Department: " << department << endl;
    cout << "Designation: " << designation << endl;
    cout << "Phone: " << phone << endl;
    cout << "Email: " << email << endl;
    cout << "Basic Salary: " << basicSalary << endl;
}