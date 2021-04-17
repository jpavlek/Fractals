#pragma once
#pragma pack(2)
#include "Fractal.h"
#include <complex>

#include "Point.h"
#include "Rectangle.h"
#include <immintrin.h>

using ComplexRectangle = Rectangle<double>;

namespace Fractals
{
	class Mandelbrot: public Fractal
	{
	public:
		static constexpr const int MAX_ITERATIONS = 10 * 256;
		static constexpr const int MAX_ITERATIONS_DEFAULT = 64;
	private:
		std::vector<Color> iterationColors_;
	public:
		static void createAllThreadsTest(const int width = 4096, const int height = 4096, const int maxIterations = 2048);
	public:
		Mandelbrot() noexcept;
		Mandelbrot(const int width, const int height) noexcept;
		Mandelbrot(const int width, const int height, int maxIterations) noexcept;
		Mandelbrot(const int width, const int height, const ColorPalette& colorPalette) noexcept;
		Mandelbrot(const int width, const int height, 
				   const ColorPalette& colorPalette, int maxIterations = MAX_ITERATIONS_DEFAULT, 
				   OperationMode operationMode = OperationMode::MultiThreaded, 
				   ThreadCountBase threadCountBase = ThreadCountBase::ThreadCount_32x32_div_2) noexcept;

		virtual ~Mandelbrot();

		int getIterationSimple(const double x, const double y) const noexcept;
		int getIteration(const double x, const double y) const noexcept;
		void saveImageToFile();

		std::string to_string(ComplexRectangle& complexRectangle, OperationMode operationMode) const noexcept;
		std::string getActiveEnhancedInstructionSet() const noexcept;
		std::string getFractalFileName() const noexcept;
	private:
		void prepareIterationColors() noexcept;
		void calculateSingleThread(const ComplexRectangle& complexRectangle, const Rectangle<int>& screenRectangle) noexcept;
		void calculateMultiThreads(ComplexRectangle& complexRectangle, ThreadCountBase threadCountBase) noexcept;
		void calculateMultiThreads(ComplexRectangle& complexRectangle) noexcept;
		void calculateMultiThreads(ComplexRectangle& complexRectangle, int threadCountBase) noexcept;
		void calculate(const ComplexRectangle& complexRectangle, const Rectangle<int>& screenRectangle) noexcept;
		
#if defined(__AVX512F__)
		void calculateImmintrinsicAVX512(const ComplexRectangle& complexRectangle, const Rectangle<int>& screenRectangle) noexcept;
		__m512i getIterationImintrin(const __m512d x, const __m512d y) const noexcept;
#elif defined(__AVX2__)
		void calculateImmintrinsicAVX2(const ComplexRectangle& complexRectangle, const Rectangle<int>& screenRectangle) noexcept;
		__m256i getIterationImintrin(const __m256d x, const __m256d y) const noexcept;
#endif

	};
}