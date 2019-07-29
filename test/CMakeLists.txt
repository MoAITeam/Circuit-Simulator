cmake_minimum_required(VERSION 3.14)
project(FirstSimulatorTest)

set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.12.3/lib/cmake/")
set(CMAKE_AUTORCC  ON)

set(CMAKE_CXX_STANDARD 11)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)

set(CMAKE_AUTOMOC ON)

add_executable(runCircuitTest TestCircuitWidget.cpp)
target_link_libraries (runCircuitTest Eigen3::Eigen Qt5::Widgets Qt5::Test test-lib)