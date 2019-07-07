cmake_minimum_required(VERSION 3.14)
project(FirstSimulatorTest)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.12.3/lib/cmake/")


find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)

set(CMAKE_AUTOMOC ON)

add_executable(FirstSimulatorTest main.cpp MyMatrix.cpp Component.cpp Circuit.cpp Node.cpp CircuitWidget.cpp CircuitWidget.h CircuitObserver.h ComponentObserver.h NodeObserver.h SparseMatrix.cpp SparseMatrix.h)
add_executable(FirstSimulatorTest-Test MyMatrix.cpp TestCircuitWidget.cpp Component.cpp Circuit.cpp Node.cpp CircuitWidget.cpp CircuitWidget.h CircuitObserver.h ComponentObserver.h NodeObserver.h SparseMatrix.cpp SparseMatrix.h)

target_link_libraries (FirstSimulatorTest Eigen3::Eigen)
target_link_libraries(FirstSimulatorTest Qt5::Widgets)
target_link_libraries(FirstSimulatorTest Qt5::Test)

target_link_libraries (FirstSimulatorTest-Test Eigen3::Eigen)
target_link_libraries(FirstSimulatorTest-Test Qt5::Widgets)
target_link_libraries(FirstSimulatorTest-Test Qt5::Test)