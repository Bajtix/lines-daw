#include "ux.hpp"

#include <RtAudio.h>
#include <math.h>

#include <chrono>
#include <format>
#include <iostream>

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
	this->consoleWindow = subwin(this->window, 3, getmaxx(this->window), 6, 0);

	curs_set(0);

	// raw();
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	keypad(stdscr, true);

	this->commandBuffer = "";
	this->inputThread = new std::thread(&TerminalUX::handleInput, this);
	this->selectedZone = TIME_WINDOW;

	return 0;
}

void TerminalUX::handleInput() {
	while (this) {
		int c = getch();

		switch (c) {
			case ':':
				this->selectedZone = CONSOLE_WINDOW;
				continue;
				break;
			case KEY_UP:
				this->selectedZone = (INTERFACE_ZONE)(this->selectedZone - 1);
				if (this->selectedZone < 0)
					this->selectedZone = (INTERFACE_ZONE)(ZONE_COUNT - 1);
				continue;
				break;
			case KEY_DOWN:
				this->selectedZone = (INTERFACE_ZONE)(this->selectedZone + 1);
				if (this->selectedZone >= ZONE_COUNT)
					this->selectedZone = (INTERFACE_ZONE)0;
				continue;
				break;
		}

		switch (this->selectedZone) {
			case CONSOLE_WINDOW:
				if (c == KEY_ENTER || c == '\n') {
					this->executeCommand(commandBuffer);
					this->commandBuffer = "";
				} else if (c == KEY_BACKSPACE) {
					this->commandBuffer = this->commandBuffer.substr(
						0, this->commandBuffer.length() - 1);
				} else {
					this->commandBuffer += (char)c;
				}
				break;
		}
	}
}

std::vector<std::string> split(std::string* s, const std::string* delimiter) {
	std::vector<std::string> tokens;
	size_t pos = 0;
	std::string token;
	while ((pos = s->find(*delimiter)) != std::string::npos) {
		token = s->substr(0, pos);
		tokens.push_back(token);
		s->erase(0, pos + delimiter->length());
	}
	tokens.push_back(*s);

	return tokens;
}

void TerminalUX::executeCommand(std::string command) {
	std::string str = " ";
	auto args = split(&command, &str);

	try {
		if (args[0] == "sbpm" && args.size() == 2) {
			this->daw->setBpm(std::stoi(args[1]));
		} else if (args[0] == "p") {
			if (this->daw->isPlaying()) {
				this->daw->pause();
			} else {
				this->daw->play();
			}
		} else if (args[0] == "q") {
			this->shouldQuit = true;
		}
	} catch (std::exception e) {
		// fuck you
	}
}

int TerminalUX::run() {
	auto timeSamples = daw->getPlayhead();

	this->updateTimeWindows(timeSamples);
	this->updateConsoleWindow();

	wrefresh(this->window);
	refresh();

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	return this->shouldQuit;
}

void TerminalUX::exit() { endwin(); }

void TerminalUX::updateTimeWindows(size_t timeSamples) {
	auto timeBeats = tc->sm2b(timeSamples);
	auto timeSecs = tc->sm2s(timeSamples);
	auto width = getmaxx(this->window);

	// === TIME INFO ===
	wclear(this->timeinfoWindow);
	this->drawSelectedBg(this->timeinfoWindow, TIME_WINDOW);
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
	this->drawSelectedBg(this->metronomeWindow, METRONOME_WINDOW);
	box(this->metronomeWindow, 0, 0);
	mvwprintw(this->metronomeWindow, 0, 2, "Metronome");
	mvwaddch(this->metronomeWindow, 1, pos, '+');

	wrefresh(this->timeinfoWindow);
	wrefresh(this->metronomeWindow);
}

void TerminalUX::drawSelectedBg(WINDOW* window, INTERFACE_ZONE zone) {
	if (this->selectedZone == zone)
		wbkgdset(window, COLOR_PAIR(1));
	else
		wbkgdset(window, COLOR_PAIR(0));
}

void TerminalUX::updateConsoleWindow() {
	wclear(this->consoleWindow);
	this->drawSelectedBg(this->consoleWindow, CONSOLE_WINDOW);
	box(this->consoleWindow, 0, 0);
	mvwprintw(this->consoleWindow, 0, 2, "Terminal");
	if (this->selectedZone == CONSOLE_WINDOW) {
		mvwaddch(this->consoleWindow, 1, 2, ':');
		mvwprintw(this->consoleWindow, 1, 3, this->commandBuffer.c_str());
	}
	wrefresh(this->consoleWindow);
}

TerminalUX::~TerminalUX() {}
