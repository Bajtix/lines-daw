#pragma once

#include <stdint.h>

#include <limits>

#include "RtAudio.h"

static const int LINES_SAMPLE_RATE = 22500;
static const char LINES_TRACK_COUNT = 4;
static unsigned int LINES_BUFFER_SIZE = 256;

static const RtAudioFormat LINES_FORMAT = RTAUDIO_SINT16;
typedef int16_t LINES_FORMAT_TYPE;

inline LINES_FORMAT_TYPE LINES_GET_SAMPLE(float from) {
	return from * std::numeric_limits<LINES_FORMAT_TYPE>::max();
}
inline float LINES_GET_FLOAT(LINES_FORMAT_TYPE from) {
	return (float)from / std::numeric_limits<LINES_FORMAT_TYPE>::max();
}