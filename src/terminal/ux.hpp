#pragma once
#include <curses.h>	 // this adds curses to main... sigh

#include <string>
#include <thread>

#include "../linesux.hpp"

enum INTERFACE_ZONE {
	TIME_WINDOW,
	METRONOME_WINDOW,
	CONSOLE_WINDOW,
	ZONE_COUNT
};

class TerminalUX : public LinesUX {
   private:
	WINDOW* window;
	WINDOW* timeinfoWindow;
	WINDOW* metronomeWindow;
	WINDOW* consoleWindow;

	INTERFACE_ZONE selectedZone;
	std::string commandBuffer;
	std::string keybindsText;
	std::thread* inputThread;

	bool shouldQuit = false;

	void updateTimeWindows(size_t timeSamples);
	void drawSelectedBg(WINDOW* window, INTERFACE_ZONE zone);
	void updateConsoleWindow();
	void handleInput();
	void executeCommand(std::string command);

   public:
	TerminalUX() {};
	virtual ~TerminalUX();
	LinesDAW* createLines(RtAudio* rtAudio);
	int start();
	int run();
	void exit();
};
