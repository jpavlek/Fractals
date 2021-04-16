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

	ColorPaletteCreator::createAllPalettesTest();

	ColorPalette colorPalette = ColorPaletteCreator::createPalette(ColorPalettesClass::RGBCube4, 1);

	Fractals::Mandelbrot mandelbrot(width, height, colorPalette, maxIterations);

	std::cout << "Done.\n";
	timer.end();
	return 0;
}
