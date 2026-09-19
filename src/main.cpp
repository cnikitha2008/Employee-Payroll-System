#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Employee.h"
#include "FileManager.h"
#include "Payroll.h"
#include "Reports.h"

#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <map>
#include <cstring>
#include <cstdio>
#include <cctype>

using namespace std;

ImFont* boldFont = nullptr;

enum Screen
{
    DASHBOARD, EMPLOYEE_MENU, ADD_EMPLOYEE, VIEW_EMPLOYEES,
    SEARCH_EMPLOYEE, UPDATE_EMPLOYEE, DELETE_EMPLOYEE,
    PAYROLL_MENU, PAYSLIP, FULL_PAYROLL, PAYROLL_RULES, CHANGE_RULES,
    REPORTS_MENU, REPORT_TOTAL, REPORT_HIGHEST, REPORT_LOWEST,
    REPORT_AVERAGE, REPORT_DEPARTMENT, REPORT_SALARY_CHART
};

bool digits(const char* s)
{
    if (!s || !s[0]) return false;
    for (int i = 0; s[i]; i++)
        if (!isdigit((unsigned char)s[i])) return false;
    return true;
}

void center(float width)
{
    float available = ImGui::GetWindowWidth() - ImGui::GetStyle().WindowPadding.x * 2;
    float x = ImGui::GetStyle().WindowPadding.x + (available - width) / 2;
    if (x > ImGui::GetStyle().WindowPadding.x) ImGui::SetCursorPosX(x);
}

bool bigButton(const char* text, float width = 320)
{
    center(width);
    return ImGui::Button(text, ImVec2(width, 48));
}

void boldText(const char* text)
{
    if (boldFont)
        ImGui::PushFont(boldFont);

    ImGui::Text("%s", text);

    if (boldFont)
        ImGui::PopFont();
}

void title(const char* text, const char* sub = "")
{
    if (boldFont) ImGui::PushFont(boldFont);
    ImGui::SetWindowFontScale(1.35f);
    float cw = ImGui::GetWindowWidth() - ImGui::GetStyle().WindowPadding.x * 2;
    float tw = ImGui::CalcTextSize(text).x;
    ImGui::SetCursorPosX(ImGui::GetStyle().WindowPadding.x + (cw - tw) / 2);
    ImGui::Text("%s", text);
    ImGui::SetWindowFontScale(1.0f);
    if (boldFont) ImGui::PopFont();
    if (sub[0])
    {
        float sw = ImGui::CalcTextSize(sub).x;
        ImGui::SetCursorPosX(ImGui::GetStyle().WindowPadding.x + (cw - sw) / 2);
        ImGui::Text("%s", sub);
    }
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
}
void backButton(Screen& screen, Screen previous)
{
    ImGui::Spacing();
    if (bigButton("Back", 180))
        screen = previous;
}

int findEmployee(const vector<Employee>& employees, int id)
{
    for (int i = 0; i < (int)employees.size(); i++)
        if (employees[i].employeeID == id)
            return i;
    return -1;
}

void clearAdd(char* id, char* name, char* age, char* gender,
              char* dept, char* designation, char* phone,
              char* email, char* salary)
{
    id[0] = name[0] = age[0] = gender[0] = dept[0] = '\0';
    designation[0] = phone[0] = email[0] = salary[0] = '\0';
}

int main()
{
    if (!glfwInit()) return 1;

    GLFWwindow* window = glfwCreateWindow(
        1100, 700, "Employee Payroll System", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.FontGlobalScale = 1.25f;

    boldFont = io.Fonts->AddFontFromFileTTF(
        "C:/Windows/Fonts/segoeuib.ttf", 22.0f);

    ImGui::StyleColorsLight();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(28, 24);
    style.FramePadding = ImVec2(12, 10);
    style.ItemSpacing = ImVec2(12, 14);
    style.WindowRounding = 12;
    style.ChildRounding = 12;
    style.FrameRounding = 8;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    FileManager manager;
    Payroll payroll;
    Reports reports;
    vector<Employee> employees = manager.loadEmployees();

    Screen screen = DASHBOARD;

    char id[20] = "", name[100] = "", age[10] = "", gender[30] = "";
    char dept[50] = "", designation[50] = "", phone[20] = "";
    char email[100] = "", salary[30] = "";

    char searchId[20] = "", updateId[20] = "", deleteId[20] = "";
    char payslipId[20] = "";

    char updateName[100] = "", updateDept[50] = "";
    char updateDesignation[50] = "", updateSalary[30] = "";

    char hra[20] = "", highHra[20] = "", da[20] = "";
    char bonus[20] = "", pf[20] = "", tax[20] = "";

    int found = -1;
    string message;
    bool rulesLoaded = false;
    bool deleteConfirm = false;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(io.DisplaySize);

        ImGui::Begin("Employee Payroll System", NULL,
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoCollapse);

        if (screen != DASHBOARD)
            ImGui::SetCursorPosY(120);

        if (screen == DASHBOARD)
        {
            ImGui::SetCursorPosY(45);

            if (boldFont)
                ImGui::PushFont(boldFont);

            ImGui::SetWindowFontScale(1.45f);

            float headingWidth = ImGui::CalcTextSize("EMPLOYEE PAYROLL SYSTEM").x;
            ImGui::SetCursorPosX(
                (ImGui::GetWindowWidth() - headingWidth) / 2
            );

            ImGui::Text("EMPLOYEE PAYROLL SYSTEM");

            ImGui::SetWindowFontScale(1.0f);

            if (boldFont)
                ImGui::PopFont();

            float subWidth = ImGui::CalcTextSize(
                "Employee and Payroll Management").x;

            ImGui::SetCursorPosX(
                (ImGui::GetWindowWidth() - subWidth) / 2
            );

            ImGui::Text("Employee and Payroll Management");

            // Keep the three cards in the vertical middle of the window.
            ImGui::SetCursorPosY(220);

            float cardW = 330, cardH = 240, gap = 24;
            float totalW = cardW * 3 + gap * 2;
            float start = (ImGui::GetWindowWidth() - totalW) / 2;
            if (start < 0) start = 0;
            ImGui::SetCursorPosX(start);

            ImGui::BeginChild("Employees", ImVec2(cardW, cardH), true);
            center(220);
            if (boldFont) ImGui::PushFont(boldFont);
            ImGui::SetWindowFontScale(1.05f);
            ImGui::Text("EMPLOYEES");
            ImGui::SetWindowFontScale(1.0f);
            if (boldFont) ImGui::PopFont();

            ImGui::Spacing();
            center(240);
            ImGui::Text("Manage employee records");
            ImGui::Spacing();
            center(180);
            ImGui::Text("Total: %d", (int)employees.size());
            ImGui::Spacing();
            center(210);
            if (ImGui::Button("OPEN", ImVec2(210, 48)))
                screen = EMPLOYEE_MENU;
            ImGui::EndChild();

            ImGui::SameLine(0, gap);

            ImGui::BeginChild("Payroll", ImVec2(cardW, cardH), true);
            center(220);
            if (boldFont) ImGui::PushFont(boldFont);
            ImGui::SetWindowFontScale(1.05f);
            ImGui::Text("PAYROLL");
            ImGui::SetWindowFontScale(1.0f);
            if (boldFont) ImGui::PopFont();

            ImGui::Spacing();
            center(240);
            ImGui::Text("Salary and payslips");
            ImGui::Spacing();
            center(220);
            ImGui::Text("Rules and calculations");
            ImGui::Spacing();
            center(210);
            if (ImGui::Button("OPEN", ImVec2(210, 48)))
                screen = PAYROLL_MENU;
            ImGui::EndChild();

            ImGui::SameLine(0, gap);

            ImGui::BeginChild("Reports", ImVec2(cardW, cardH), true);
            center(220);
            if (boldFont) ImGui::PushFont(boldFont);
            ImGui::SetWindowFontScale(1.05f);
            ImGui::Text("REPORTS");
            ImGui::SetWindowFontScale(1.0f);
            if (boldFont) ImGui::PopFont();

            ImGui::Spacing();
            center(240);
            ImGui::Text("Statistics and analysis");
            ImGui::Spacing();
            center(220);
            ImGui::Text("Salary and departments");
            ImGui::Spacing();
            center(210);
            if (ImGui::Button("OPEN", ImVec2(210, 48)))
                screen = REPORTS_MENU;
            ImGui::EndChild();

            // Exit button stays directly below the centered cards.
            ImGui::SetCursorPosY(495);
            if (bigButton("EXIT APPLICATION", 240))
                glfwSetWindowShouldClose(window, true);
        }

        else if (screen == EMPLOYEE_MENU)
        {
            title("EMPLOYEE MANAGEMENT", "Manage employee records");

            if (bigButton("Add Employee")) screen = ADD_EMPLOYEE;
            if (bigButton("View Employees")) screen = VIEW_EMPLOYEES;
            if (bigButton("Search Employee")) screen = SEARCH_EMPLOYEE;
            if (bigButton("Update Employee")) screen = UPDATE_EMPLOYEE;
            if (bigButton("Delete Employee")) screen = DELETE_EMPLOYEE;

            backButton(screen, DASHBOARD);
        }

        else if (screen == ADD_EMPLOYEE)
        {
            title("ADD EMPLOYEE", "Enter employee information");

            ImGui::InputText("Employee ID", id, sizeof(id));
            ImGui::InputText("Name", name, sizeof(name));
            ImGui::InputText("Age", age, sizeof(age));
            ImGui::InputText("Gender", gender, sizeof(gender));
            ImGui::InputText("Department", dept, sizeof(dept));
            ImGui::InputText("Designation", designation, sizeof(designation));
            ImGui::InputText("Phone", phone, sizeof(phone));
            ImGui::InputText("Email", email, sizeof(email));
            ImGui::InputText("Basic Salary", salary, sizeof(salary));

            if (bigButton("SAVE EMPLOYEE", 220))
            {
                try
                {
                    int eid = stoi(id);
                    int eage = stoi(age);
                    double esalary = stod(salary);

                    bool duplicate = findEmployee(employees, eid) != -1;

                    if (!digits(id) || eid <= 0)
                        message = "Enter a valid Employee ID.";
                    else if (duplicate)
                        message = "Employee ID already exists.";
                    else if (!name[0])
                        message = "Name is required.";
                    else if (!digits(age) || eage < 18 || eage > 100)
                        message = "Age must be between 18 and 100.";
                    else if (!dept[0])
                        message = "Department is required.";
                    else if (!designation[0])
                        message = "Designation is required.";
                    else if (!digits(phone) || strlen(phone) != 10)
                        message = "Phone must contain 10 digits.";
                    else if (string(email).find('@') == string::npos ||
                             string(email).find('.') == string::npos)
                        message = "Enter a valid email.";
                    else if (esalary <= 0)
                        message = "Salary must be greater than 0.";
                    else
                    {
                        Employee e;
                        e.employeeID = eid;
                        e.name = name;
                        e.age = eage;
                        e.gender = gender;
                        e.department = dept;
                        e.designation = designation;
                        e.phone = phone;
                        e.email = email;
                        e.basicSalary = esalary;

                        employees.push_back(e);
                        manager.saveEmployees(employees);
                        message = "Employee added successfully.";
                        clearAdd(id, name, age, gender, dept,
                                 designation, phone, email, salary);
                    }
                }
                catch (...)
                {
                    message = "Enter valid values.";
                }
            }

            ImGui::Text("%s", message.c_str());
            backButton(screen, EMPLOYEE_MENU);
        }

        else if (screen == VIEW_EMPLOYEES)
        {
            title("EMPLOYEE RECORDS", "All employees stored in CSV");

            ImGui::Text("Total Employees: %d", (int)employees.size());

            if (ImGui::BeginTable("EmployeesTable", 5,
                ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg |
                ImGuiTableFlags_ScrollY, ImVec2(0, 500)))
            {
                ImGui::TableSetupColumn("ID");
                ImGui::TableSetupColumn("Name");
                ImGui::TableSetupColumn("Department");
                ImGui::TableSetupColumn("Designation");
                ImGui::TableSetupColumn("Basic Salary");
                ImGui::TableHeadersRow();

                for (const Employee& e : employees)
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("%d", e.employeeID);
                    ImGui::TableSetColumnIndex(1); ImGui::Text("%s", e.name.c_str());
                    ImGui::TableSetColumnIndex(2); ImGui::Text("%s", e.department.c_str());
                    ImGui::TableSetColumnIndex(3); ImGui::Text("%s", e.designation.c_str());
                    ImGui::TableSetColumnIndex(4); ImGui::Text("Rs. %.2f", e.basicSalary);
                }
                ImGui::EndTable();
            }

            backButton(screen, EMPLOYEE_MENU);
        }

        else if (screen == SEARCH_EMPLOYEE)
        {
            title("SEARCH EMPLOYEE", "Search using Employee ID");
            ImGui::InputText("Employee ID", searchId, sizeof(searchId));

            if (bigButton("SEARCH", 180))
            {
                try
                {
                    found = findEmployee(employees, stoi(searchId));
                    message = found == -1 ? "Employee not found." : "Employee found.";
                }
                catch (...) { found = -1; message = "Enter a valid Employee ID."; }
            }

            ImGui::Text("%s", message.c_str());

            if (found != -1)
            {
                Employee& e = employees[found];
                ImGui::Separator();
                ImGui::Text("Employee ID: %d", e.employeeID);
                ImGui::Text("Name: %s", e.name.c_str());
                ImGui::Text("Age: %d", e.age);
                ImGui::Text("Gender: %s", e.gender.c_str());
                ImGui::Text("Department: %s", e.department.c_str());
                ImGui::Text("Designation: %s", e.designation.c_str());
                ImGui::Text("Phone: %s", e.phone.c_str());
                ImGui::Text("Email: %s", e.email.c_str());
                ImGui::Text("Basic Salary: Rs. %.2f", e.basicSalary);
            }

            backButton(screen, EMPLOYEE_MENU);
        }

        else if (screen == UPDATE_EMPLOYEE)
        {
            title("UPDATE EMPLOYEE", "Find and update employee details");
            ImGui::InputText("Employee ID", updateId, sizeof(updateId));

            if (bigButton("FIND EMPLOYEE", 200))
            {
                try
                {
                    found = findEmployee(employees, stoi(updateId));
                    if (found != -1)
                    {
                        strcpy(updateName, employees[found].name.c_str());
                        strcpy(updateDept, employees[found].department.c_str());
                        strcpy(updateDesignation, employees[found].designation.c_str());
                        sprintf(updateSalary, "%.2f", employees[found].basicSalary);
                        message = "Employee found.";
                    }
                    else message = "Employee not found.";
                }
                catch (...) { found = -1; message = "Enter a valid Employee ID."; }
            }

            ImGui::Text("%s", message.c_str());

            if (found != -1)
            {
                ImGui::InputText("Name", updateName, sizeof(updateName));
                ImGui::InputText("Department", updateDept, sizeof(updateDept));
                ImGui::InputText("Designation", updateDesignation, sizeof(updateDesignation));
                ImGui::InputText("Basic Salary", updateSalary, sizeof(updateSalary));

                if (bigButton("SAVE CHANGES", 200))
                {
                    try
                    {
                        double s = stod(updateSalary);
                        if (!updateName[0] || !updateDept[0] || !updateDesignation[0])
                            message = "Required fields cannot be empty.";
                        else if (s <= 0)
                            message = "Salary must be greater than 0.";
                        else
                        {
                            employees[found].name = updateName;
                            employees[found].department = updateDept;
                            employees[found].designation = updateDesignation;
                            employees[found].basicSalary = s;
                            manager.saveEmployees(employees);
                            message = "Employee updated successfully.";
                        }
                    }
                    catch (...) { message = "Enter a valid salary."; }
                }
            }

            backButton(screen, EMPLOYEE_MENU);
        }

        else if (screen == DELETE_EMPLOYEE)
        {
            title("DELETE EMPLOYEE", "Remove an employee record");
            ImGui::InputText("Employee ID", deleteId, sizeof(deleteId));

            if (bigButton("DELETE EMPLOYEE", 220))
            {
                try
                {
                    found = findEmployee(employees, stoi(deleteId));
                    if (found == -1) message = "Employee not found.";
                    else deleteConfirm = true;
                }
                catch (...) { message = "Enter a valid Employee ID."; }
            }

            if (deleteConfirm)
            {
                ImGui::OpenPopup("Confirm Delete");
                deleteConfirm = false;
            }

            if (ImGui::BeginPopupModal("Confirm Delete", NULL,
                ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("Delete this employee?");
                if (found != -1)
                    ImGui::Text("Name: %s", employees[found].name.c_str());

                if (ImGui::Button("Yes, Delete", ImVec2(140, 44)))
                {
                    employees.erase(employees.begin() + found);
                    manager.saveEmployees(employees);
                    found = -1;
                    deleteId[0] = '\0';
                    message = "Employee deleted successfully.";
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("Cancel", ImVec2(140, 44)))
                {
                    found = -1;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            ImGui::Text("%s", message.c_str());
            backButton(screen, EMPLOYEE_MENU);
        }

        else if (screen == PAYROLL_MENU)
        {
            title("PAYROLL MANAGEMENT", "Salary calculations and payslips");

            if (bigButton("Individual Payslip")) screen = PAYSLIP;
            if (bigButton("Full Payroll Report")) screen = FULL_PAYROLL;
            if (bigButton("View Payroll Rules")) screen = PAYROLL_RULES;
            if (bigButton("Change Payroll Rules"))
            {
                rulesLoaded = false;
                message.clear();
                screen = CHANGE_RULES;
            }

            backButton(screen, DASHBOARD);
        }

        else if (screen == PAYSLIP)
        {
            title("INDIVIDUAL PAYSLIP", "Generate salary details");
            ImGui::InputText("Employee ID", payslipId, sizeof(payslipId));

            if (bigButton("GENERATE PAYSLIP", 220))
            {
                try
                {
                    found = findEmployee(employees, stoi(payslipId));
                    message = found == -1 ? "Employee not found." : "";
                }
                catch (...) { found = -1; message = "Enter a valid Employee ID."; }
            }

            ImGui::Text("%s", message.c_str());

            if (found != -1)
            {
                Employee& e = employees[found];
                double h = payroll.calculateHRA(e.basicSalary);
                double d = payroll.calculateDA(e.basicSalary);
                double b = payroll.calculateBonus(e.basicSalary);
                double gross = e.basicSalary + h + d + b;
                double p = payroll.calculatePF(e.basicSalary);
                double t = payroll.calculateTax(gross);
                double net = gross - p - t;

                center(650);
                ImGui::BeginChild("Payslip", ImVec2(650, 390), true);
                center(300);
                ImGui::SetWindowFontScale(1.45f);
                ImGui::Text("EMPLOYEE PAYSLIP");
                ImGui::SetWindowFontScale(1.0f);
                ImGui::Separator();
                ImGui::Text("Employee ID: %d", e.employeeID);
                ImGui::Text("Name: %s", e.name.c_str());
                ImGui::Text("Department: %s", e.department.c_str());
                ImGui::Text("Designation: %s", e.designation.c_str());
                ImGui::Separator();
                ImGui::Text("Basic Salary: Rs. %.2f", e.basicSalary);
                ImGui::Text("HRA: Rs. %.2f", h);
                ImGui::Text("DA: Rs. %.2f", d);
                ImGui::Text("Bonus: Rs. %.2f", b);
                ImGui::Text("Gross Salary: Rs. %.2f", gross);
                ImGui::Text("PF: Rs. %.2f", p);
                ImGui::Text("Tax: Rs. %.2f", t);
                ImGui::Separator();
                ImGui::SetWindowFontScale(1.35f);
                ImGui::Text("NET SALARY: Rs. %.2f", net);
                ImGui::SetWindowFontScale(1.0f);
                ImGui::EndChild();
            }

            backButton(screen, PAYROLL_MENU);
        }

        else if (screen == FULL_PAYROLL)
        {
            title("FULL PAYROLL REPORT", "Payroll details for all employees");

            if (ImGui::BeginTable("PayrollTable", 7,
                ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg |
                ImGuiTableFlags_ScrollY, ImVec2(0, 500)))
            {
                ImGui::TableSetupColumn("ID");
                ImGui::TableSetupColumn("Name");
                ImGui::TableSetupColumn("Basic");
                ImGui::TableSetupColumn("HRA");
                ImGui::TableSetupColumn("DA");
                ImGui::TableSetupColumn("PF");
                ImGui::TableSetupColumn("Net");
                ImGui::TableHeadersRow();

                for (const Employee& e : employees)
                {
                    double h = payroll.calculateHRA(e.basicSalary);
                    double d = payroll.calculateDA(e.basicSalary);
                    double b = payroll.calculateBonus(e.basicSalary);
                    double gross = e.basicSalary + h + d + b;
                    double p = payroll.calculatePF(e.basicSalary);
                    double net = gross - p - payroll.calculateTax(gross);

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::Text("%d", e.employeeID);
                    ImGui::TableSetColumnIndex(1); ImGui::Text("%s", e.name.c_str());
                    ImGui::TableSetColumnIndex(2); ImGui::Text("%.0f", e.basicSalary);
                    ImGui::TableSetColumnIndex(3); ImGui::Text("%.0f", h);
                    ImGui::TableSetColumnIndex(4); ImGui::Text("%.0f", d);
                    ImGui::TableSetColumnIndex(5); ImGui::Text("%.0f", p);
                    ImGui::TableSetColumnIndex(6); ImGui::Text("%.0f", net);
                }
                ImGui::EndTable();
            }

            backButton(screen, PAYROLL_MENU);
        }

        else if (screen == PAYROLL_RULES)
        {
            title("PAYROLL RULES", "Current salary calculation rules");

            center(600);
            ImGui::BeginChild("Rules", ImVec2(600, 300), true);
            ImGui::Text("HRA (Basic < 40000): %.2f%%", payroll.hraRate * 100);
            ImGui::Text("HRA (Basic >= 40000): %.2f%%", payroll.highHraRate * 100);
            ImGui::Text("DA: %.2f%%", payroll.daRate * 100);
            ImGui::Text("Bonus: %.2f%%", payroll.bonusRate * 100);
            ImGui::Text("PF: %.2f%%", payroll.pfRate * 100);
            ImGui::Text("Tax (Gross > 50000): %.2f%%", payroll.taxRate * 100);
            ImGui::EndChild();

            backButton(screen, PAYROLL_MENU);
        }

        else if (screen == CHANGE_RULES)
        {
            title("CHANGE PAYROLL RULES", "Modify salary percentages");

            if (!rulesLoaded)
            {
                sprintf(hra, "%.2f", payroll.hraRate * 100);
                sprintf(highHra, "%.2f", payroll.highHraRate * 100);
                sprintf(da, "%.2f", payroll.daRate * 100);
                sprintf(bonus, "%.2f", payroll.bonusRate * 100);
                sprintf(pf, "%.2f", payroll.pfRate * 100);
                sprintf(tax, "%.2f", payroll.taxRate * 100);
                rulesLoaded = true;
            }

            ImGui::InputText("HRA < 40000", hra, sizeof(hra));
            ImGui::InputText("HRA >= 40000", highHra, sizeof(highHra));
            ImGui::InputText("DA", da, sizeof(da));
            ImGui::InputText("Bonus", bonus, sizeof(bonus));
            ImGui::InputText("PF", pf, sizeof(pf));
            ImGui::InputText("Tax", tax, sizeof(tax));

            if (bigButton("SAVE PAYROLL RULES", 240))
            {
                try
                {
                    double a = stod(hra), b = stod(highHra), c = stod(da);
                    double d = stod(bonus), e = stod(pf), f = stod(tax);

                    if (a < 0 || a > 100 || b < 0 || b > 100 ||
                        c < 0 || c > 100 || d < 0 || d > 100 ||
                        e < 0 || e > 100 || f < 0 || f > 100)
                        message = "Percentages must be between 0 and 100.";
                    else
                    {
                        payroll.hraRate = a / 100;
                        payroll.highHraRate = b / 100;
                        payroll.daRate = c / 100;
                        payroll.bonusRate = d / 100;
                        payroll.pfRate = e / 100;
                        payroll.taxRate = f / 100;
                        payroll.saveRules();
                        message = "Payroll rules saved successfully.";
                    }
                }
                catch (...) { message = "Enter valid percentage values."; }
            }

            ImGui::Text("%s", message.c_str());

            if (bigButton("Back", 180))
            {
                payroll.loadRules();
                rulesLoaded = false;
                message.clear();
                screen = PAYROLL_MENU;
            }
        }

        else if (screen == REPORTS_MENU)
        {
            title("REPORTS", "Employee and salary analytics");

            if (bigButton("Total Employees")) screen = REPORT_TOTAL;
            if (bigButton("Highest Salary")) screen = REPORT_HIGHEST;
            if (bigButton("Lowest Salary")) screen = REPORT_LOWEST;
            if (bigButton("Average Salary")) screen = REPORT_AVERAGE;
            if (bigButton("Department-wise Count")) screen = REPORT_DEPARTMENT;
            if (bigButton("Salary Chart")) screen = REPORT_SALARY_CHART;

            backButton(screen, DASHBOARD);
        }

        else if (screen == REPORT_TOTAL)
        {
            title("TOTAL EMPLOYEES", "Current employee count");
            center(500);
            ImGui::BeginChild("Total", ImVec2(500, 180), true);
            center(100);
            ImGui::SetWindowFontScale(2.0f);
            ImGui::Text("%d", (int)employees.size());
            ImGui::SetWindowFontScale(1.0f);
            ImGui::EndChild();
            backButton(screen, REPORTS_MENU);
        }

        else if (screen == REPORT_HIGHEST || screen == REPORT_LOWEST)
        {
            bool highestMode = screen == REPORT_HIGHEST;
            title(highestMode ? "HIGHEST SALARY" : "LOWEST SALARY",
                  "Basic salary comparison");

            if (employees.empty())
                ImGui::Text("No employees found.");
            else
            {
                Employee result = employees[0];
                for (const Employee& e : employees)
                {
                    if ((highestMode && e.basicSalary > result.basicSalary) ||
                        (!highestMode && e.basicSalary < result.basicSalary))
                        result = e;
                }

                center(600);
                ImGui::BeginChild("SalaryResult", ImVec2(600, 200), true);
                ImGui::Text("Employee ID: %d", result.employeeID);
                ImGui::Text("Name: %s", result.name.c_str());
                ImGui::Text("Department: %s", result.department.c_str());
                ImGui::Text("Basic Salary: Rs. %.2f", result.basicSalary);
                ImGui::EndChild();
            }

            backButton(screen, REPORTS_MENU);
        }

        else if (screen == REPORT_AVERAGE)
        {
            title("AVERAGE SALARY", "Average basic salary");
            double total = 0;
            for (const Employee& e : employees) total += e.basicSalary;
            double average = employees.empty() ? 0 : total / employees.size();

            center(600);
            ImGui::BeginChild("Average", ImVec2(600, 180), true);
            center(300);
            ImGui::SetWindowFontScale(1.6f);
            ImGui::Text("Rs. %.2f", average);
            ImGui::SetWindowFontScale(1.0f);
            ImGui::EndChild();

            backButton(screen, REPORTS_MENU);
        }

        else if (screen == REPORT_DEPARTMENT)
        {
            title("DEPARTMENT-WISE COUNT", "Number of employees per department");

            map<string, int> counts;
            for (const Employee& e : employees) counts[e.department]++;

            center(650);
            if (ImGui::BeginTable("Departments", 2,
                ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg,
                ImVec2(650, 400)))
            {
                ImGui::TableSetupColumn("Department");
                ImGui::TableSetupColumn("Employee Count");
                ImGui::TableHeadersRow();

                for (const auto& item : counts)
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("%s", item.first.c_str());
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%d", item.second);
                }
                ImGui::EndTable();
            }

            backButton(screen, REPORTS_MENU);
        }

        else if (screen == REPORT_SALARY_CHART)
        {
            title("SALARY CHART", "Visual representation of basic salary");

            center(950);
            ImGui::BeginChild("Chart", ImVec2(950, 480), true);

            for (const Employee& e : employees)
            {
                ImGui::Text("%s", e.name.c_str());

                float value = (float)(e.basicSalary / 150000.0);
                if (value > 1) value = 1;
                if (value < 0) value = 0;

                ImGui::ProgressBar(value, ImVec2(700, 25));
                ImGui::SameLine();
                ImGui::Text("Rs. %.0f", e.basicSalary);
            }

            ImGui::EndChild();
            backButton(screen, REPORTS_MENU);
        }

        ImGui::End();

        ImGui::Render();

        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
