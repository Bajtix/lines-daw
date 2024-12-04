#include "../lines.hpp"
#include "tracks.hpp"

Track::Track(LinesDAW* daw) : AudioBuffer(daw) {
	this->bufferLength = tc->b2sm(4);
	this->buffer = new LINES_FORMAT_TYPE[this->bufferLength];
}

LINES_FORMAT_TYPE Track::getSample(size_t at) {
	at = at % this->bufferLength;
	return this->buffer[at];
}

int Track::writeSample(size_t at, LINES_FORMAT_TYPE sample) {
	at = at % this->bufferLength;
	this->buffer[at] = sample;
	return 0;
}
