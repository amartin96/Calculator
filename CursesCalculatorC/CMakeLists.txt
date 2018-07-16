# detect a Curses install
find_package(Curses REQUIRED)
message(${CURSES_HAVE_CURSES_H})
message(${CURSES_HAVE_NCURSES_CURSES_H})

# include Curses headers
include_directories(${CURSES_INCLUDE_DIRS})

add_executable(CursesCalculatorC main.c)

# link with Curses libraries
target_link_libraries(CursesCalculatorC ${CURSES_LIBRARIES})