#pragma once

#include "windows.h"
#ifdef min
#undef min
#endif

class Timer {
public:
	LARGE_INTEGER start;
	LARGE_INTEGER freq;

	void startTimer() {
		if (!QueryPerformanceFrequency(&freq)) {
			printf("## Failed to get frequency ##\n");
		}
		QueryPerformanceCounter(&start);
	}

	double getTimeDiff() {
		LARGE_INTEGER end;
		QueryPerformanceCounter(&end);
		//printf("start = %lld, end = %lld, freq = %lld\n", start.QuadPart, end.QuadPart, freq.QuadPart);
		return ((double)(end.QuadPart - start.QuadPart)) / ((double)freq.QuadPart);
	}
};

