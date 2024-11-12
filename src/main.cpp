#include <RtAudio.h>

#include <algorithm>
#include <iostream>

#include "helpers.hpp"
#include "lines.hpp"

#ifdef LINES_TERMINAL
#include "terminal/ux.hpp"
typedef TerminalUX UserInterface;
#endif

int main() {
	auto rtAudio = new RtAudio(RtAudio::LINUX_ALSA);

	for (auto id : rtAudio->getDeviceIds()) {
		print_device_info(rtAudio->getDeviceInfo(id));
	}

	uint inputDevice, outputDevice;
	std::cout << "Input device: ";
	std::cin >> inputDevice;

	std::cout << "Output device: ";
	std::cin >> outputDevice;

	auto app = new LinesDAW(rtAudio, inputDevice, outputDevice);

	auto interface = new UserInterface(app);
	interface->start();
	while (true) {
		interface->run();
	}
	interface->exit();
}
