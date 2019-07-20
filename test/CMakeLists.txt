cmake_minimum_required(VERSION 3.14)
project(FirstSimulatorTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)



find_package (Eigen3 3.3 REQUIRED NO_MODULE)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)

#file(GLOB Sources "components.qrc CurrentSource.cpp CurrentSource.h VoltageSource.cpp VoltageSource.h Wire.cpp Wire.h Resistor.cpp Resistor.h Component.cpp Component.h Circuit.cpp  Circuit.h Node.cpp Node.h CircuitScene.cpp CircuitScene.h CircuitObserver.h ComponentObserver.h NodeObserver.h EigenInterface.cpp SparseMatrix.cpp SparseMatrix.h ModelException.h MatrixException.h MainWindow.cpp MainWindow.h" )


add_executable(runGameTest TestCircuitWidget.cpp ${Sources})
target_link_libraries (runGameTest Eigen3::Eigen Qt5::Widgets Qt5::Test core)
