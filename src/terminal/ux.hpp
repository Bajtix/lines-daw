#pragma once
#include <curses.h>	 // this adds curses to main... sigh

#include "../linesux.hpp"

class TerminalUX : public LinesUX {
   private:
	WINDOW* window;
	WINDOW* timeinfoWindow;
	WINDOW* metronomeWindow;

	void updateTimeWindows(size_t timeSamples);

   public:
	TerminalUX() {};
	virtual ~TerminalUX();
	LinesDAW* createLines(RtAudio* rtAudio);
	int start();
	int run();
	void exit();
};