cmake_minimum_required(VERSION 3.9)
project(Calculator)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_subdirectory(CalculatorC)
add_subdirectory(CalculatorCpp)
add_subdirectory(CLICalculatorC)
add_subdirectory(CLICalculatorCpp)
add_subdirectory(CursesCalculatorC)
add_subdirectory(GtkCalculatorC)
add_subdirectory(QtCalculatorCpp)