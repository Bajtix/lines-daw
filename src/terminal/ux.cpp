#include "ux.hpp"

#include <RtAudio.h>

#include <iostream>

#include "../helpers.hpp"
#include "../lines.hpp"

LinesDAW* TerminalUX::createLines(RtAudio* rtAudio) {
	for (auto id : rtAudio->getDeviceIds()) {
		print_device_info(rtAudio->getDeviceInfo(id));
	}

	uint inputDevice, outputDevice;
	std::cout << "Input device: ";
	std::cin >> inputDevice;

	std::cout << "Output device: ";
	std::cin >> outputDevice;

	return new LinesDAW(rtAudio, inputDevice, outputDevice);
}

int TerminalUX::start() { return 0; }

int TerminalUX::run() { return 0; }

void TerminalUX::exit() {}

TerminalUX::~TerminalUX() {}
