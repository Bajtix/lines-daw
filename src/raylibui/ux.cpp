#include "ux.hpp"

#include <raylib.h>

#include "../helpers.hpp"

LinesDAW* RaylibuiUX::createLines(RtAudio* rtAudio) {
	for (auto id : rtAudio->getDeviceIds()) {
		print_device_info(rtAudio->getDeviceInfo(id));
	}

	uint inputDevice, outputDevice, bpm;
	std::cout << "Input device: ";
	std::cin >> inputDevice;

	std::cout << "Output device: ";
	std::cin >> outputDevice;

	std::cout << "Initial BPM: ";
	std::cin >> bpm;

	auto lines = new LinesDAW(rtAudio, inputDevice, outputDevice);
	lines->setBpm(bpm);

	return lines;
}

int RaylibuiUX::start() {
	InitWindow(500, 200, "lines");
	return 0;
}

int RaylibuiUX::run() {
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawText("raylibuiUX :)", 100, 100, 36, BLACK);
	EndDrawing();
	return WindowShouldClose();
}

void RaylibuiUX::exit() { std::cout << "meow" << std::endl; }
