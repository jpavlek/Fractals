#pragma pack(2)
#include "Fractal.h"
#include <iostream>

namespace Fractals
{
	Fractal::Fractal()  noexcept:
		Fractal(DEFAULT_X, DEFAULT_Y, ColorPalette(), DEFAULT_MAX_ITERATIONS, OperationMode::MultiThreaded, ThreadCountBase::ThreadCount_08x08_div_2)
	{
	}

	Fractal::Fractal(const int width, const int height)  noexcept:
		Fractal(width, height, ColorPalette(), DEFAULT_MAX_ITERATIONS, OperationMode::MultiThreaded, ThreadCountBase::ThreadCount_08x08_div_2)
	{
	}

	Fractal::Fractal(const int width, const int height, const ColorPalette& colorPalette, const int maxIterations, OperationMode operationMode, ThreadCountBase threadCountBase) noexcept:
		screenSize_{ width, height },
		bitmap_{ width, height },
		colorPalette_{ colorPalette },
		maxIterations_ { maxIterations },
		operationMode_ { operationMode},
		threadCountBase_{ threadCountBase }
	{
	}

	Fractal::~Fractal()
	{
		colorPalette_.colorPalette_.clear();
		colorPalette_.colorPalette_.shrink_to_fit();
	}

	void Fractal::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) noexcept
	{
		bitmap_.setPixel(x, y, red, green, blue);
	}

	void Fractal::setPixel(int x, int y, Color color) noexcept
	{
		bitmap_.setPixel(x, y, color);
	}

	void Fractal::checkCalculationPercentage(int currentCount, int frequency, int increaseStep, int totalCount) noexcept
	{
		if (currentCount % frequency)
		{
			return;
		}

		int maxValue = totalCount;
		if (totalCount == 0)
		{
			maxValue = screenSize_.coordinates_[0];
		}
		int currentPercentage = 100 * currentCount / maxValue;
		
		if (currentPercentage - percentageCalculated_ < increaseStep || currentPercentage > 100)
		{
			return;
		}

		percentageCalculated_ = currentPercentage;
		std::string progressBarString = progressBar("[", currentPercentage, 100, "]");
		std::string progBar = std::string(111, '\b') + progressBarString + std::string(111, '\b');
		std::cout << progBar;
	}

	std::string Fractal::progressBar(const std::string prefix, const int percentage, const int total, const std::string postfix) const
	{
		std::string progressBar = prefix + std::string(std::max(percentage, 0), '=') + ">" + std::string(total - percentage, '.') + postfix + " " + std::to_string(percentage) + "/" + std::to_string(total) + "%";
		return progressBar;
	}

	bool Fractal::saveToFile(std::string filename)
	{
		std::cout << "Saving fractal image to file: " << filename << "... ";
		bool result = bitmap_.write(filename);
		return result;
	}

	std::string Fractal::operationModeToString(const OperationMode operationMode)
	{
		std::string operationModeString;

		switch (operationMode)
		{
		case OperationMode::SingleThreaded:
			operationModeString = "Singlethreaded";
			break;
		case OperationMode::MultiThreaded:
			operationModeString = "Multithreaded";
			break;
		default:
			operationModeString = "Multithreaded(?)";
			break;
		}

		return operationModeString;
	}

}