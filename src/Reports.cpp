#include "Reports.h"
#include <iostream>
#include <map>

using namespace std;

void Reports::totalEmployees(vector<Employee> employees)
{
    cout << endl;
    cout << "Total Employees: " << employees.size() << endl;
}

void Reports::highestSalary(vector<Employee> employees)
{
    if (employees.empty())
    {
        cout << "No employees found!" << endl;
        return;
    }

    Employee highest = employees[0];

    for (Employee emp : employees)
    {
        if (emp.basicSalary > highest.basicSalary)
        {
            highest = emp;
        }
    }

    cout << endl;
    cout << "Highest Salary" << endl;
    cout << "--------------" << endl;
    cout << "Employee ID: " << highest.employeeID << endl;
    cout << "Name: " << highest.name << endl;
    cout << "Basic Salary: " << highest.basicSalary << endl;
}

void Reports::lowestSalary(vector<Employee> employees)
{
    if (employees.empty())
    {
        cout << "No employees found!" << endl;
        return;
    }

    Employee lowest = employees[0];

    for (Employee emp : employees)
    {
        if (emp.basicSalary < lowest.basicSalary)
        {
            lowest = emp;
        }
    }

    cout << endl;
    cout << "Lowest Salary" << endl;
    cout << "-------------" << endl;
    cout << "Employee ID: " << lowest.employeeID << endl;
    cout << "Name: " << lowest.name << endl;
    cout << "Basic Salary: " << lowest.basicSalary << endl;
}

void Reports::averageSalary(vector<Employee> employees)
{
    if (employees.empty())
    {
        cout << "No employees found!" << endl;
        return;
    }

    double total = 0;

    for (Employee emp : employees)
    {
        total += emp.basicSalary;
    }

    double average = total / employees.size();

    cout << endl;
    cout << "Average Basic Salary: " << average << endl;
}

void Reports::departmentWiseCount(vector<Employee> employees)
{
    if (employees.empty())
    {
        cout << "No employees found!" << endl;
        return;
    }

    map<string, int> departmentCount;

    for (Employee emp : employees)
    {
        departmentCount[emp.department]++;
    }

    cout << endl;
    cout << "DEPARTMENT-WISE EMPLOYEE COUNT" << endl;
    cout << "==============================" << endl;

    for (auto item : departmentCount)
    {
        cout << item.first << ": " << item.second << endl;
    }
}

void Reports::salaryChart(vector<Employee> employees)
{
    if (employees.empty())
    {
        cout << "No employees found!" << endl;
        return;
    }

    cout << endl;
    cout << "SALARY CHART" << endl;
    cout << "============" << endl;

    for (Employee emp : employees)
    {
        cout << emp.name << " : ";

        int bars = emp.basicSalary / 5000;

        for (int i = 0; i < bars; i++)
        {
            cout << "*";
        }

        cout << " " << emp.basicSalary << endl;
    }
}

void Reports::displayReports(vector<Employee> employees)
{
    int choice;

    while (true)
    {
        cout << endl;
        cout << "=================================" << endl;
        cout << "          REPORTS MENU" << endl;
        cout << "=================================" << endl;

        cout << "1. Total Employees" << endl;
        cout << "2. Highest Salary" << endl;
        cout << "3. Lowest Salary" << endl;
        cout << "4. Average Salary" << endl;
        cout << "5. Department-wise Count" << endl;
        cout << "6. Salary Chart" << endl;
        cout << "7. Back" << endl;

        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            totalEmployees(employees);
        }
        else if (choice == 2)
        {
            highestSalary(employees);
        }
        else if (choice == 3)
        {
            lowestSalary(employees);
        }
        else if (choice == 4)
        {
            averageSalary(employees);
        }
        else if (choice == 5)
        {
            departmentWiseCount(employees);
        }
        else if (choice == 6)
        {
            salaryChart(employees);
        }
        else if (choice == 7)
        {
            break;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }
}