set(CalculatorCppSources "Calculator.cpp")
add_library(CalculatorCpp SHARED ${CalculatorCppSources})
add_library(CalculatorCppStatic STATIC ${CalculatorCppSources})

# make this directory available for inclusion in projects that link to this library
target_include_directories(CalculatorCpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(CalculatorCppStatic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})