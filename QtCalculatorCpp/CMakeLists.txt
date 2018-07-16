# necessary to include auto-generated files
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# automatically invoke the Qt meta-object compiler when necessary:
#   - place the Q_OBJECT macro in the definitions for classes that use Qt (i.e. in the header file)
#   - at the bottom of the corresponding source file, place '#include "moc_<name>.cpp"'
set(CMAKE_AUTOMOC ON)

# automatically invoke the Qt UI compiler when necessary
#   - for a ui file '<name>.ui', a header file 'ui_<name>.h' will be generated
set(CMAKE_AUTOUIC ON)

# import the Qt5::Widgets package
find_package(Qt5Widgets REQUIRED)

add_executable(QtCalculatorCpp main.cpp MainWindow.cpp)

target_include_directories(QtCalculatorCpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(QtCalculatorCpp Qt5::Widgets CalculatorCppStatic)