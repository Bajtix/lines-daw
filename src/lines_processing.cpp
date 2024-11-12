#include "lines.hpp"

int LinesDAW::process(LINES_FORMAT_TYPE* outputBuffer,
					  LINES_FORMAT_TYPE* inputBuffer, unsigned int frameCount,
					  double streamTime) {
	for (size_t i = 0; i < frameCount; i++) {
		outputBuffer[i] = inputBuffer[i];
		outputBuffer[i] +=
			this->metronomeTrack->getSample(this->globalPlayhead);
		this->globalPlayhead++;
	}

	return 0;
}
