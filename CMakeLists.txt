cmake_minimum_required(VERSION 3.14)
project(FirstSimulatorTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTORCC  ON)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)
set(CMAKE_AUTOMOC ON)

add_subdirectory(sources)
add_subdirectory(test)
enable_testing()
add_test(NAME MyTest COMMAND Test)