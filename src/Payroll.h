#ifndef PAYROLL_H
#define PAYROLL_H

#include "Employee.h"

using namespace std;

class Payroll
{
public:
    double hraRate;
    double highHraRate;
    double daRate;
    double bonusRate;
    double pfRate;
    double taxRate;

    Payroll();

    void loadRules();
    void saveRules();

    double calculateHRA(double basicSalary);
    double calculateDA(double basicSalary);
    double calculateBonus(double basicSalary);
    double calculatePF(double basicSalary);
    double calculateTax(double grossSalary);
    double calculateNetSalary(Employee emp);

    void displayPayslip(Employee emp);
    void displayRules();
    void changeRules();
};

#endif