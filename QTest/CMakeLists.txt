cmake_minimum_required(VERSION 3.14)
project(FirstSimulatorTest)

set(CMAKE_CXX_STANDARD 14)



find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)



set(CMAKE_AUTOMOC ON)

set(TEST_SOURCE_FILES TestCircuitWidget.cpp RunAllTest.cpp)

add_executable(FirstSimulatorTest-Test ${TEST_SOURCE_FILES})

target_link_libraries(FirstSimulatorTest-Test Qt5::Widgets)
target_link_libraries(FirstSimulatorTest-Test Qt5::Test)
target_link_libraries(FirstSimulatorTest-Test "CircuitWidget.h")


