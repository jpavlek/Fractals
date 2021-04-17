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

int main()
{
	Timer timer;
	timer.start();

	ProcessorFeatureSet::checkProcessorFeatures();

	int const width = 2 * 2 * 2048;
	int const height = 2 * 2 * 2048;
	int const maxIterations = 2048;

#ifdef DEBUG
	ColorPaletteCreator::createAllPalettesTest();
#endif // DEBUG

	ColorPalette colorPalette = ColorPaletteCreator::createPalette(ColorPalettesClass::RGBSpectrum10, 2);
	std::cout << "\n";
	
	std::vector<ThreadCountBase> threadCountBases;

	{
		Timer timer;
		timer.start();
		Fractals::Mandelbrot mandelbrot(width, height, colorPalette, maxIterations, OperationMode::SingleThreaded, ThreadCountBase::ThreadCount_02x02_div_2);
		std::cout << "\n";
		timer.end();
		std::cout << "\n";
	}
	
	threadCountBases.emplace_back(ThreadCountBase::ThreadCount_02x02_div_2);
	threadCountBases.emplace_back(ThreadCountBase::ThreadCount_04x04_div_2);
	threadCountBases.emplace_back(ThreadCountBase::ThreadCount_08x08_div_2);
	threadCountBases.emplace_back(ThreadCountBase::ThreadCount_16x16_div_2);
	threadCountBases.emplace_back(ThreadCountBase::ThreadCount_32x32_div_2);
	threadCountBases.emplace_back(ThreadCountBase::ThreadCount_64x64_div_2);

	for (const auto threadCountBase : threadCountBases)
	{
		Timer timer;
		timer.start();
		Fractals::Mandelbrot mandelbrot(width, height, colorPalette, maxIterations, OperationMode::MultiThreaded, threadCountBase);
		std::cout << "\n";
		timer.end();
		std::cout << "\n";
	}

	std::cout << "Done.\n";
	timer.end();
	return 0;
}
