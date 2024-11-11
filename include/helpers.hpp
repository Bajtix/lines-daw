#pragma once
#include <RtAudio.h>

inline void print_device_info(RtAudio::DeviceInfo info) {
	std::cout << info.ID << ": " << info.name << " ========" << std::endl
			  << "SR = " << info.preferredSampleRate << std::endl
			  << "OUTC = " << info.outputChannels << std::endl
			  << "INC = " << info.inputChannels << std::endl;
}
