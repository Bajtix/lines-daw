#include <RtAudio.h>

#include <algorithm>
#include <iostream>

#include "helpers.hpp"
#include "lines.hpp"

#ifdef LINES_TERMINAL
#include "terminal/ux.hpp"
typedef TerminalUX UserInterface;
#endif

#ifdef LINES_RAYLIBUI
#include "raylibui/ux.hpp"
typedef RaylibuiUX UserInterface;
#endif

int main() {
	auto rtAudio = new RtAudio(RtAudio::LINUX_ALSA);
	auto interface = new UserInterface();
	auto app = interface->createLines(rtAudio);

	interface->init(app);
	int statusCode = interface->start();
	if (statusCode) return statusCode;
	while (interface->run() == 0) {	 // todo enum of codes and what they mean
	}
	interface->exit();

	delete app;
}
