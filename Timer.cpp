#include "Timer.h"
#include <iostream>

int Timer::calls_ = 0;

void Timer::start() noexcept
{
	start_ = std::chrono::high_resolution_clock::now();
}

void Timer::resetCalls()
{
	calls_ = 0;
}

Timer::Timer() noexcept:
	start_ (std::chrono::high_resolution_clock::now()),
	end_(std::chrono::high_resolution_clock::now()),
	elapsedTime_(end_ - start_)
{
}

void Timer::end(bool verbose) noexcept
{
	end_ = std::chrono::high_resolution_clock::now();
	elapsedTime_ = end_ - start_;
	calls_++;
	if (verbose)
	{
		std::cout << "Elapsed time: " << elapsedTime_.count() << " Calls: " << std::to_string(calls_) << "\n";
	}
}
