#include "ux.hpp"

#include <RtAudio.h>
#include <math.h>

#include <chrono>
#include <format>
#include <iostream>
#include <thread>

#include "../helpers.hpp"
#include "../lines.hpp"

LinesDAW* TerminalUX::createLines(RtAudio* rtAudio) {
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

int TerminalUX::start() {
	this->window = initscr();
	this->timeinfoWindow = subwin(this->window, 3, getmaxx(this->window), 0, 0);
	this->metronomeWindow =
		subwin(this->window, 3, getmaxx(this->window), 3, 0);
	curs_set(0);
	return 0;
}

int TerminalUX::run() {
	auto timeSamples = daw->getPlayhead();

	this->updateTimeWindows(timeSamples);
	wrefresh(this->window);
	refresh();

	std::this_thread::sleep_for(std::chrono::milliseconds(16));
	return 0;
}

void TerminalUX::exit() { endwin(); }

void TerminalUX::updateTimeWindows(size_t timeSamples) {
	auto timeBeats = tc->sm2b(timeSamples);
	auto timeSecs = tc->sm2s(timeSamples);
	auto width = getmaxx(this->window);

	// === TIME INFO ===
	wclear(this->timeinfoWindow);
	box(this->timeinfoWindow, 0, 0);
	mvwprintw(this->timeinfoWindow, 1, 2,
			  std::format("SPL: {:10d} \tBTS: {:04.2f}\tSEC: {:3.2f}",
						  timeSamples, timeBeats, timeSecs)
				  .c_str());

	// === METRONOME ===
	int pos = ((int)floor(timeBeats) % 2)
				  ? width - (timeBeats - floor(timeBeats)) * width
				  : (timeBeats - floor(timeBeats)) * width;

	wclear(this->metronomeWindow);
	box(this->metronomeWindow, 0, 0);
	mvwprintw(this->metronomeWindow, 0, 2, "Metronome");
	mvwaddch(this->metronomeWindow, 1, pos, '+');

	wrefresh(this->timeinfoWindow);
	wrefresh(this->metronomeWindow);
}

TerminalUX::~TerminalUX() {}
