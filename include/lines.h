#pragma once
#include <RtAudio.h>
#include <stdint.h>

#include "constants.h"
#include "timebase.h"
#include "track.h"

class LinesDAW {
   public:
	LinesDAW(RtAudio *rtAudio, uint input, uint output);
	~LinesDAW();

   private:
	Track *audioTracks[LINES_TRACK_COUNT];
	RtAudio *rtAudio;
	size_t globalPlayhead = 0;
	uint16_t bpm = 120;
	Timebase timeconv = {.sample_rate = (int *)&LINES_SAMPLE_RATE,
						 .bpm = &this->bpm};

	bool audioRecording = false;
	int8_t audioSelectedTrack = -1;

	int process(LINES_FORMAT_TYPE *outputBuffer, LINES_FORMAT_TYPE *inputBuffer,
				unsigned int frameCount, double streamTime);

	static int processInternal(void *outputBuffer, void *inputBuffer,
							   unsigned int nFrames, double streamTime,
							   RtAudioStreamStatus status, void *userData);
};