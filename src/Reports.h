#ifndef REPORTS_H
#define REPORTS_H

#include <vector>
#include "Employee.h"

using namespace std;

class Reports
{
public:
    void totalEmployees(vector<Employee> employees);
    void highestSalary(vector<Employee> employees);
    void lowestSalary(vector<Employee> employees);
    void averageSalary(vector<Employee> employees);
    void departmentWiseCount(vector<Employee> employees);
    void salaryChart(vector<Employee> employees);

    void displayReports(vector<Employee> employees);
};

#endif