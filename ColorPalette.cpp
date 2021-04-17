#pragma pack(2)
#include "ColorPalette.h"
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "FileSystem.h"

std::string ColorPalette::toString(const ColorPalettesClass& colorEnum)
{
	std::string colorEnumName;

	switch (colorEnum)
	{
	case ColorPalettesClass::RGBCube2:
		colorEnumName = "RGBCube2";
		break;
	case ColorPalettesClass::RGBCube3:
		colorEnumName = "RGBCube3";
		break;
	case ColorPalettesClass::RGBCube4:
		colorEnumName = "RGBCube4";
		break;
	case ColorPalettesClass::RGBCube5:
		colorEnumName = "RGBCube5";
		break;
	case ColorPalettesClass::RGBCube6:
		colorEnumName = "RGBCube6";
		break;
	case ColorPalettesClass::RGBCube10:
		colorEnumName = "RGBCube10";
		break;
	case ColorPalettesClass::RGBRainbow10:
		colorEnumName = "RGBRainbow10";
		break;
	case ColorPalettesClass::RGBSpectrum10:
		colorEnumName = "RGBSpectrum10";
		break;
	default:
		colorEnumName = "DefaultColorEnumClassName";
		break;
	}

	return colorEnumName;
}

ColorPalette::ColorPalette(std::string paletteName, int paletteSize, std::vector<Color> colorPalette) noexcept:
	paletteName_{ paletteName },
	paletteSize_ { paletteSize },
	colorPalette_ { colorPalette}
{
}

ColorPalette::ColorPalette() noexcept:
	ColorPalette("DefaultPalette", 0, std::vector<Color>())
{
	setPalette();
#ifdef _DEBUG
	std::cout << "Palette created, size: " << sizeof(ColorPalette) << " B\n";
	std::cout << "colorPalette_, size: " << sizeof(colorPalette_) << " B\n";
	std::cout << "paletteName_, size: " << sizeof(paletteName_) << " B\n";
	std::cout << "paletteSize_, size: " << sizeof(int) << " B\n";
#endif // _DEBUG
}

ColorPalette::ColorPalette(const ColorPalette& colorPalette) noexcept:
	colorPalette_{ colorPalette.colorPalette_ },
	paletteName_{ colorPalette.paletteName_ },
	paletteSize_{ colorPalette.paletteSize_ }
{
}

ColorPalette::ColorPalette(ColorPalette&& colorPalette) noexcept:
	colorPalette_{ colorPalette.colorPalette_ },
	paletteName_{ colorPalette.paletteName_ },
	paletteSize_{ colorPalette.paletteSize_ }
{
}

ColorPalette& ColorPalette::operator=(const ColorPalette& colorPalette) noexcept
{
	if (this != &colorPalette)
	{
		colorPalette_.clear();
		std::copy(colorPalette.colorPalette_.begin(), colorPalette.colorPalette_.end(), colorPalette_.begin());
		paletteName_.clear();
		paletteName_ = colorPalette.paletteName_;
		paletteSize_ = colorPalette.paletteSize_;
	}
	return *this;
}

ColorPalette& ColorPalette::operator=(ColorPalette&& colorPalette) noexcept
{
	colorPalette_.clear();
	colorPalette_.reserve(colorPalette.colorPalette_.size());
	colorPalette_ = colorPalette.colorPalette_;
	paletteName_.clear();
	paletteName_ = colorPalette.paletteName_;
	paletteSize_ = colorPalette.paletteSize_;
	return *this;
}

ColorPalette::~ColorPalette()
{
	colorPalette_.clear();
	colorPalette_.shrink_to_fit();
	paletteName_.clear();
	paletteName_.shrink_to_fit();
	paletteSize_ = 0;
}

void ColorPalette::setPalette(int paletteSize) noexcept
{
	colorPalette_.reserve(paletteSize);
	Color color;
    int transitionCount = 4;
    int divisionFactor = paletteSize / transitionCount;
	int nuanceStep = COLOR_RESOLUTION / divisionFactor;
	int transitionSize = COLOR_RESOLUTION / nuanceStep;
	colorPalette_.resize(paletteSize, Color());
	paletteSize_ = paletteSize;
    for (int i = 0; i < transitionSize; ++i)
    {
        color.setColor(0, 0, nuanceStep * i);
        colorPalette_[i] = color;
        color.setColor(0, nuanceStep * i, MAX_COLOR_VALUE - nuanceStep * i);
        colorPalette_[i + transitionSize] = color;
        color.setColor(nuanceStep * i, MAX_COLOR_VALUE - nuanceStep * i, 0);
        colorPalette_[i + 2 * transitionSize] = color;
        color.setColor(MAX_COLOR_VALUE - nuanceStep * i, 0, nuanceStep * i);
        colorPalette_[i + 3 * transitionSize] = color;
    }

#ifdef _DEBUG
	std::cout << "Default palette set...\n";
#endif // _DEBUG

	if (FileSystem::checkRelativeFilePath("Palettes"))
	{
		saveColorPaletteAsBitmapFile(".\\Palettes\\DefaultPalette.bmp");
		std::cout << "\n";
	}
}


void ColorPalette::setPaletteName(std::string paleteName) noexcept
{
	paletteName_ = paleteName;
}

Color ColorPalette::getColor(int colorIndex) const noexcept
{
    return colorPalette_[colorIndex];
}

int ColorPalette::getPaletteSize() const noexcept
{
	return paletteSize_;
}

std::string ColorPalette::getPaletteName() const noexcept
{
	return paletteName_;
}

void ColorPalette::saveColorPaletteAsBitmapFile(std::string fileName) noexcept
{
	int width = paletteSize_;
	int height = DEFAULT_PALETTE_BITMAP_HEIGHT;
	Bitmap bitmap(width, DEFAULT_PALETTE_BITMAP_HEIGHT);

#ifdef _DEBUG
	std::cout << "Filling color palette bitmap (" << width << "x" << height << ")...\n";
#endif // _DEBUG
	
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			bitmap.setPixel(x, y, getColor(x));
		}
	}

	bool result = bitmap.write(fileName);
	if (result)
	{
		std::cout << "Color palette " << paletteName_ << " saved to file: \"" << fileName << "\".\n";
	}
	
}

void ColorPalette::saveColorPaletteAsBitmapFile() noexcept
{
	std::string fileName = paletteName_ + ".bmp";
	if (FileSystem::checkRelativeFilePath("Palettes"))
	{
		saveColorPaletteAsBitmapFile(fileName);
	}
}

