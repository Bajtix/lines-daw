#pragma once

#include <stdint.h>

#include <iostream>

struct Timebase {
	const int* sample_rate;
	const uint16_t* bpm;

	inline double sm2s(size_t sample) { return (double)sample / *sample_rate; }
	inline size_t s2sm(double second) { return second * *sample_rate; }

	inline size_t b2sm(double beat) { return s2sm(b2s(beat)); }
	inline double sm2b(size_t sample) { return s2b(sm2s(sample)); }

	inline double s2b(double second) { return second * (*bpm / 60.0); }
	inline double b2s(double beat) { return beat / (*bpm / 60.0); }
};
