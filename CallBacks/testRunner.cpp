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
    // MOCK_METHOD(void, connect, ());
    MOCK_METHOD(void, disconnect, ());
    MOCK_METHOD(float, getSalary, ( int ), (const));
    MOCK_METHOD(void, updateSalary, ( int, float ) );
    MOCK_METHOD(std::vector<Employee>, getSalariesRange, ( float ), (const));
    MOCK_METHOD(std::vector<Employee>, getSalariesRange, ( float, float ), (const));
};

void RealCallback()
{
    std::cout << "Real callback invoked!\n";
}

MockDatabaseConnection::MockDatabaseConnection(std::string serverAddress)
    : IDatabaseConnection(serverAddress)
{
}

TEST(TestEmployerManager, CallbackTest)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    testing::MockFunction<void(int, int)> mockFunction;

    dbConnection.SetOnConnect(mockFunction.AsStdFunction());

    EXPECT_CALL(mockFunction, Call(testing::_, testing::_));

    dbConnection.connect();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
