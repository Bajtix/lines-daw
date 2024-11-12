#pragma once
#include <stdint.h>

#include <iostream>

#include "../audiobuffer.hpp"
#include "../constants.h"

class Track : public AudioBuffer {
   public:
	size_t loopStart = 0;
	size_t loopLength = LINES_SAMPLE_RATE * 2;
	Track(LinesDAW* daw) : AudioBuffer(daw) {}
	virtual LINES_FORMAT_TYPE getSample(size_t at);
	virtual int writeSample(size_t at, LINES_FORMAT_TYPE sample);
};

class TrackMetronome : public AudioBuffer {
   public:
	int16_t frequency;
	TrackMetronome(LinesDAW* daw, int16_t frequency);
	virtual LINES_FORMAT_TYPE getSample(size_t at);
	virtual int writeSample(size_t at, LINES_FORMAT_TYPE sample);
};