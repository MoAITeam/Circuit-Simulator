cmake_minimum_required(VERSION 3.14)
project(FirstSimulatorTest)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.12.3/lib/cmake/")


find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

add_executable(FirstSimulatorTest main.cpp Component.cpp Circuit.cpp Node.cpp CircuitWidget.cpp CircuitWidget.h Observer.h)
target_link_libraries (FirstSimulatorTest Eigen3::Eigen)
target_link_libraries(FirstSimulatorTest Qt5::Widgets)