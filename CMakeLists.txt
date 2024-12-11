cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 23)

project(lines)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(JACK)
include(RtAudio)

# add rayib
set(LINES_RAYLIBUI 1)

if(LINES_TERMINAL)
	set(TERMINAL_SOURCES
		src/terminal/ux.cpp
	)
endif()

if(LINES_RAYLIBUI)
	set(RAYLIBUI_SOURCES
		src/raylibui/ux.cpp
	)
	include(Raylib)
endif()

set(SOURCES
	src/main.cpp
	src/lines.cpp
	src/lines_processing.cpp
	src/audiobuffers/track.cpp
	src/audiobuffers/track_metronome.cpp
)


add_executable(lines-daw
	${SOURCES}
	${TERMINAL_SOURCES}
	${RAYLIBUI_SOURCES}
)

target_link_libraries(lines-daw PRIVATE RtAudio)
target_include_directories(lines-daw PRIVATE thirdparty/rtaudio)

if(LINES_TERMINAL)
	target_compile_definitions(lines-daw PUBLIC LINES_TERMINAL)
	target_link_libraries(lines-daw PUBLIC curses)
endif()

if(LINES_RAYLIBUI)
	target_compile_definitions(lines-daw PUBLIC LINES_RAYLIBUI)
	target_link_libraries(lines-daw PUBLIC raylib)
endif()
