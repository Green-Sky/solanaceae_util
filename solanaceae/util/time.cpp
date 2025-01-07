#include "./time.hpp"

#include <chrono>

uint64_t getTimeMS(void) {
	return
		std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
		).count()
	;
}

