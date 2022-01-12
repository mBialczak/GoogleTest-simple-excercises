cmake_minimum_required(VERSION 3.16)

project(AAA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # lots of warnings
    add_compile_options(-Wall -Wextra)
endif()

# # add google test
# include(FetchContent)
# FetchContent_Declare(gtest
#   GIT_REPOSITORY https://github.com/google/googletest
#   GIT_TAG release-1.11.0 )
# FetchContent_GetProperties(gtest)
# # gtest_POPULATED
# # gtest_SOURCE_DIR
# # gtest_BUILD_DIR
# if(NOT gtest_POPULATED)
#   FetchContent_Populate(gtest)
#   add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BUILD_DIR})
# endif()

include(FetchContent)
FetchContent_Declare(gtest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG release-1.11.0)

FetchContent_GetProperties(gtest)

if(NOT gtest_POPULATED)
  FetchContent_Populate(gtest)
  add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BUILD_DIR})
endif()

# set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
# set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_library(sumLibrary STATIC LibraryCode.cpp)

add_executable(mainApp main.cpp)
target_link_libraries(mainApp sumLibrary)


# add test target
add_executable(test testRunner.cpp)
target_link_libraries(test sumLibrary gtest_main gmock_main)