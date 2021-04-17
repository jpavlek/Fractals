#pragma once
#pragma pack(2)
#include"Point.h"
#include "Bitmap.h"
#include "ColorPalette.h"

namespace Geometry
{
	template< typename T, int dimensions = 2 > struct Point;
}

using ScreenSize = Geometry::Point<int>;

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
		FileSystem::Bitmap bitmap_;
		Colors::ColorPalette colorPalette_;
		ScreenSize screenSize_;
		int percentageCalculated_ = 0;
		int maxIterations_ = 0;
		OperationMode operationMode_ = OperationMode::MultiThreaded;
		ThreadCountBase threadCountBase_ = ThreadCountBase::ThreadCount_08x08_div_2;

	public:
		Fractal() noexcept;
		Fractal(const int width, const int height) noexcept;
		Fractal(const int width, const int height, const Colors::ColorPalette& colorPalette, const int maxIterations, const OperationMode& operationMode, const ThreadCountBase& threadCountBase) noexcept;
		virtual ~Fractal();
		bool saveToFile(const std::string& filename);
		static std::string operationModeToString(const OperationMode& operationMode);
		static constexpr const int DEFAULT_X = 100;
		static constexpr const int DEFAULT_Y = 100;
		static constexpr const int DEFAULT_MAX_ITERATIONS = 64;
	protected:
		void setPixel(const int x, const int y, const uint8_t red, const uint8_t green, const uint8_t blue) noexcept;
		void setPixel(const int x, const int y, const Colors::Color& color) noexcept;
		void checkCalculationPercentage(const int currentCount, const int frequency, const int increaseStep, const int totalCount = 0) noexcept;
		std::string progressBar(const std::string& prefix, const int percentage, const int total, const std::string& postfix) const;
	};
}