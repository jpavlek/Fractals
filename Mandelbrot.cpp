#pragma pack(2)
#include "Mandelbrot.h"
#include <iostream>
#include "ColorPaletteCreator.h"
#include "Timer.h"
#include <thread>
#include "FileSystem.h"
#include "Rectangle.h"
#include "Point.h"

#ifdef _WIN32
//#include <intrin.h>
#endif

using ScreenRectangle = Geometry::Rectangle<int>;
using ScreenOffset = Geometry::Point<int>;
//using Complex

namespace Fractals
{
	void Mandelbrot::createAllThreadsTest(const int width, const int height, const int maxIterations)
	{
		const std::string outputString = "\nThreads Performance Test - SingleThreaded to Multithreadeded Performance Comparison (Threads: 2, 8, 32, 128, 512, 2048):\n" 
										"========================================================================================================================\n\n";
		std::cout << outputString;

		Colors::ColorPalette colorPalette = Colors::ColorPaletteCreator::createPalette(Colors::ColorPalettesClass::RGBCube4, 1);
		std::cout << "\n";

		{
			Timer::resetCalls();
			Timer timer;
			timer.start();
			Fractals::Mandelbrot mandelbrot(width, height, colorPalette, maxIterations, OperationMode::SingleThreaded, ThreadCountBase::ThreadCount_02x02_div_2);
			std::cout << "\n";
			timer.end();
			Timer::resetCalls();
			std::cout << "\n";
		}

		std::vector<ThreadCountBase> threadCountBases;
		threadCountBases.emplace_back(ThreadCountBase::ThreadCount_02x02_div_2);
		threadCountBases.emplace_back(ThreadCountBase::ThreadCount_04x04_div_2);
		threadCountBases.emplace_back(ThreadCountBase::ThreadCount_08x08_div_2);
		threadCountBases.emplace_back(ThreadCountBase::ThreadCount_16x16_div_2);
		threadCountBases.emplace_back(ThreadCountBase::ThreadCount_32x32_div_2);
		//threadCountBases.emplace_back(ThreadCountBase::ThreadCount_64x64_div_2);
		
		for (const auto threadCountBase : threadCountBases)
		{
			Timer::resetCalls();
			Timer timer;
			timer.start();
			Fractals::Mandelbrot mandelbrot(width, height, colorPalette, maxIterations, OperationMode::MultiThreaded, threadCountBase);
			std::cout << "\n";
			timer.end();
			Timer::resetCalls();
			std::cout << "\n";
		}
	}

	Mandelbrot::Mandelbrot() noexcept:
		Mandelbrot(DEFAULT_X, DEFAULT_Y, Colors::ColorPalette(), MAX_ITERATIONS_DEFAULT)
	{
	}

	Mandelbrot::Mandelbrot(const int width, const int height) noexcept:
		Mandelbrot(width, height, Colors::ColorPalette(), MAX_ITERATIONS_DEFAULT)
	{
	}

	Mandelbrot::Mandelbrot(const int width, const int height, int maxIterations) noexcept :
		Mandelbrot(width, height, Colors::ColorPalette(), maxIterations)
	{
	}

	Mandelbrot::Mandelbrot(const int width, const int height, const Colors::ColorPalette& colorPalette) noexcept:
		Mandelbrot(width, height, colorPalette, MAX_ITERATIONS_DEFAULT)
	{
	}

	Mandelbrot::Mandelbrot(const int width, const int height, const Colors::ColorPalette& colorPalette, int maxIterations, OperationMode operationMode, ThreadCountBase threadCountBase) noexcept:
		Fractal(width, height, colorPalette, maxIterations, operationMode, threadCountBase)
	{
		prepareIterationColors();

		ComplexRectangle complexPlaneRectangle(-2.0 / 1.3, -1.0, 0.6 / 1.3 , 1.0);
		std::cout << to_string(complexPlaneRectangle, operationMode);
		
		switch (operationMode)
		{
		case OperationMode::SingleThreaded:
		{
			std::cout << ", Enhanced Instruction Set Active: " << getActiveEnhancedInstructionSet() << "\n";
			calculateSingleThread(complexPlaneRectangle, screenSize_);
		} break;
		default:
		{
			const int threadCount = static_cast<int>(threadCountBase) * static_cast<int>(threadCountBase) / 2;
			std::cout << ", Number of threads: " << threadCount << "\n";
			std::cout << "Enhanced Instruction Set Active: " << getActiveEnhancedInstructionSet() << "\n";

			calculateMultiThreads(complexPlaneRectangle, threadCountBase);
			
			std::cout << "\n";
		} break;
		
		}

		saveImageToFile();
	}

	void Mandelbrot::prepareIterationColors() noexcept
	{
		int paletteSize = colorPalette_.getPaletteSize();
		iterationColors_.reserve(maxIterations_ + 1);
		iterationColors_.resize(maxIterations_ + 1);
		for (int counter = 0; counter < maxIterations_; ++counter)
		{
			iterationColors_[counter] = colorPalette_.colorPalette_[counter % paletteSize];
		}
	}

	void Mandelbrot::calculateSingleThread(const ComplexRectangle& complexRectangle, const ScreenRectangle& screenRectangle) noexcept
	{
		checkCalculationPercentage(0, 16, 0, 100);
		const ScreenOffset screenOffset = screenRectangle.bottomLeftCorner_;
		const ScreenSize screenSize = screenRectangle.size();
		const Geometry::ComplexPoint complexOffset = complexRectangle.bottomLeftCorner_;
		const Geometry::ComplexPoint discreteStep(complexRectangle.sizeX() / screenSize.coordinates_[0], complexRectangle.sizeY() / screenSize.coordinates_[1]);

		Colors::Color color;
		Geometry::ComplexPoint fractalPoint = 0.0, step = 0.0;
		int x = 0, iterations = 0;
		for (; x < screenSize.coordinates_[0]; ++x)
		{
			int y = 0;
			step.coordinates_[1] = 0.0;
			for (; y < screenSize.coordinates_[1]; ++y)
			{
				fractalPoint = complexOffset + step;
				iterations = getIteration(fractalPoint.coordinates_[0], fractalPoint.coordinates_[1]);

				color = iterationColors_[iterations];

				setPixel(x + screenOffset.coordinates_[0], y + screenOffset.coordinates_[1], color);
				setPixel(x + screenOffset.coordinates_[0], screenSize_.coordinates_[1] - 1 - y - screenOffset.coordinates_[1], color);

				step.coordinates_[1] += discreteStep.coordinates_[1];
			}
			step.coordinates_[0] += discreteStep.coordinates_[0];
			checkCalculationPercentage(x + 1, 16, 1);
		}
		std::cout << "\n";
	}

	void Mandelbrot::calculateMultiThreads(ComplexRectangle& complexRectangle) noexcept
	{
		const int threadCountBasis = 2 * std::thread::hardware_concurrency();
		calculateMultiThreads(complexRectangle, threadCountBasis);
	}

	void Mandelbrot::calculateMultiThreads(ComplexRectangle& complexRectangle, ThreadCountBase threadCountBase) noexcept
	{
		const int threadCountBasis = static_cast<int>(threadCountBase);
		calculateMultiThreads(complexRectangle, threadCountBasis);
	}

	void Mandelbrot::calculateMultiThreads(ComplexRectangle& complexRectangle, int threadCountBase) noexcept
	{
		checkCalculationPercentage(0, 16, 0, 100);
		const int threadCountBasis = (threadCountBase < 2) ? 2 * std::thread::hardware_concurrency() : threadCountBase;

		// We are calculating the square image so we are dividing the square into smaller square areas, each per thread. 
		// However, we are using the symmetry of the Mandelbrot set on the x-axis, so we need to calculate only the bottom half of the image and mirror the points.
		// Therefore, only half of the threads are needed.
		const int maxThreads = threadCountBasis * threadCountBasis / 2; 
		
		std::vector< std::thread> threads;
		threads.reserve(maxThreads);

		std::vector<ComplexRectangle> complexRectangles;

		std::vector<Geometry::Rectangle<int>> rectangles;
		rectangles.reserve(maxThreads);

		std::vector<ScreenRectangle> screenRectangles;

		ScreenSize rectangleScreenSize = screenSize_ / threadCountBasis;
		double fractalWidth = (complexRectangle.topRightCorner_.coordinates_[0] - complexRectangle.bottomLeftCorner_.coordinates_[0]) / threadCountBasis;

		for (int j = 0; j * j < maxThreads; ++j)
		{
			for (int i = 0; i * i < 2 * maxThreads; ++i)
			{
				ComplexRectangle cpr(complexRectangle.bottomLeftCorner_.coordinates_[0] + i * fractalWidth, complexRectangle.bottomLeftCorner_.coordinates_[1] + j * fractalWidth,
					complexRectangle.bottomLeftCorner_.coordinates_[0] + (i + 1) * fractalWidth, complexRectangle.bottomLeftCorner_.coordinates_[1] + (j + 1) * fractalWidth); // OK
				complexRectangles.emplace_back(cpr);

				Geometry::Rectangle<int> screenRegion = Geometry::Rectangle<int>(rectangleScreenSize) + ScreenSize(rectangleScreenSize) * ScreenOffset(i, j);
				rectangles.emplace_back(screenRegion);
			}
		}
		for (int i = 0; i < maxThreads; ++i)
		{
#if defined(__AVX512F__)
			threads.emplace_back(std::thread(&Mandelbrot::calculateImmintrinsicAVX512, this, std::ref(complexRectangles[i]), std::ref(rectangles[i])));
#elif defined(__AVX2__)
			threads.emplace_back(std::thread(&Mandelbrot::calculateImmintrinsicAVX2, this, std::ref(complexRectangles[i]), std::ref(rectangles[i])));
#else
			threads.emplace_back(std::thread(&Mandelbrot::calculate, this, std::ref(complexRectangles[i]), std::ref(rectangles[i])));
#endif
		}

		for (size_t i = 0; i < maxThreads; i++) threads[i].join();
	}

	void Mandelbrot::calculate(const ComplexRectangle& complexRectangle, const ScreenRectangle& screenRectangle) noexcept
	{
		Timer timer;
		const ScreenOffset screenOffset = screenRectangle.bottomLeftCorner_;
		const ScreenSize screenSize = screenRectangle.size();
		const Geometry::ComplexPoint complexOffset = complexRectangle.bottomLeftCorner_;
		const Geometry::ComplexPoint discreteStep(complexRectangle.sizeX() / screenSize.coordinates_[0], complexRectangle.sizeY() / screenSize.coordinates_[1]);

		Colors::Color color;
		Geometry::ComplexPoint fractalPoint = 0.0, step = 0.0;
		int x = 0, iterations = 0;
		for (; x < screenSize.coordinates_[0]; ++x)
		{
			int y = 0;
			step.coordinates_[1] = 0.0;
			for (; y < screenSize.coordinates_[1]; ++y)
			{
				fractalPoint = complexOffset + step;
				iterations = getIteration(fractalPoint.coordinates_[0], fractalPoint.coordinates_[1]);

				color = iterationColors_[iterations];

				setPixel(x + screenOffset.coordinates_[0], y + screenOffset.coordinates_[1], color);
				setPixel(x + screenOffset.coordinates_[0], screenSize_.coordinates_[1] - 1 - y - screenOffset.coordinates_[1], color);

				step.coordinates_[1] += discreteStep.coordinates_[1];
			}
			step.coordinates_[0] += discreteStep.coordinates_[0];
		}
		timer.end(false);
		checkCalculationPercentage(Timer::calls_, 1, 1, static_cast<int>(threadCountBase_) * static_cast<int>(threadCountBase_) / 2);
	}

#if defined(__AVX512F__)
	void Mandelbrot::calculateImmintrinsicAVX512(const ComplexRectangle& complexRectangle, const ScreenRectangle& screenRectangle) noexcept
	{
		Timer timer;
		const ScreenOffset screenOffset = screenRectangle.bottomLeftCorner_;
		const ScreenSize screenSize = screenRectangle.size();
		const Geometry::ComplexPoint complexOffset = complexRectangle.bottomLeftCorner_;
		const Geometry::ComplexPoint discreteStep(complexRectangle.sizeX() / screenSize.coordinates_[0], complexRectangle.sizeY() / screenSize.coordinates_[1]);

		Geometry::ComplexPoint fractalPoint = 0.0;
		Geometry::ComplexPoint step = 0.0;
		Colors::Color color, color1, color2, color3, color4, color5, color6, color7;

		const __m512d _dicreteStepY = _mm512_set1_pd(discreteStep.coordinates_[1]);										// |dY|dY|dY|dY|dY|dY|dY|dY|
		const __m512d _offsetsY = _mm512_mul_pd(_mm512_set_pd(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0), _dicreteStepY);	// |0|dY|2dY|3dY|4dY|5dY|6dY|7dY|

		int iteration7, iteration6, iteration5, iteration4, iteration3, iteration2, iteration1, iteration0;
		__m512i _iterations;
		__m512d _fractalPointsX, _fractalPointsY;
		int y = 0;
		int x = 0;
		for (; x < screenSize.coordinates_[0]; x += 1)
		{
			step.coordinates_[1] = 0.0;
			y = 0;
			for (; y < screenSize.coordinates_[1]; y += 8)
			{
				fractalPoint = complexOffset + step;
				// Packing 8 complex numbers to 16 doubles for processing in getIterationImintrin
				_fractalPointsX = _mm512_set1_pd(fractalPoint.coordinates_[0]);								// |X|X|X|X|X|X|X|X|
				_fractalPointsY = _mm512_add_pd(_mm512_set1_pd(fractalPoint.coordinates_[1]), _offsetsY);	// |Y|Y+dY|Y+2dY|Y+3dY|Y+4dY|Y+5dY|Y+6dY|Y+7dY|

				_iterations = getIterationImintrin(_fractalPointsX, _fractalPointsY);						// getIterationImintrin function uses AVX2 processor SIMD instruction set

				iteration0 = static_cast<int>(_iterations.m512i_i64[7]);
				iteration1 = static_cast<int>(_iterations.m512i_i64[6]);
				iteration2 = static_cast<int>(_iterations.m512i_i64[5]);
				iteration3 = static_cast<int>(_iterations.m512i_i64[4]);
				iteration4 = static_cast<int>(_iterations.m512i_i64[3]);
				iteration5 = static_cast<int>(_iterations.m512i_i64[2]);
				iteration6 = static_cast<int>(_iterations.m512i_i64[1]);
				iteration7 = static_cast<int>(_iterations.m512i_i64[0]);
				
				std::tie(color, color1, color2, color3, color4, color5, color6, color7) = std::tie(iterationColors_[iteration0], iterationColors_[iteration1], iterationColors_[iteration2], iterationColors_[iteration3], iterationColors_[iteration4], iterationColors_[iteration5], iterationColors_[iteration6], iterationColors_[iteration7]);

				setPixel(x + screenOffset.coordinates_[0], y + screenOffset.coordinates_[1], color);
				setPixel(x + screenOffset.coordinates_[0], screenSize_.coordinates_[1] - 1 - y - screenOffset.coordinates_[1], color);

				setPixel(x + screenOffset.coordinates_[0], y + screenOffset.coordinates_[1] + 1, color1);
				setPixel(x + screenOffset.coordinates_[0], screenSize_.coordinates_[1] - 2 - y - screenOffset.coordinates_[1], color1);

				setPixel(x + screenOffset.coordinates_[0], y + screenOffset.coordinates_[1] + 2, color2);
				setPixel(x + screenOffset.coordinates_[0], screenSize_.coordinates_[1] - 3 - y - screenOffset.coordinates_[1], color2);

				setPixel(x + screenOffset.coordinates_[0], y + screenOffset.coordinates_[1] + 3, color3);
				setPixel(x + screenOffset.coordinates_[0], screenSize_.coordinates_[1] - 4 - y - screenOffset.coordinates_[1], color3);

				setPixel(x + screenOffset.coordinates_[0], y + screenOffset.coordinates_[1] + 4, color4);
				setPixel(x + screenOffset.coordinates_[0], screenSize_.coordinates_[1] - 5 - y - screenOffset.coordinates_[1], color4);

				setPixel(x + screenOffset.coordinates_[0], y + screenOffset.coordinates_[1] + 5, color5);
				setPixel(x + screenOffset.coordinates_[0], screenSize_.coordinates_[1] - 6 - y - screenOffset.coordinates_[1], color5);

				setPixel(x + screenOffset.coordinates_[0], y + screenOffset.coordinates_[1] + 6, color6);
				setPixel(x + screenOffset.coordinates_[0], screenSize_.coordinates_[1] - 7 - y - screenOffset.coordinates_[1], color6);

				setPixel(x + screenOffset.coordinates_[0], y + screenOffset.coordinates_[1] + 7, color7);
				setPixel(x + screenOffset.coordinates_[0], screenSize_.coordinates_[1] - 8 - y - screenOffset.coordinates_[1], color7);

				step.coordinates_[1] += 8 * discreteStep.coordinates_[1];
			}
			step.coordinates_[0] += discreteStep.coordinates_[0];
		}
		timer.end(false);
		checkCalculationPercentage(Timer::calls_, 1, 1, static_cast<int>(threadCountBase_) * static_cast<int>(threadCountBase_) / 2);
	}

	__m512i Mandelbrot::getIterationImintrin(const __m512d x, const __m512d y) const noexcept
	{
		__m512d _Rez_2, _Imz_2, _Rez_t, _Imz_t;									// Re{z}^2, Im{z}^2, Re{z_temp}, Im{z_temp} 
		__mmask8 _mask1_8bit, _mask2_8bit;										// 8bit masks: mask1 to check absolute z value, mask2 to check if max iterations count has been reached;
		__m512i _iterations = _mm512_setzero_si512();							// |0|0|0|0|0|0|0|0|
		__m512i _max_iterations = _mm512_set1_epi64(maxIterations_);			// |512|512|512|512|512|512|512|512|, set the max number of iterations, i.e. 512 (or 1024, 2048, 4096...)

		__m512i _const_1 = _mm512_set1_epi64(1);								// |1|1|1|1|1|1|1|1|
		__m512d _const_2 = _mm512_set1_pd(2.0);									// |2.0|2.0|2.0|2.0|2.0|2.0|2.0|2.0|
		__m512d _const_4 = _mm512_set1_pd(4.0);									// |4.0|4.0|4.0|4.0|4.0|4.0|4.0|4.0|

		__m512d _Imz = _mm512_set1_pd(0.0);										// |0.0|0.0|0.0|0.0|0.0|0.0|0.0|0.0|
		__m512d _Rez = _mm512_set1_pd(0.0);										// |0.0|0.0|0.0|0.0|0.0|0.0|0.0|0.0|

	repeat:
		// We are going to reuse Re{z}^2 and Im{z}^2 to save on number of arithmetic operations
		_Rez_2 = _mm512_mul_pd(_Rez, _Rez);										// Re{z}^2 = Re{z} * Re{z}
		_Imz_2 = _mm512_mul_pd(_Imz, _Imz);										// Im{z}^2 = Im{z} * Im{z}

		// Re{z_temp} = Re{z*z'} + x = Re{z}^2 - Im{z}^2 + x
		_Rez_t = _mm512_sub_pd(_Rez_2, _Imz_2);									// Re{z_temp} = Re{z}^2 - Im{z}^2
		_Rez_t = _mm512_add_pd(_Rez_t, x);										// Re{z_temp} =	Re{z temp}			+ x

		// Im{z_temp} = 2 * Re{z} * Im{z} + y
		_Imz_t = _mm512_mul_pd(_Rez, _Imz);										// Im{z_temp} = Re{z} * Im{z}
		_Imz_t = _mm512_fmadd_pd(_Imz_t, _const_2, y);							// Im{z_temp} = Im{z_temp}	* 2.0 + y

		// z_(n+1) = z_(n)
		_Rez = _Rez_t;															// Re{z} = Re{z_temp}
		_Imz = _Imz_t;															// Im{z} = Im{z_temp}

		// |z|^2 = z*z' = Re{z}^2 + Im{z}^2
		_Rez_2 = _mm512_add_pd(_Rez_2, _Imz_2);									// z*z' = Re{z}^2 + Im{z}^2
		_mask1_8bit = _mm512_cmp_pd_mask(_Rez_2, _const_4, _CMP_LT_OQ);			// check |z|^2 < 4.0, sets 1s for all bits of the numbers where condition is true, 0 otherwise

		_mask2_8bit = _mm512_cmpgt_epi64_mask(_max_iterations, _iterations);	// maxIterations > iterations
		_mask2_8bit = _mask2_8bit & _mask1_8bit;								// check |z|^2 < 4.0 && iterations < maxIterations, 8 bit mask sets 1 for numbers where it holds, 0s elsewhere
		_iterations = _mm512_mask_add_epi64(_iterations, _mask2_8bit, _iterations, _const_1);	// increment corresponding iterations only

		if (_mask2_8bit > 0) goto repeat;										// 8 bit integer number, holds 1s for numbers satisfzing the conditions, i.e. 0b01010000
																				// repeats the loop until there are no more numbers to increment (0b0000)

		return _iterations;
	}

#elif defined(__AVX2__)
	void Mandelbrot::calculateImmintrinsicAVX2(const ComplexRectangle& complexRectangle, const ScreenRectangle& screenRectangle) noexcept
	{
		Timer timer;
		const ScreenOffset screenOffset = screenRectangle.bottomLeftCorner_;
		const ScreenSize screenSize = screenRectangle.size();
		const Geometry::ComplexPoint complexOffset = complexRectangle.bottomLeftCorner_;
		const Geometry::ComplexPoint discreteStep(complexRectangle.sizeX() / screenSize.coordinates_[0], complexRectangle.sizeY() / screenSize.coordinates_[1]);
		
		Geometry::ComplexPoint fractalPoint = 0.0;
		Geometry::ComplexPoint step = 0.0;
		Colors::Color color, color1, color2, color3;

		const __m256d _dicreteStepY = _mm256_set1_pd(discreteStep.coordinates_[1]);					// |dY|dY|dY|dY|
		const __m256d _offsetsY = _mm256_mul_pd(_mm256_set_pd(0.0, 1.0, 2.0, 3.0), _dicreteStepY);	// |0|dY|2dY|3dY|

		int iteration3;
		int iteration2;
		int iteration1;
		int iteration0;
		__m256i _iterations;
		__m256d _fractalPointsX, _fractalPointsY;
		int y = 0;
		int x = 0;
		for (; x < screenSize.coordinates_[0]; x += 1)
		{
			step.coordinates_[1] = 0.0;
			y = 0;
			for (; y < screenSize.coordinates_[1]; y += 4)
			{
				fractalPoint = complexOffset + step;
				// Packing 4 complex numbers to 8 doubles for processing in getIterationImintrin
				_fractalPointsX = _mm256_set1_pd(fractalPoint.coordinates_[0]);								// |X|X|X|X|
				_fractalPointsY = _mm256_add_pd(_mm256_set1_pd(fractalPoint.coordinates_[1]), _offsetsY);	// |Y|Y+dY|Y+2dY|Y+3dY|

				_iterations = getIterationImintrin(_fractalPointsX, _fractalPointsY);						// getIterationImintrin function uses AVX2 processor SIMD instruction set

				iteration0 = static_cast<int>(_iterations.m256i_i64[3]);
				iteration1 = static_cast<int>(_iterations.m256i_i64[2]);
				iteration2 = static_cast<int>(_iterations.m256i_i64[1]);
				iteration3 = static_cast<int>(_iterations.m256i_i64[0]);
				
				std::tie(color, color1, color2, color3) = std::tie(iterationColors_[iteration0], iterationColors_[iteration1], iterationColors_[iteration2], iterationColors_[iteration3]);

				setPixel(x + screenOffset.coordinates_[0], y + screenOffset.coordinates_[1], color);
				setPixel(x + screenOffset.coordinates_[0], screenSize_.coordinates_[1] - 1 - y - screenOffset.coordinates_[1], color);

				setPixel(x + screenOffset.coordinates_[0], y + screenOffset.coordinates_[1] + 1, color1);
				setPixel(x + screenOffset.coordinates_[0], screenSize_.coordinates_[1] - 2 - y - screenOffset.coordinates_[1], color1);

				setPixel(x + screenOffset.coordinates_[0], y + screenOffset.coordinates_[1] + 2, color2);
				setPixel(x + screenOffset.coordinates_[0], screenSize_.coordinates_[1] - 3 - y - screenOffset.coordinates_[1], color2);

				setPixel(x + screenOffset.coordinates_[0], y + screenOffset.coordinates_[1] + 3, color3);
				setPixel(x + screenOffset.coordinates_[0], screenSize_.coordinates_[1] - 4 - y - screenOffset.coordinates_[1], color3);

				step.coordinates_[1] += 4 * discreteStep.coordinates_[1];
			}
			step.coordinates_[0] += discreteStep.coordinates_[0];
		}
		timer.end(false);
		checkCalculationPercentage(Timer::calls_, 1, 1, static_cast<int>(threadCountBase_) * static_cast<int>(threadCountBase_) / 2);
	}

	__m256i Mandelbrot::getIterationImintrin(const __m256d x, const __m256d y) const noexcept
	{
		__m256d _Rez_2, _Imz_2, _Rez_t, _Imz_t, _mask1;							// Re{z}^2, Im{z}^2, Re{z_temp}, Im{z_temp}, mask1 to check absolute z value 
		__m256i _mask2, _increment1;											// mask2 to check if max iterations count has been reached; iteration increment by 1

		__m256i _iterations = _mm256_setzero_si256();							// |0|0|0|0|
		__m256i _max_iterations = _mm256_set1_epi64x(maxIterations_);			// |512|512|512|512|, set the max number of iterations, i.e. 512 (or 1024, 2048, 4096...)

		__m256i _const_1 = _mm256_set1_epi64x(1);								// |1|1|1|1|
		__m256d _const_2 = _mm256_set1_pd(2.0);									// |2.0|2.0|2.0|2.0|
		__m256d _const_4 = _mm256_set1_pd(4.0);									// |4.0|4.0|4.0|4.0|

		__m256d _Imz = _mm256_set1_pd(0.0);										// |0.0|0.0|0.0|0.0|
		__m256d _Rez = _mm256_set1_pd(0.0);										// |0.0|0.0|0.0|0.0|

	repeat:
		// We are going to reuse Re{z}^2 and Im{z}^2 to save on number of arithmetic operations
		_Rez_2 = _mm256_mul_pd(_Rez, _Rez);										// Re{z}^2 = Re{z} * Re{z}
		_Imz_2 = _mm256_mul_pd(_Imz, _Imz);										// Im{z}^2 = Im{z} * Im{z}

		// Re{z_temp} = Re{z*z'} + x = Re{z}^2 - Im{z}^2 + x
		_Rez_t = _mm256_sub_pd(_Rez_2, _Imz_2);									// Re{z_temp} = Re{z}^2 - Im{z}^2
		_Rez_t = _mm256_add_pd(_Rez_t, x);										// Re{z_temp} =	Re{z temp}			+ x

		// Im{z_temp} = 2 * Re{z} * Im{z} + y
		_Imz_t = _mm256_mul_pd(_Rez, _Imz);										// Im{z_temp} = Re{z} * Im{z}
		_Imz_t = _mm256_fmadd_pd(_Imz_t, _const_2, y);							// Im{z_temp} = Im{z_temp}	* 2.0 + y

		// z_(n+1) = z_(n)
		_Rez = _Rez_t;															// Re{z} = Re{z_temp}
		_Imz = _Imz_t;															// Im{z} = Im{z_temp}

		// |z|^2 = z*z' = Re{z}^2 + Im{z}^2
		_Rez_2 = _mm256_add_pd(_Rez_2, _Imz_2);									// z*z' = Re{z}^2 + Im{z}^2
		_mask1 = _mm256_cmp_pd(_Rez_2, _const_4, _CMP_LT_OQ);					// check |z|^2 < 4.0, sets 1s for all bits of the numbers where condition is true, 0 otherwise

		_mask2 = _mm256_cmpgt_epi64(_max_iterations, _iterations);				// maxIterations > iterations
		_mask2 = _mm256_and_si256(_mask2, _mm256_castpd_si256(_mask1));			// check |z|^2 < 4.0 && iterations < maxIterations, set 1s where it holds, 0s elsewhere
																				// |0..0|1..1|0..0|1..1| (4x64 = 256 bit) i.e. the condition holds for 2nd and 4th double
		_increment1 = _mm256_and_si256(_const_1, _mask2);						// set 1 to the integers where condition holds 
		_iterations = _mm256_add_epi64(_iterations, _increment1);				// increment corresponding iterations only

		if (_mm256_movemask_pd(_mm256_castsi256_pd(_mask2)) > 0) goto repeat;	// sets the most significant bit of each number from the mask_2 
																				// to a 4 bit integer number, i.e. |0..0|1..1|0..0|1..1| -> 0b0101
																				// repeats the loop until there are no more numbers to increment (0b0000)

		return _iterations;
	}
#endif

	Mandelbrot::~Mandelbrot()
	{
		iterationColors_.clear();
		iterationColors_.shrink_to_fit();
	}

	int Mandelbrot::getIterationSimple(const double x, const double y) const noexcept
	{
		std::complex<double> z = 0;
		std::complex<double> c{ x, y };
		int iterations = 0;
		while (iterations < maxIterations_)
		{
			z = z * z + c;
			
			if (abs(z) > 2.0)
			{
				break;
			}

			iterations++;
		}

		return iterations;
	}

	int Mandelbrot::getIteration(const double x, const double y) const noexcept
	{
		int iterations = 0;
		double absz2 = 0.0;			// abs(z*z) < 4.0, as using abs(z) < 2.0 is more computationally expensive
		std::complex<double> z = 0;
		std::complex<double> z_z;	// z*z': z components squared, used for optimization reasons in order to save on the total number of arythmetic operations
		while (absz2 < 4.0 && iterations < maxIterations_)
		{
			z_z = { z.real() * z.real(), z.imag() * z.imag() };					// using complex number assignments as they are faster than equivalent assignments of 2 doubles.
			z = { z_z.real() - z_z.imag() + x, 2 * z.real() * z.imag() + y };	// using real() and imag() member accessor funcions is faster than assigning and storing them in 2 double variables 
			absz2 = z_z.real() + z_z.imag();
			iterations++;
		}

		return iterations;
	}

	void Mandelbrot::saveImageToFile()
	{
		if (FileSystem::FileSystem::FileSystem::checkRelativeFilePath("Fractals"))
		{
			std::string fileName = getFractalFileName();
			saveToFile(fileName);
		}	
	}

	std::string Mandelbrot::to_string(ComplexRectangle& complexRectangle, OperationMode operationMode) const noexcept
	{
		std::string outputString =	"Creating Mandelbrot set: [" + complexRectangle.to_string() + "], Max iterations : " + std::to_string(maxIterations_) + "\n"
									"Image name: " + getFractalFileName() +  ", Image size: " + screenSize_.to_string(false) + "\n"
									"Palette: " + colorPalette_.getPaletteName() + ", Palette size: " + std::to_string(colorPalette_.getPaletteSize()) + "\n"
									"Operation Mode: " + Fractal::operationModeToString(operationMode);
		return outputString;
	}
	
	std::string Mandelbrot::getActiveEnhancedInstructionSet() const noexcept
	{
		std::string result;
#if defined(__AVX512F__)
		result = "AVX512F";
#elif defined(__AVX2__)
		result = "AVX2 (256-bit SIMD)";
#else
		result = "No supported enhanced instruction set active.";
#endif
		return result;
	}

	std::string Mandelbrot::getFractalFileName() const noexcept
	{
		const std::string fileName = std::string((".\\Fractals\\Mandelbrot_")) + 
				std::to_string(screenSize_.coordinates_[0]) + "x" + std::to_string(screenSize_.coordinates_[1]) + "_" +
				std::to_string(maxIterations_) + "_" + colorPalette_.getPaletteName() + ".bmp";
		return fileName;
	}
}