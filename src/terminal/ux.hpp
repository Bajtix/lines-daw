#pragma once
#include "../linesux.hpp"

class TerminalUX : public LinesUX {
   public:
	TerminalUX() {};
	virtual ~TerminalUX();
	LinesDAW* createLines(RtAudio* rtAudio);
	int start();
	int run();
	void exit();
};