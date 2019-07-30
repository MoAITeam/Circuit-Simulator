add_executable(CircuitTest TestCircuitWidget.cpp)
target_link_libraries(CircuitTest Qt5::Widgets Eigen3::Eigen Qt5::Test)
target_link_libraries(CircuitTest CircuitLib) #senza questa non trova le definizioni dei metodi
