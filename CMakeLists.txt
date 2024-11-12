cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(lines)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(JACK)
include(RtAudio)

# add terminal

set(TERMINAL_SOURCES
	src/terminal/ux.cpp
)

set(TERMINAL_HEADERS
	include/terminal/ux.hpp
)

set(SOURCES
	src/main.cpp
	src/lines.cpp
	src/lines_processing.cpp
	src/track.cpp
	src/track_metronome.cpp
)

set(HEADERS
    include/helpers.hpp
	include/track.hpp
	include/lines.hpp
	include/constants.h
	include/timebase.hpp
	include/audiobuffer.hpp
	include/utilitytracks.hpp
	include/linesux.hpp
)

add_executable(lines-daw
	${SOURCES}
	${HEADERS}
	${TERMINAL_SOURCES}
	${TERMINAL_HEADERS}
)

target_compile_definitions(lines-daw PUBLIC LINES_TERMINAL)


target_link_libraries(lines-daw PRIVATE RtAudio)
target_include_directories(lines-daw PRIVATE thirdparty/rtaudio)
target_include_directories(lines-daw PRIVATE include/)
