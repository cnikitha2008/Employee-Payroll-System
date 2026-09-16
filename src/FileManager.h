#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include "Employee.h"

using namespace std;

class FileManager
{
public:
    vector<Employee> loadEmployees();
    void saveEmployees(vector<Employee> employees);
};

#endif