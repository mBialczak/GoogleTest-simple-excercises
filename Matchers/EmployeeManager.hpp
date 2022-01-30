#pragma once
#include <map>
#include <string>
#include <vector>

#include "Employee.hpp"
#include "IDatabaseConnection.hpp"

class EmployeeManager
{
      public:
    EmployeeManager(IDatabaseConnection* dbConnection);
    ~EmployeeManager();

    void setSalary(int employeeId, float newSalary);
    float getSalary(int employeeId) const;

    std::map<std::string, float> getSalariesGreater(float low) const;
    std::map<std::string, float> getSalariesBetween(float low, float high) const;

      private:
    std::map<std::string, float> vectorToMap(std::vector<Employee> const& employees) const;

    IDatabaseConnection* mDbConnection;
};
