#pragma once
#include "../linesux.hpp"

class TerminalUX : LinesUX {
   public:
	TerminalUX(LinesDAW* daw) : LinesUX(daw) {}
	int start();
	int run();
	void exit();
	~TerminalUX();
};