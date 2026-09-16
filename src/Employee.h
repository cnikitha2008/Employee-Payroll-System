#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
using namespace std;

class Employee
{
public:
    int employeeID;
    string name;
    int age;
    string gender;
    string department;
    string designation;
    string phone;
    string email;
    double basicSalary;

    void input();
    void display();
};

#endif