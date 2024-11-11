#include <math.h>

#include "lines.hpp"
#include "utilitytracks.hpp"

TrackMetronome::TrackMetronome(LinesDAW* daw, int16_t frequency)
	: AudioBuffer(daw) {
	this->frequency = frequency;
}

LINES_FORMAT_TYPE TrackMetronome::getSample(size_t at) {
	double sigStart = tc->b2s(floor(tc->sm2b(at)));
	double sigTime = tc->sm2s(at) - sigStart;

	int r = ((int)floor(sigTime * this->frequency)) % 2;
	return (r == 0) * LINES_GET_SAMPLE(0.2) * (sigTime < 0.05);
}

int TrackMetronome::writeSample(size_t at, LINES_FORMAT_TYPE sample) {
	return 1;
}
