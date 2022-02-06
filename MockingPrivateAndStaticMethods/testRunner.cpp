#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <map>

#include "Employee.hpp"
#include "EmployeeManager.hpp"
#include "IDatabaseConnection.hpp"

class MockDatabaseConnection : public IDatabaseConnection
{
  public:
    MockDatabaseConnection(std::string serverAddress, HelperClass* hC);
    // MOCK_METHOD(void, connect, ());
    MOCK_METHOD(void, disconnect, ());
    MOCK_METHOD(float, getSalary, ( int ), (const));
    MOCK_METHOD(void, updateSalary, ( int, float ) );
    MOCK_METHOD(std::vector<Employee>, getSalariesRange, ( float ), (const));
    MOCK_METHOD(std::vector<Employee>, getSalariesRange, ( float, float ), (const));
    MOCK_METHOD(void, onConnect, (), (override));
};

void RealCallback()
{
    std::cout << "Real callback invoked!\n";
}

MockDatabaseConnection::MockDatabaseConnection(std::string serverAddress, HelperClass* hC)
    : IDatabaseConnection(serverAddress, hC)
{
}

class MockHelper : public HelperClass
{
  public:
    MOCK_METHOD(void, increaseConnectionCount, (), (override));
};

TEST(TestEmployerManager, BasicTest)
{
    MockHelper hC;
    EXPECT_CALL(hC, increaseConnectionCount);
    MockDatabaseConnection mdb("dummyConnection", &hC);
    EXPECT_CALL(mdb, onConnect());
    mdb.connect();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
