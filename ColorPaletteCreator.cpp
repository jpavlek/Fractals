#pragma pack(2)
#include "ColorPaletteCreator.h"
#include <iostream>

ColorPalette ColorPaletteCreator::createPalette(ColorPalettesClass colorPaletteType, int step)
{
	ColorPaletteCreator colorPaletteCreator;

	switch (colorPaletteType)
	{
	case ColorPalettesClass::RGBCube3:
	{
		colorPaletteCreator.addColorPaletteRangePoints({ ColorsEnum::Blue, ColorsEnum::Green, ColorsEnum::Red, ColorsEnum::Blue });
		ColorPalette colorPalette = colorPaletteCreator.createPaletteFromRangePoints(ColorPalettesClass::RGBCube3, step);
		return colorPalette;
	}
	break;
	case ColorPalettesClass::RGBCube4:
	{
		colorPaletteCreator.addColorPaletteRangePoints({ ColorsEnum::Black, ColorsEnum::Blue, ColorsEnum::Green, ColorsEnum::Red, ColorsEnum::Blue});
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

ColorPaletteCreator::ColorPaletteCreator() noexcept
{
}

ColorPalette ColorPaletteCreator::createPaletteFromRangePoints(ColorPalettesClass colorPaletteType, int step)
{
	Color color;
	int transitionCount = (int) rangeColors_.size() - 1;
	
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
			paletteColors[i* transitionSize + j] = color;
		}
	}
	std::string colorPaletteName = std::string("Palette_") + ColorPalette::toString(colorPaletteType) + "_" + std::to_string(paletteSize) + "_" + std::to_string(step);
	ColorPalette colorPalette(colorPaletteName, paletteSize, paletteColors);
	std::cout << colorPaletteName << " set...\n";

	colorPalette.saveColorPaletteAsBitmapFile(std::string(".\\Palettes\\") + colorPaletteName + ".bmp");
	
	return colorPalette;
}

void ColorPaletteCreator::addColorPaletteRangePoint(Color color) noexcept
{
	rangeColors_.emplace_back(color);
}

void ColorPaletteCreator::addColorPaletteRangePoints(std::vector<ColorsEnum> colors) noexcept
{
	for (ColorsEnum color : colors)
	{
		rangeColors_.emplace_back(color);
	}
}
