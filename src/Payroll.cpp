#include "Payroll.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Payroll::Payroll()
{
    hraRate = 0.20;
    highHraRate = 0.25;
    daRate = 0.10;
    bonusRate = 0.05;
    pfRate = 0.12;
    taxRate = 0.10;

    loadRules();
}

void Payroll::loadRules()
{
    ifstream file("data/payroll_rules.csv");

    if (!file.is_open())
    {
        saveRules();
        return;
    }

    string line;
    string key;
    string value;

    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);

        getline(ss, key, ',');
        getline(ss, value, ',');

        double rate = stod(value) / 100;

        if (key == "HRA")
            hraRate = rate;
        else if (key == "HighHRA")
            highHraRate = rate;
        else if (key == "DA")
            daRate = rate;
        else if (key == "Bonus")
            bonusRate = rate;
        else if (key == "PF")
            pfRate = rate;
        else if (key == "Tax")
            taxRate = rate;
    }

    file.close();
}

void Payroll::saveRules()
{
    ofstream file("data/payroll_rules.csv");

    file << "Rule,Percentage\n";
    file << "HRA," << hraRate * 100 << "\n";
    file << "HighHRA," << highHraRate * 100 << "\n";
    file << "DA," << daRate * 100 << "\n";
    file << "Bonus," << bonusRate * 100 << "\n";
    file << "PF," << pfRate * 100 << "\n";
    file << "Tax," << taxRate * 100 << "\n";

    file.close();
}

double Payroll::calculateHRA(double basicSalary)
{
    if (basicSalary < 40000)
        return basicSalary * hraRate;
    else
        return basicSalary * highHraRate;
}

double Payroll::calculateDA(double basicSalary)
{
    return basicSalary * daRate;
}

double Payroll::calculateBonus(double basicSalary)
{
    return basicSalary * bonusRate;
}

double Payroll::calculatePF(double basicSalary)
{
    return basicSalary * pfRate;
}

double Payroll::calculateTax(double grossSalary)
{
    if (grossSalary <= 50000)
        return 0;
    else
        return grossSalary * taxRate;
}

double Payroll::calculateNetSalary(Employee emp)
{
    double hra = calculateHRA(emp.basicSalary);
    double da = calculateDA(emp.basicSalary);
    double bonus = calculateBonus(emp.basicSalary);

    double grossSalary = emp.basicSalary + hra + da + bonus;

    double pf = calculatePF(emp.basicSalary);
    double tax = calculateTax(grossSalary);

    return grossSalary - pf - tax;
}

void Payroll::displayPayslip(Employee emp)
{
    double hra = calculateHRA(emp.basicSalary);
    double da = calculateDA(emp.basicSalary);
    double bonus = calculateBonus(emp.basicSalary);

    double grossSalary = emp.basicSalary + hra + da + bonus;

    double pf = calculatePF(emp.basicSalary);
    double tax = calculateTax(grossSalary);

    double netSalary = grossSalary - pf - tax;

    cout << endl;
    cout << "EMPLOYEE PAYSLIP" << endl;
    cout << "================" << endl;

    cout << "Employee ID: " << emp.employeeID << endl;
    cout << "Name: " << emp.name << endl;
    cout << "Department: " << emp.department << endl;
    cout << "Designation: " << emp.designation << endl;

    cout << endl;

    cout << "Basic Salary: " << emp.basicSalary << endl;
    cout << "HRA: " << hra << endl;
    cout << "DA: " << da << endl;
    cout << "Bonus: " << bonus << endl;
    cout << "Gross Salary: " << grossSalary << endl;

    cout << endl;

    cout << "PF: " << pf << endl;
    cout << "Tax: " << tax << endl;
    cout << "Net Salary: " << netSalary << endl;
}

void Payroll::displayRules()
{
    cout << endl;
    cout << "CURRENT PAYROLL RULES" << endl;
    cout << "=====================" << endl;

    cout << "HRA (Basic < 40000): " << hraRate * 100 << "%" << endl;
    cout << "HRA (Basic >= 40000): " << highHraRate * 100 << "%" << endl;
    cout << "DA: " << daRate * 100 << "%" << endl;
    cout << "Bonus: " << bonusRate * 100 << "%" << endl;
    cout << "PF: " << pfRate * 100 << "%" << endl;
    cout << "Tax (Gross > 50000): " << taxRate * 100 << "%" << endl;
}

void Payroll::changeRules()
{
    int choice;
    double newRate;

    cout << endl;
    cout << "CHANGE PAYROLL RULE" << endl;
    cout << "===================" << endl;

    cout << "1. HRA for Basic < 40000" << endl;
    cout << "2. HRA for Basic >= 40000" << endl;
    cout << "3. DA" << endl;
    cout << "4. Bonus" << endl;
    cout << "5. PF" << endl;
    cout << "6. Tax" << endl;
    cout << "7. Back" << endl;

    cout << endl;
    cout << "Enter your choice: ";

    while (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid number: ";
    }

    if (choice == 7)
    {
        return;
    }

    if (choice < 1 || choice > 6)
    {
        cout << "Invalid choice!" << endl;
        return;
    }

    cout << "Enter new percentage: ";

    while (!(cin >> newRate) || newRate < 0 || newRate > 100)
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Enter a percentage between 0 and 100: ";
    }

    if (choice == 1)
        hraRate = newRate / 100;
    else if (choice == 2)
        highHraRate = newRate / 100;
    else if (choice == 3)
        daRate = newRate / 100;
    else if (choice == 4)
        bonusRate = newRate / 100;
    else if (choice == 5)
        pfRate = newRate / 100;
    else if (choice == 6)
        taxRate = newRate / 100;

    saveRules();

    cout << endl;
    cout << "Payroll rule updated successfully!" << endl;
}