#pragma once
#include <RtAudio.h>
#include <stdint.h>

#include "audiobuffer.hpp"
#include "audiobuffers/tracks.hpp"
#include "constants.h"
#include "timebase.hpp"

class Track;  // forward declaration -> track.hpp

// helpful for tracks
#define tc this->daw->getTimeconv()

class LinesDAW {
   public:
	LinesDAW(RtAudio *rtAudio, uint input, uint output);
	~LinesDAW();

	Timebase *getTimeconv();
	size_t getPlayhead();
	void setPlayhead(size_t where);
	void setBpm(uint16_t bpm);
	uint16_t getBpm();
	void play();
	void pause();
	bool isPlaying();

   private:
	Track *audioTracks[LINES_TRACK_COUNT];
	TrackMetronome *metronomeTrack;

	RtAudio *rtAudio;
	size_t globalPlayhead = 0;
	uint16_t bpm = 120;
	Timebase timeconv = {.sample_rate = (int *)&LINES_SAMPLE_RATE,
						 .bpm = &this->bpm};

	bool audioRecording = false;
	bool playing = false;
	int8_t audioSelectedTrack = -1;

	int process(LINES_FORMAT_TYPE *outputBuffer, LINES_FORMAT_TYPE *inputBuffer,
				unsigned int frameCount, double streamTime);

	static int processInternal(void *outputBuffer, void *inputBuffer,
							   unsigned int nFrames, double streamTime,
							   RtAudioStreamStatus status, void *userData);
};