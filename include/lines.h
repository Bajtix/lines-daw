#include <RtAudio.h>
#include <stdint.h>

#include "constants.h"
#include "track.h"

class LinesDAW {
   public:
	LinesDAW(RtAudio *rtAudio, uint input, uint output);
	~LinesDAW();

   private:
	Track *tracks[LINES_TRACK_COUNT];
	RtAudio *rtAudio;
	size_t globalPlayhead;
	uint8_t bpm;

	int process(LINES_FORMAT_TYPE *outputBuffer, LINES_FORMAT_TYPE *inputBuffer,
				unsigned int frameCount, double streamTime);

	static int processInternal(void *outputBuffer, void *inputBuffer,
							   unsigned int nFrames, double streamTime,
							   RtAudioStreamStatus status, void *userData);
};