#pragma once
#pragma pack(2)
#include <string>
#include "Bitmap.h"
#include "ColorPalette.h"
#include"Point.h"

struct Color;
using ScreenSize = Point<int>;

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
	public:
		Fractal() noexcept;
		Fractal(const int width, const int height) noexcept;
		Fractal(const int width, const int height, const ColorPalette& colorPalette, const int maxIterations) noexcept;
		virtual ~Fractal();
		bool saveToFile(std::string filename);
		static constexpr const int DEFAULT_X = 100;
		static constexpr const int DEFAULT_Y = 100;
		static constexpr const int DEFAULT_MAX_ITERATIONS = 64;
	protected:
		void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) noexcept;
		void setPixel(int x, int y, Color color) noexcept;
		void checkCalculationPercentage(int currentCount, int frequency, int increaseStep, int totalCount = 0) noexcept;
		std::string progressBar(std::string prefix, int percentage, int total, std::string postfix) const noexcept;
	};
}