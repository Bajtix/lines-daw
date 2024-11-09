#pragma once
#include <stdint.h>

#include <iostream>

#include "constants.h"

class Track {
   public:
	int16_t* buffer;
	size_t length;
	size_t loopStart = 0;
	size_t loopLength = LINES_SAMPLE_RATE * 2;
	size_t playhead = 0;
};