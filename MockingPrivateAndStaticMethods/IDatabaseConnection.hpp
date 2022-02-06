#pragma once

#include <functional>
#include <string>
#include <vector>

#include "Employee.hpp"

class HelperClass
{
  private:
    virtual void increaseConnectionCount();
    friend class IDatabaseConnection;
};

// interface because we might subclass it
// example: IOracleDatabaseConnectionManager, ISQLDatabaseConnectionManager
class IDatabaseConnection
{
    using Callback = std::function<void(int, int)>;

  public:
    IDatabaseConnection(std::string serverAddress, HelperClass* hC);

    virtual float getSalary(int id) const = 0;   // SELECT * FROM employees WHERE id=...
    virtual void updateSalary(int id, float newSalary) = 0;

    virtual std::vector<Employee> getSalariesRange(float low) const = 0;   // just greater than low
    virtual std::vector<Employee> getSalariesRange(float low, float high) const = 0;

    virtual void connect();
    virtual void disconnect();

    void SetOnConnect(Callback onConnect);

  protected:
    std::string mServerAddress;
    // Callback mOnConnect;

  private:
    virtual void onConnect() {}
    static void increaseConnectionCount();
    static unsigned connectionCount;
    HelperClass* mHelper;
    friend class HelperClass;
};
