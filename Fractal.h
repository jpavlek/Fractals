#pragma once
#pragma pack(2)
#include <string>
#include "Bitmap.h"
#include "ColorPalette.h"
#include"Point.h"

struct Color;
using ScreenSize = Point<int>;

enum class OperationMode
{
	SingleThreaded,
	MultiThreaded
};

enum class ThreadCountBase
{
	ThreadCount_02x02_div_2 = 2,
	ThreadCount_04x04_div_2 = 4,
	ThreadCount_08x08_div_2 = 8,
	ThreadCount_16x16_div_2 = 16,
	ThreadCount_32x32_div_2 = 32,
	ThreadCount_64x64_div_2 = 64, 
};

namespace Fractals
{
	class Fractal
	{
	protected:
		Bitmap bitmap_;
		ColorPalette colorPalette_;
		ScreenSize screenSize_;
		int percentageCalculated_ = 0;
		int maxIterations_ = 0;
		OperationMode operationMode_ = OperationMode::MultiThreaded;
		ThreadCountBase threadCountBase_ = ThreadCountBase::ThreadCount_08x08_div_2;

	public:
		Fractal() noexcept;
		Fractal(const int width, const int height) noexcept;
		Fractal(const int width, const int height, const ColorPalette& colorPalette, const int maxIterations, OperationMode operationMode, ThreadCountBase threadCountBase) noexcept;
		virtual ~Fractal();
		bool saveToFile(std::string filename);
		static std::string operationModeToString(const OperationMode operationMode);
		static constexpr const int DEFAULT_X = 100;
		static constexpr const int DEFAULT_Y = 100;
		static constexpr const int DEFAULT_MAX_ITERATIONS = 64;
	protected:
		void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) noexcept;
		void setPixel(int x, int y, Color color) noexcept;
		void checkCalculationPercentage(int currentCount, int frequency, int increaseStep, int totalCount = 0) noexcept;
		std::string progressBar(const std::string prefix, const int percentage, const int total, const std::string postfix) const;
	};
}