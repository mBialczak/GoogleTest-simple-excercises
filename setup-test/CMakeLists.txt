cmake_minimum_required(VERSION 3.15)

project(mainApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # lots of warnings
    add_compile_options(-Wall -Wextra)
endif()

# add google test
include(FetchContent)
FetchContent_Declare(gtest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG release-1.11.0 )
FetchContent_GetProperties(gtest)
# gtest_POPULATED
# gtest_SOURCE_DIR
# gtest_BUILD_DIR
if(NOT gtest_POPULATED)
  FetchContent_Populate(gtest)
  add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BUILD_DIR})
endif()

add_library(sumLibrary STATIC LibraryCode.cpp)

add_executable(mainApp main.cpp)
target_link_libraries(mainApp sumLibrary)

add_executable(testRunner test.cpp)
target_link_libraries(testRunner sumLibrary gtest_main gmock_main)
