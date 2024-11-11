#pragma once

#include "audiobuffer.hpp"

class LinesDAW;

class TrackMetronome : public AudioBuffer {
   public:
	int16_t frequency;
	TrackMetronome(LinesDAW* daw, int16_t frequency);
	virtual LINES_FORMAT_TYPE getSample(size_t at);
	virtual int writeSample(size_t at, LINES_FORMAT_TYPE sample);
};