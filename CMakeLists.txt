cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

project(lines)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(JACK)
include(RtAudio)

# add terminal
set(LINES_TERMINAL 1)

if(LINES_TERMINAL)
	set(TERMINAL_SOURCES
		src/terminal/ux.cpp
	)
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
)

if(LINES_TERMINAL)
	target_compile_definitions(lines-daw PUBLIC LINES_TERMINAL)
endif()

target_link_libraries(lines-daw PRIVATE RtAudio)
target_include_directories(lines-daw PRIVATE thirdparty/rtaudio)
target_include_directories(lines-daw PRIVATE include/)
