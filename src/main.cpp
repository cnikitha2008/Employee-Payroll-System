#include <iostream>
#include <vector>
#include <windows.h>
#include "Employee.h"
#include "FileManager.h"
#include "Payroll.h"
#include "Reports.h"

using namespace std;

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void showTitle()
{
    setColor(11);

    cout << endl;
    cout << "============================================" << endl;
    cout << "          EMPLOYEE PAYROLL SYSTEM" << endl;
    cout << "============================================" << endl;

    setColor(7);
}

int main()
{
    FileManager manager;

    vector<Employee> employees = manager.loadEmployees();

    int choice;

    while (true)
    {
        showTitle();

        setColor(10);
        cout << "1. Add Employee" << endl;
        cout << "2. View Employees" << endl;
        cout << "3. Search Employee" << endl;
        cout << "4. Update Employee" << endl;
        cout << "5. Delete Employee" << endl;
        cout << "6. Generate Payroll" << endl;
        cout << "7. Generate Reports" << endl;
        cout << "8. Exit" << endl;

        setColor(7);

        cout << endl;
        setColor(14);
        cout << "Enter your choice: ";
        setColor(7);

        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');

            setColor(12);
            cout << "Please enter a number: ";
            setColor(7);
        }

        if (choice == 1)
        {
            Employee newEmployee;

            setColor(11);
            cout << endl;
            cout << "ADD EMPLOYEE" << endl;
            cout << "============" << endl;
            setColor(7);

            newEmployee.input();

            bool idExists = false;

            for (Employee emp : employees)
            {
                if (emp.employeeID == newEmployee.employeeID)
                {
                    idExists = true;
                    break;
                }
            }

            if (idExists)
            {
                setColor(12);
                cout << endl;
                cout << "Employee ID already exists!" << endl;
                cout << "Employee was not added." << endl;
                setColor(7);
            }
            else
            {
                employees.push_back(newEmployee);
                manager.saveEmployees(employees);

                setColor(10);
                cout << endl;
                cout << "Employee added successfully!" << endl;
                setColor(7);
            }
        }

        else if (choice == 2)
        {
            setColor(11);
            cout << endl;
            cout << "EMPLOYEE LIST" << endl;
            cout << "=============" << endl;
            setColor(7);

            if (employees.empty())
            {
                setColor(12);
                cout << "No employees found!" << endl;
                setColor(7);
            }
            else
            {
                for (Employee emp : employees)
                {
                    emp.display();
                    cout << "------------------------" << endl;
                }
            }
        }

        else if (choice == 3)
        {
            int searchID;

            setColor(11);
            cout << endl;
            cout << "SEARCH EMPLOYEE" << endl;
            cout << "===============" << endl;
            setColor(7);

            cout << "Enter Employee ID: ";

            while (!(cin >> searchID))
            {
                cin.clear();
                cin.ignore(1000, '\n');

                setColor(12);
                cout << "Please enter a valid number: ";
                setColor(7);
            }

            bool found = false;

            for (Employee emp : employees)
            {
                if (emp.employeeID == searchID)
                {
                    cout << endl;
                    emp.display();

                    found = true;
                    break;
                }
            }

            if (!found)
            {
                setColor(12);
                cout << endl;
                cout << "Employee not found!" << endl;
                setColor(7);
            }
        }

        else if (choice == 4)
        {
            int updateID;
            int updateChoice;

            setColor(11);
            cout << endl;
            cout << "UPDATE EMPLOYEE" << endl;
            cout << "===============" << endl;
            setColor(7);

            cout << "Enter Employee ID: ";

            while (!(cin >> updateID))
            {
                cin.clear();
                cin.ignore(1000, '\n');

                setColor(12);
                cout << "Please enter a valid number: ";
                setColor(7);
            }

            bool found = false;

            for (Employee &emp : employees)
            {
                if (emp.employeeID == updateID)
                {
                    found = true;

                    cout << endl;
                    cout << "Current Employee Details" << endl;
                    cout << "------------------------" << endl;

                    emp.display();

                    cout << endl;
                    cout << "What do you want to update?" << endl;

                    cout << "1. Name" << endl;
                    cout << "2. Age" << endl;
                    cout << "3. Gender" << endl;
                    cout << "4. Department" << endl;
                    cout << "5. Designation" << endl;
                    cout << "6. Phone" << endl;
                    cout << "7. Email" << endl;
                    cout << "8. Basic Salary" << endl;
                    cout << "9. Cancel" << endl;

                    cout << endl;
                    cout << "Enter your choice: ";

                    while (!(cin >> updateChoice))
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');

                        setColor(12);
                        cout << "Please enter a valid number: ";
                        setColor(7);
                    }

                    cin.ignore();

                    if (updateChoice == 1)
                    {
                        cout << "Enter new Name: ";
                        getline(cin, emp.name);

                        while (emp.name.empty())
                        {
                            cout << "Name cannot be empty. Enter again: ";
                            getline(cin, emp.name);
                        }
                    }

                    else if (updateChoice == 2)
                    {
                        cout << "Enter new Age: ";

                        while (!(cin >> emp.age) ||
                               emp.age < 18 ||
                               emp.age > 100)
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');

                            cout << "Enter a valid age between 18 and 100: ";
                        }
                    }

                    else if (updateChoice == 3)
                    {
                        cout << "Enter new Gender: ";
                        getline(cin, emp.gender);
                    }

                    else if (updateChoice == 4)
                    {
                        cout << "Enter new Department: ";
                        getline(cin, emp.department);

                        while (emp.department.empty())
                        {
                            cout << "Department cannot be empty. Enter again: ";
                            getline(cin, emp.department);
                        }
                    }

                    else if (updateChoice == 5)
                    {
                        cout << "Enter new Designation: ";
                        getline(cin, emp.designation);

                        while (emp.designation.empty())
                        {
                            cout << "Designation cannot be empty. Enter again: ";
                            getline(cin, emp.designation);
                        }
                    }

                    else if (updateChoice == 6)
                    {
                        cout << "Enter new Phone: ";
                        getline(cin, emp.phone);

                        while (emp.phone.length() != 10)
                        {
                            cout << "Phone must contain 10 digits. Enter again: ";
                            getline(cin, emp.phone);
                        }
                    }

                    else if (updateChoice == 7)
                    {
                        cout << "Enter new Email: ";
                        getline(cin, emp.email);

                        while (emp.email.find('@') == string::npos ||
                               emp.email.find('.') == string::npos)
                        {
                            cout << "Enter a valid email address: ";
                            getline(cin, emp.email);
                        }
                    }

                    else if (updateChoice == 8)
                    {
                        cout << "Enter new Basic Salary: ";

                        while (!(cin >> emp.basicSalary) ||
                               emp.basicSalary <= 0)
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');

                            cout << "Enter a valid salary greater than 0: ";
                        }
                    }

                    else if (updateChoice == 9)
                    {
                        cout << "Update cancelled." << endl;
                        break;
                    }

                    else
                    {
                        setColor(12);
                        cout << "Invalid choice!" << endl;
                        setColor(7);
                        break;
                    }

                    if (updateChoice >= 1 && updateChoice <= 8)
                    {
                        manager.saveEmployees(employees);

                        setColor(10);
                        cout << endl;
                        cout << "Employee updated successfully!" << endl;
                        setColor(7);

                        cout << endl;
                        cout << "Updated Employee Details" << endl;
                        cout << "------------------------" << endl;

                        emp.display();
                    }

                    break;
                }
            }

            if (!found)
            {
                setColor(12);
                cout << endl;
                cout << "Employee not found!" << endl;
                setColor(7);
            }
        }

        else if (choice == 5)
        {
            int deleteID;

            setColor(11);
            cout << endl;
            cout << "DELETE EMPLOYEE" << endl;
            cout << "===============" << endl;
            setColor(7);

            cout << "Enter Employee ID: ";

            while (!(cin >> deleteID))
            {
                cin.clear();
                cin.ignore(1000, '\n');

                setColor(12);
                cout << "Please enter a valid number: ";
                setColor(7);
            }

            bool found = false;

            for (int i = 0; i < employees.size(); i++)
            {
                if (employees[i].employeeID == deleteID)
                {
                    found = true;

                    employees.erase(employees.begin() + i);

                    manager.saveEmployees(employees);

                    setColor(10);
                    cout << endl;
                    cout << "Employee deleted successfully!" << endl;
                    setColor(7);

                    break;
                }
            }

            if (!found)
            {
                setColor(12);
                cout << endl;
                cout << "Employee not found!" << endl;
                setColor(7);
            }
        }

        else if (choice == 6)
        {
            int payrollChoice;

            setColor(11);
            cout << endl;
            cout << "PAYROLL MANAGEMENT" << endl;
            cout << "==================" << endl;
            setColor(7);

            cout << "1. Generate Individual Payslip" << endl;
            cout << "2. Generate Full Payroll Report" << endl;
            cout << "3. View Payroll Rules" << endl;
            cout << "4. Change Payroll Rules" << endl;
            cout << "5. Back" << endl;

            cout << endl;
            cout << "Enter your choice: ";

            while (!(cin >> payrollChoice))
            {
                cin.clear();
                cin.ignore(1000, '\n');

                setColor(12);
                cout << "Please enter a valid number: ";
                setColor(7);
            }

            Payroll payroll;

            if (payrollChoice == 1)
            {
                int searchID;

                cout << endl;
                cout << "Enter Employee ID: ";

                while (!(cin >> searchID))
                {
                    cin.clear();
                    cin.ignore(1000, '\n');

                    setColor(12);
                    cout << "Please enter a valid number: ";
                    setColor(7);
                }

                bool found = false;

                for (Employee emp : employees)
                {
                    if (emp.employeeID == searchID)
                    {
                        payroll.displayPayslip(emp);
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    setColor(12);
                    cout << endl;
                    cout << "Employee not found!" << endl;
                    setColor(7);
                }
            }

            else if (payrollChoice == 2)
            {
                setColor(11);
                cout << endl;
                cout << "FULL PAYROLL REPORT" << endl;
                cout << "===================" << endl;
                setColor(7);

                if (employees.empty())
                {
                    cout << "No employees found!" << endl;
                }
                else
                {
                    for (Employee emp : employees)
                    {
                        payroll.displayPayslip(emp);

                        cout << endl;
                        cout << "------------------------" << endl;
                    }
                }
            }

            else if (payrollChoice == 3)
            {
                payroll.displayRules();
            }

            else if (payrollChoice == 4)
            {
                payroll.changeRules();
            }

            else if (payrollChoice == 5)
            {
                cout << "Going back..." << endl;
            }

            else
            {
                setColor(12);
                cout << "Invalid choice!" << endl;
                setColor(7);
            }
        }

        else if (choice == 7)
        {
            Reports reports;

            reports.displayReports(employees);
        }

        else if (choice == 8)
        {
            setColor(14);
            cout << endl;
            cout << "Exiting Employee Payroll System..." << endl;
            setColor(7);

            break;
        }

        else
        {
            setColor(12);
            cout << endl;
            cout << "Invalid choice!" << endl;
            setColor(7);
        }
    }

    return 0;
}