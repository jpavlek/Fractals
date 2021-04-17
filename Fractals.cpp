// Fractals.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma pack(2)
#include "Timer.h"
#include "ColorPalette.h"
#include "Mandelbrot.h"
#include "ProcessorFeatureSet.h"
#include "ColorPaletteCreator.h"
#include <iostream>
#include "Tests.h"

namespace Colors
{
	class ColorPalette;
	class ColorPaletteCreator;
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

	Colors::ColorPalette colorPalette = Colors::ColorPaletteCreator::createPalette(Colors::ColorPalettesClass::RGBSpectrum10, 2);
	std::cout << "\n";

	Fractals::Mandelbrot mandelbrot(width, height, colorPalette, maxIterations, OperationMode::MultiThreaded, ThreadCountBase::ThreadCount_32x32_div_2);
	std::cout << "\n";

	timerOptimized.end();
	std::cout << "\n";
	Timer::resetCalls();

	Tests::runAllPerformanceTests();

	std::cout << "Done.\n";
	timerTotal.end();
	return 0;
}
