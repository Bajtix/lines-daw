#pragma once

#include "../lines.hpp"
#include "../linesux.hpp"

class RaylibuiUX : public LinesUX {
   public:
	RaylibuiUX() {};
	virtual ~RaylibuiUX() {}

	LinesDAW* createLines(RtAudio* rtAudio);
	int start();
	int run();
	void exit();
};