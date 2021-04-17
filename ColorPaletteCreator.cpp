#pragma pack(2)
#include "ColorPaletteCreator.h"
#include "ColorPalette.h"
#include "Color.h"
#include <iostream>
#include "Timer.h"
#include "FileSystem.h"

namespace Colors
{

	ColorPalette ColorPaletteCreator::createPalette(const ColorPalettesClass& colorPaletteType, int step)
	{
		ColorPaletteCreator colorPaletteCreator;

		switch (colorPaletteType)
		{
		case ColorPalettesClass::RGBCube2:
		{
			colorPaletteCreator.addColorPaletteRangePoints({ ColorsEnum::Black, ColorsEnum::White, ColorsEnum::Black });
			ColorPalette colorPalette = colorPaletteCreator.createPaletteFromRangePoints(ColorPalettesClass::RGBCube2, step);
			return colorPalette;
		}
		break;
		case ColorPalettesClass::RGBCube3:
		{
			colorPaletteCreator.addColorPaletteRangePoints({ ColorsEnum::Blue, ColorsEnum::Green, ColorsEnum::Red, ColorsEnum::Blue });
			ColorPalette colorPalette = colorPaletteCreator.createPaletteFromRangePoints(ColorPalettesClass::RGBCube3, step);
			return colorPalette;
		}
		break;
		case ColorPalettesClass::RGBCube4:
		{
			colorPaletteCreator.addColorPaletteRangePoints({ ColorsEnum::Black, ColorsEnum::Blue, ColorsEnum::Green, ColorsEnum::Red, ColorsEnum::Blue });
			ColorPalette colorPalette = colorPaletteCreator.createPaletteFromRangePoints(ColorPalettesClass::RGBCube4, step);
			return colorPalette;
		}
		break;
		case ColorPalettesClass::RGBCube5:
		{
			colorPaletteCreator.addColorPaletteRangePoints({ ColorsEnum::Black, ColorsEnum::Blue, ColorsEnum::Green, ColorsEnum::Yellow, ColorsEnum::Red, ColorsEnum::White });
			ColorPalette colorPalette = colorPaletteCreator.createPaletteFromRangePoints(ColorPalettesClass::RGBCube5, step);
			return colorPalette;
		}
		break;
		case ColorPalettesClass::RGBCube6:
		{
			colorPaletteCreator.addColorPaletteRangePoints({ ColorsEnum::Black, ColorsEnum::Green, ColorsEnum::Blue, ColorsEnum::Magenta, ColorsEnum::Red, ColorsEnum::Yellow, ColorsEnum::White });
			ColorPalette colorPalette = colorPaletteCreator.createPaletteFromRangePoints(ColorPalettesClass::RGBCube6, step);
			return colorPalette;
		}
		break;
		case ColorPalettesClass::RGBCube10:
		{
			colorPaletteCreator.addColorPaletteRangePoints({ ColorsEnum::Black, ColorsEnum::Blue, ColorsEnum::Green, ColorsEnum::Red, ColorsEnum::Blue, ColorsEnum::White, ColorsEnum::Green, ColorsEnum::Black, ColorsEnum::Red, ColorsEnum::White, ColorsEnum::Black });
			ColorPalette colorPalette = colorPaletteCreator.createPaletteFromRangePoints(ColorPalettesClass::RGBCube10, step);
			return colorPalette;
		}
		break;
		case ColorPalettesClass::RGBRainbow10:
		{
			colorPaletteCreator.addColorPaletteRangePoints({ ColorsEnum::Purple, ColorsEnum::Blue, ColorsEnum::Cyan, ColorsEnum::Green, ColorsEnum::White, ColorsEnum::Yellow, ColorsEnum::Red });
			ColorPalette colorPalette = colorPaletteCreator.createPaletteFromRangePoints(ColorPalettesClass::RGBRainbow10, step);
			return colorPalette;
		}
		break;
		case ColorPalettesClass::RGBSpectrum10:
		{
			colorPaletteCreator.addColorPaletteRangePoints({ ColorsEnum::Black, ColorsEnum::Blue, ColorsEnum::Cyan, ColorsEnum::Green, ColorsEnum::White, ColorsEnum::Yellow, ColorsEnum::Orange, ColorsEnum::Red, ColorsEnum::Magenta, ColorsEnum::Violet, ColorsEnum::Indigo });
			ColorPalette colorPalette = colorPaletteCreator.createPaletteFromRangePoints(ColorPalettesClass::RGBSpectrum10, step);
			return colorPalette;
		}
		break;
		default:
			colorPaletteCreator.addColorPaletteRangePoints({ ColorsEnum::Black, ColorsEnum::Blue, ColorsEnum::Green, ColorsEnum::Yellow, ColorsEnum::Red, ColorsEnum::White });
			ColorPalette colorPalette = colorPaletteCreator.createPaletteFromRangePoints(ColorPalettesClass::RGBCube5, 2);
			return colorPalette;
			break;
		}
	}

	void ColorPaletteCreator::createAllPalettesTest()
	{
		std::cout << "Color Palettes Test - Create all palettes: \n";
		std::cout << "========================================== \n\n";
		Timer timerPalettes;
		timerPalettes.start();

		ColorPalette colorPalette;
		for (int i = 1; i < 128; i *= 2)
		{
			colorPalette = ColorPaletteCreator::createPalette(ColorPalettesClass::RGBCube2, i);
			colorPalette = ColorPaletteCreator::createPalette(ColorPalettesClass::RGBCube3, i);
			colorPalette = ColorPaletteCreator::createPalette(ColorPalettesClass::RGBCube4, i);
			colorPalette = ColorPaletteCreator::createPalette(ColorPalettesClass::RGBCube5, i);
			colorPalette = ColorPaletteCreator::createPalette(ColorPalettesClass::RGBCube6, i);
			colorPalette = ColorPaletteCreator::createPalette(ColorPalettesClass::RGBCube10, i);
			colorPalette = ColorPaletteCreator::createPalette(ColorPalettesClass::RGBRainbow10, i);
			colorPalette = ColorPaletteCreator::createPalette(ColorPalettesClass::RGBSpectrum10, i);
		}
		std::cout << "\n";
		timerPalettes.end();
	}

	ColorPaletteCreator::ColorPaletteCreator() noexcept
	{
	}

	ColorPalette ColorPaletteCreator::createPaletteFromRangePoints(const ColorPalettesClass& colorPaletteType, int step)
	{
		Color color;
		int transitionCount = (int)rangeColors_.size() - 1;

		std::vector<Color> paletteColors;

		int transitionSize = ColorPalette::COLOR_RESOLUTION;
		if (step > 1)
		{
			transitionSize = ColorPalette::COLOR_RESOLUTION / step;
		}
		int paletteSize = transitionSize * transitionCount;
		paletteColors.reserve(paletteSize);
		paletteColors.resize(paletteSize);

		int rangeColorsCount = transitionCount;
		for (int i = 0; i < rangeColorsCount; ++i)
		{
			ColorInt colorStep(ColorInt(rangeColors_[(i + 1) % (rangeColorsCount + 1)]) / transitionSize - rangeColors_[i] / transitionSize);
			for (int j = 0; j < transitionSize; ++j)
			{
				ColorInt colorInt(rangeColors_[i] + colorStep * j);
				color.setColor(colorInt);
				paletteColors[i * transitionSize + j] = color;
			}
		}
		std::string colorPaletteName = std::string("Pal_") + ColorPalette::toString(colorPaletteType) + "_" + std::to_string(paletteSize) + "_" + std::to_string(step);
		ColorPalette colorPalette(colorPaletteName, paletteSize, paletteColors);

#ifdef _DEBUG
		std::cout << colorPaletteName << " set.\n";
#endif // _DEBUG

		if (FileSystem::FileSystem::checkRelativeFilePath("Palettes"))
		{
			std::string relativeFilePathName = std::string(".\\Palettes\\") + colorPaletteName + ".bmp";
			colorPalette.saveColorPaletteAsBitmapFile(relativeFilePathName);
		}

		return colorPalette;
	}

	void ColorPaletteCreator::addColorPaletteRangePoint(const Color& color) noexcept
	{
		rangeColors_.emplace_back(color);
	}

	void ColorPaletteCreator::addColorPaletteRangePoints(const std::vector<ColorsEnum>& colors) noexcept
	{
		for (ColorsEnum color : colors)
		{
			rangeColors_.emplace_back(color);
		}
	}

}