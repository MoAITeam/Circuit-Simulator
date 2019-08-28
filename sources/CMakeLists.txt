set(SOURCE_FILES ResourceManager.h ResourceManager.cpp MainWindow.cpp MainWindow.h components.qrc CurrentSource.cpp CurrentSource.h VoltageSource.cpp VoltageSource.h Wire.cpp Wire.h Resistor.cpp Resistor.h Component.cpp Component.h Circuit.cpp Circuit.h Node.cpp Node.h CircuitScene.cpp CircuitScene.h CircuitObserver.h ComponentObserver.h NodeObserver.h EigenInterface.cpp SparseMatrix.cpp SparseMatrix.h ModelException.h MatrixException.h Voltmeter.cpp Voltmeter.h Amperometer.cpp Amperometer.h VCVS.cpp VCVS.h VCCS.cpp VCCS.h CCCS.cpp CCCS.h CCVS.cpp CCVS.h ActiveComponent.h CircuitSamples.cpp ActiveComponent.cpp)

add_library(CircuitLib SHARED ${SOURCE_FILES})
target_link_libraries(CircuitLib Eigen3::Eigen Qt5::Widgets)

add_executable(CircuitMainApp main.cpp)
target_link_libraries(CircuitMainApp Qt5::Widgets Eigen3::Eigen)
target_link_libraries(CircuitMainApp CircuitLib) #senza questa non trova le definizioni dei metodi
