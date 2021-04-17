// Fractals.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma pack(2)
#include "Mandelbrot.h"
#include <iostream>
#include "ColorPaletteCreator.h"
#include "Timer.h"

#include <stdio.h>
#include "ProcessorFeatureSet.h"

#ifdef _WIN32
#include <intrin.h>
#endif

void runAllPerformanceTests()
{
	ColorPaletteCreator::createAllPalettesTest();

	Fractals::Mandelbrot::createAllThreadsTest();
}

int main()
{
	Timer timerTotal;
	timerTotal.start();

	ProcessorFeatureSet::checkProcessorFeatures();

	const int width = 2 * 4096;
	const int height = 2 * 4096;
	const int maxIterations = 4096;

	Timer timerOptimized;
	timerOptimized.start();

	ColorPalette colorPalette = ColorPaletteCreator::createPalette(ColorPalettesClass::RGBSpectrum10, 2);
	std::cout << "\n";

	Fractals::Mandelbrot mandelbrot(width, height, colorPalette, maxIterations, OperationMode::MultiThreaded, ThreadCountBase::ThreadCount_32x32_div_2);
	std::cout << "\n";

	timerOptimized.end();
	std::cout << "\n";
	Timer::resetCalls();

	runAllPerformanceTests();

	std::cout << "Done.\n";
	timerTotal.end();
	return 0;
}
