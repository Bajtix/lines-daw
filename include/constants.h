#pragma once

static const int LINES_SAMPLE_RATE = 22500;
static const char LINES_TRACK_COUNT = 4;
static unsigned int LINES_BUFFER_SIZE = 256;

static const RtAudioFormat LINES_FORMAT = RTAUDIO_SINT16;
typedef uint16_t LINES_FORMAT_TYPE;