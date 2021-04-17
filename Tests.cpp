#pragma pack(2)
#include "Tests.h"
#include <iostream>
#include "Timer.h"
#include "ColorPalette.h"
#include "ColorPaletteCreator.h"
#include "Mandelbrot.h"

void Tests::createAllPalettesTest()
{
	std::cout << "Color Palettes Test - Create all palettes: \n";
	std::cout << "========================================== \n\n";
	Timer timerPalettes;
	timerPalettes.start();

	Colors::ColorPalette colorPalette;
	for (int i = 1; i < 128; i *= 2)
	{
		colorPalette = Colors::ColorPaletteCreator::createPalette(Colors::ColorPalettesClass::RGBCube2, i);
		colorPalette = Colors::ColorPaletteCreator::createPalette(Colors::ColorPalettesClass::RGBCube3, i);
		colorPalette = Colors::ColorPaletteCreator::createPalette(Colors::ColorPalettesClass::RGBCube4, i);
		colorPalette = Colors::ColorPaletteCreator::createPalette(Colors::ColorPalettesClass::RGBCube5, i);
		colorPalette = Colors::ColorPaletteCreator::createPalette(Colors::ColorPalettesClass::RGBCube6, i);
		colorPalette = Colors::ColorPaletteCreator::createPalette(Colors::ColorPalettesClass::RGBCube10, i);
		colorPalette = Colors::ColorPaletteCreator::createPalette(Colors::ColorPalettesClass::RGBRainbow10, i);
		colorPalette = Colors::ColorPaletteCreator::createPalette(Colors::ColorPalettesClass::RGBSpectrum10, i);
	}
	std::cout << "\n";
	timerPalettes.end();
}

void Tests::runAllPerformanceTests()
{
	Colors::ColorPaletteCreator::createAllPalettesTest();

	Fractals::Mandelbrot::createAllThreadsTest();
}