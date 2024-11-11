cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(lines)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(JACK)
include(RtAudio)

set(SOURCES
	src/main.cpp
	src/lines.cpp
	src/lines_processing.cpp
)

set(HEADERS
    include/helpers.hpp
	include/track.h
	include/lines.h
	include/constants.h
	include/timebase.h
)

add_executable(lines-daw
	${SOURCES}
	${HEADERS}
)

target_link_libraries(lines-daw PRIVATE RtAudio)
target_include_directories(lines-daw PRIVATE thirdparty/rtaudio)
target_include_directories(lines-daw PRIVATE include/)
