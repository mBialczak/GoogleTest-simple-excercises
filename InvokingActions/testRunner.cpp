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

    void someMemberFunction()
    {
        std::cout << "Member function called!\n";
        throw std::runtime_error("Dummy error");
    }

    void otherMemberFunction(std::string param)
    {
        std::cout << "Member function with called with param: \n"
                  << param << '\n';
        throw std::runtime_error("Dummy error");
    }
};

MockDatabaseConnection::MockDatabaseConnection(std::string serverAddress)
    : IDatabaseConnection(serverAddress)
{
}

TEST(TestEmployeeManager, TestConnectionError)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect()).WillOnce(testing::Throw(std::runtime_error("dummy error")));

    ASSERT_THROW(EmployeeManager employeeManager(&dbConnection), std::runtime_error);
}

ACTION(myThrow)
{
    std::cout << "Throwing an error!\n";
    throw std::runtime_error("Dummy error");
}

TEST(TestEmployeeManager, TestConnectionErrorAction)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect()).WillOnce(myThrow());

    ASSERT_THROW(EmployeeManager employeeManager(&dbConnection), std::runtime_error);
}

void someFreeFunction()
{
    std::cout << "Free function\n";
    throw std::runtime_error("Dummy exception");
}

TEST(TestEmployeeManager, TestConnectionErrorInvoke)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect()).WillOnce(testing::Invoke(someFreeFunction));

    ASSERT_THROW(EmployeeManager employeeManager(&dbConnection), std::runtime_error);
}

TEST(TestEmployeeManager, TestConnectionErrorInvokeLambda)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect()).WillOnce(testing::Invoke([]() {
        std::cout << "Lambda called\n";
        throw std::runtime_error("Dummy exception");
    }));

    ASSERT_THROW(EmployeeManager employeeManager(&dbConnection), std::runtime_error);
}

TEST(TestEmployeeManager, TestConnectionErrorInvokeMethod)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    auto boundMethod = std::bind(&MockDatabaseConnection::someMemberFunction, &dbConnection);
    EXPECT_CALL(dbConnection, connect()).WillOnce(testing::InvokeWithoutArgs(boundMethod));
    ASSERT_THROW(EmployeeManager employeeManager(&dbConnection), std::runtime_error);
}

TEST(TestEmployeeManager, TestConnectionErrorInvokeMethodWithParam)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    auto boundMethod = std::bind(&MockDatabaseConnection::otherMemberFunction,
                                 &dbConnection,
                                 "some param");
    EXPECT_CALL(dbConnection, connect()).WillOnce(testing::InvokeWithoutArgs(boundMethod));
    ASSERT_THROW(EmployeeManager employeeManager(&dbConnection), std::runtime_error);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
