cmake_minimum_required(VERSION 3.14)
project(FirstSimulatorTest)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.12.3/lib/cmake/")

set(CMAKE_AUTORCC  ON)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(PNG REQUIRED)


set(CMAKE_AUTOMOC ON)

set(SOURCE_FILES MainWindow.cpp MainWindow.h components.qrc CurrentSource.cpp CurrentSource.h VoltageSource.cpp VoltageSource.h Wire.cpp Wire.h Resistor.cpp Resistor.h Component.cpp Component.h Circuit.cpp  Circuit.h Node.cpp Node.h CircuitScene.cpp CircuitScene.h CircuitObserver.h ComponentObserver.h NodeObserver.h EigenInterface.cpp SparseMatrix.cpp SparseMatrix.h ModelException.h MatrixException.h ResourceManager.cpp ResourceManager.h)

add_subdirectory(test)

add_executable(FirstSimulatorTest main.cpp ${SOURCE_FILES} )

add_library(dir STATIC${SOURCE_FILES})

target_link_libraries (FirstSimulatorTest Eigen3::Eigen Qt5::Widgets  )
