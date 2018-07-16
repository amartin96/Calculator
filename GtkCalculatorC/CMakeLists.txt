# detect a GTK+ install
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

# locate GTK+ headers and libraries
include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})

# add relevant GTK+ compiler flags
add_definitions(${GTK_CFLAGS_OTHER})

add_executable(GtkCalculatorC main.c)

# copy the UI file to the output directory if it has changed
configure_file(layout.glade ${CMAKE_CURRENT_BINARY_DIR}/bin/layout.glade COPYONLY)

# link the target to the GTK+ libraries
target_link_libraries(GtkCalculatorC ${GTK_LIBRARIES} CalculatorCStatic)