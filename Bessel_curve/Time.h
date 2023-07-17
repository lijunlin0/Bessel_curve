#pragma once
#include<chrono>

class Time
{
public:
	static long long UpdateMS;
	static const long long FrameMS = 17;

	static long long CurrentTime()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}
};
