#pragma once
#include <iostream>

#include "constants.h"

class LinesDAW;	 // forward declaration -> lines.hpp
class Timebase;

class AudioBuffer {
   protected:
	LinesDAW* daw;

   public:
	LINES_FORMAT_TYPE* buffer;
	size_t bufferLength;

	AudioBuffer(LinesDAW* daw) { this->daw = daw; }
	virtual ~AudioBuffer() {};
	virtual LINES_FORMAT_TYPE getSample(size_t at) = 0;
	virtual int writeSample(size_t at, LINES_FORMAT_TYPE sample) = 0;
};