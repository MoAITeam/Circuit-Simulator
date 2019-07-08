cmake_minimum_required(VERSION 3.14)
project(FirstSimulatorTest)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.12.3/lib/cmake/")

add_subdirectory(QTest)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)


set(CMAKE_AUTOMOC ON)

set(SOURCE_FILES main.cpp Component.cpp Component.h Circuit.cpp  Circuit.h Node.cpp Node.h CircuitWidget.cpp CircuitWidget.h CircuitObserver.h ComponentObserver.h NodeObserver.h IMatrix.cpp IMatrix.h)

enable_testing()

add_executable(FirstSimulatorTest main.cpp Component.cpp Component.h Circuit.cpp  Circuit.h Node.cpp Node.h CircuitWidget.cpp CircuitWidget.h CircuitObserver.h ComponentObserver.h NodeObserver.h IMatrix.cpp IMatrix.h)


target_link_libraries (FirstSimulatorTest Eigen3::Eigen)
target_link_libraries(FirstSimulatorTest Qt5::Widgets)
target_link_libraries(FirstSimulatorTest Qt5::Test)
