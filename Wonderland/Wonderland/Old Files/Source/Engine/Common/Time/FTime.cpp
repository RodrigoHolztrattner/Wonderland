///////////////////////////////////////////////////////////////////////////////
// Filename: FTime.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FTime.h"
#include <stdio.h>
#include <time.h>

FTime::FTime()
{
}

FTime::FTime(const FTime& other)
{
}

FTime::~FTime()
{
}

float FTime::GetTimeElapsed(bool _reset)
{
	static clock_t lastCall = 0;

	// Check if we are reseting the elapsed time
	if (_reset)
	{
		// Zero the last call
		lastCall = 0;

		return lastCall;
	}
	else
	{
		// Get the new time
		clock_t newTime = clock();

		// Set the elapsed time
		clock_t elapsedTime = ((float)(newTime - lastCall) / (float)CLOCKS_PER_SEC) * 1000.0f;

		// Set the last call time
		lastCall = newTime;

		return elapsedTime / 1000.0f;
	}
}