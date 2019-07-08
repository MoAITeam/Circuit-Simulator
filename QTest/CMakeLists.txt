cmake_minimum_required(VERSION 3.14)
project(FirstSimulatorTest)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.12.3/lib/cmake/")


find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)



set(CMAKE_AUTOMOC ON)

add_executable(FirstSimulatorTest-Test TestCircuitWidget.cpp )

target_link_libraries (FirstSimulatorTest-Test Eigen3::Eigen)
target_link_libraries(FirstSimulatorTest-Test Qt5::Widgets)
target_link_libraries(FirstSimulatorTest-Test Qt5::Test)
target_link_libraries(FirstSimulatorTest-Test "CircuitWidget.h")


