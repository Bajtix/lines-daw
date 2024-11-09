#include "lines.h"

int LinesDAW::process(LINES_FORMAT_TYPE* outputBuffer,
					  LINES_FORMAT_TYPE* inputBuffer, unsigned int frameCount,
					  double streamTime) {
	for (size_t i = 0; i < frameCount; i++) {
		outputBuffer[i] = inputBuffer[i];
	}

	return 0;
}
