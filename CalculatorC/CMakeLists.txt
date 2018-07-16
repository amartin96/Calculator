set(CalculatorCSources "calculator.c")
add_library(CalculatorC SHARED ${CalculatorCSources})
add_library(CalculatorCStatic STATIC ${CalculatorCSources})

# make this directory available for inclusion in projects that link to this library
target_include_directories(CalculatorC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(CalculatorCStatic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})