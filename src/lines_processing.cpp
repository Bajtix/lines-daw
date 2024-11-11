#include "lines.h"

int LinesDAW::process(LINES_FORMAT_TYPE* outputBuffer,
					  LINES_FORMAT_TYPE* inputBuffer, unsigned int frameCount,
					  double streamTime) {
	for (size_t i = 0; i < frameCount; i++) {
		outputBuffer[i] = inputBuffer[i];
	}

	std::cout << "SAMPLES " << globalPlayhead << "\tSECONDS"
			  << this->timeconv.sm2s(this->globalPlayhead) << "\tBEATS"
			  << this->timeconv.sm2b(this->globalPlayhead) << std::endl;

	this->globalPlayhead += frameCount;

	return 0;
}
