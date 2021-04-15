#include "Timer.h"
#include <iostream>

int Timer::calls_ = 0;

void Timer::start() noexcept
{
	start_ = std::chrono::high_resolution_clock::now();
}

Timer::Timer() noexcept:
	start_ (std::chrono::high_resolution_clock::now()),
	end_(std::chrono::high_resolution_clock::now()),
	elapsedTime_(end_ - start_)
{
}

void Timer::end() noexcept
{
	end_ = std::chrono::high_resolution_clock::now();
	elapsedTime_ = end_ - start_;
	calls_++;
	std::cout << "Elapsed time: " << elapsedTime_.count() << " Calls: " << std::to_string(calls_) << "\n";
}
