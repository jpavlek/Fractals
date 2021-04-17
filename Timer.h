#pragma once
#include <chrono>

class Timer
{
public:
	static void resetCalls();

public:
	static int calls_;

private:
	std::chrono::high_resolution_clock::time_point start_;
	std::chrono::high_resolution_clock::time_point end_;
	std::chrono::duration<double> elapsedTime_;

public:
	Timer() noexcept;
	void start() noexcept;
	void end(bool verbose = true) noexcept;
};

