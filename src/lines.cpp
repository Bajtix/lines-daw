#include "lines.hpp"

#include "helpers.hpp"

LinesDAW::LinesDAW(RtAudio* rtAudio, uint input, uint output) {
	this->rtAudio = rtAudio;

	RtAudio::StreamParameters outputParams = {
		.deviceId = output, .nChannels = 1, .firstChannel = 0};

	RtAudio::StreamParameters inputParams = {
		.deviceId = input, .nChannels = 1, .firstChannel = 0};

	if (rtAudio->openStream(&outputParams, &inputParams, LINES_FORMAT,
							LINES_SAMPLE_RATE, &LINES_BUFFER_SIZE,
							&LinesDAW::processInternal, this)) {
		std::cout << rtAudio->getErrorText() << std::endl;
		throw std::exception();
	}

	for (size_t i = 0; i < LINES_TRACK_COUNT; i++) {
		this->audioTracks[i] = new Track(this);
	}

	this->metronomeTrack = new TrackMetronome(this, 523.25);

	rtAudio->startStream();
}

LinesDAW::~LinesDAW() {
	if (this->rtAudio->isStreamOpen()) {
		this->rtAudio->closeStream();
	}

	for (size_t i = 0; i < LINES_TRACK_COUNT; i++) {
		delete this->audioTracks[i];
	}
}

Timebase* LinesDAW::getTimeconv() { return &this->timeconv; }

void LinesDAW::setPlayhead(size_t where) {
	this->globalPlayhead = where;  // todo - checks;
}

size_t LinesDAW::getPlayhead() { return this->globalPlayhead; }

void LinesDAW::setBpm(uint16_t bpm) {
	if (bpm == 0) throw new std::exception();

	this->bpm = bpm;
}

int LinesDAW::processInternal(void* obufPtr, void* ibufPtr,
							  unsigned int nFrames, double streamTime,
							  RtAudioStreamStatus status, void* udPtr) {
	auto context = (LinesDAW*)udPtr;
	auto inputBuffer = (LINES_FORMAT_TYPE*)ibufPtr;
	auto outputBuffer = (LINES_FORMAT_TYPE*)obufPtr;

	if (status) std::cout << "Stream underflow detected!" << std::endl;

	return context->process(outputBuffer, inputBuffer, nFrames, streamTime);
}
