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
    MockDatabaseConnection(std::string serverAddress);
    MOCK_METHOD(void, connect, ());
    MOCK_METHOD(void, disconnect, ());
    MOCK_METHOD(float, getSalary, ( int ), (const));
    MOCK_METHOD(void, updateSalary, ( int, float ) );
    MOCK_METHOD(std::vector<Employee>, getSalariesRange, ( float ), (const));
    MOCK_METHOD(std::vector<Employee>, getSalariesRange, ( float, float ), (const));
};

MockDatabaseConnection::MockDatabaseConnection(std::string serverAddress)
    : IDatabaseConnection(serverAddress)
{
}

TEST(TestEmployerManager, TestConnection)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect());
    EXPECT_CALL(dbConnection, disconnect());
    EmployeeManager employeeManager(&dbConnection);
}

TEST(TestEmployerManager, TestUpdateSalary)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect());
    EXPECT_CALL(dbConnection, disconnect());
    EXPECT_CALL(dbConnection, updateSalary(testing::_, testing::_)).Times(1);
    EmployeeManager employeeManager(&dbConnection);
    employeeManager.setSalary(50, 6000);
}

TEST(TestEmployerManager, TestGetSalary)
{
    constexpr int employeeId = 50;
    constexpr float salary = 6100.0;
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect());
    EXPECT_CALL(dbConnection, disconnect());
    EXPECT_CALL(dbConnection, getSalary(testing::_)).Times(1).WillOnce(testing::Return(salary));
    EmployeeManager employeeManager(&dbConnection);

    float returnedSalary = employeeManager.getSalary(employeeId);

    ASSERT_EQ(salary, returnedSalary);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
