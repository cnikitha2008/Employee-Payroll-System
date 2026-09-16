#include "FileManager.h"
#include <fstream>
#include <sstream>

using namespace std;

vector<Employee> FileManager::loadEmployees()
{
    vector<Employee> employees;

    ifstream file("data/employees.csv");

    string line;

    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);
        string value;

        Employee emp;

        getline(ss, value, ',');
        emp.employeeID = stoi(value);

        getline(ss, emp.name, ',');

        getline(ss, value, ',');
        emp.age = stoi(value);

        getline(ss, emp.gender, ',');
        getline(ss, emp.department, ',');
        getline(ss, emp.designation, ',');
        getline(ss, emp.phone, ',');
        getline(ss, emp.email, ',');

        getline(ss, value, ',');
        emp.basicSalary = stod(value);

        employees.push_back(emp);
    }

    file.close();

    return employees;
}

void FileManager::saveEmployees(vector<Employee> employees)
{
    ofstream file("data/employees.csv");

    file << "EmployeeID,Name,Age,Gender,Department,Designation,Phone,Email,BasicSalary\n";

    for (Employee emp : employees)
    {
        file << emp.employeeID << ",";
        file << emp.name << ",";
        file << emp.age << ",";
        file << emp.gender << ",";
        file << emp.department << ",";
        file << emp.designation << ",";
        file << emp.phone << ",";
        file << emp.email << ",";
        file << emp.basicSalary << "\n";
    }

    file.close();
}