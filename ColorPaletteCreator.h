#pragma once
#pragma pack(2)

#include "ColorPalette.h"

class ColorPaletteCreator
{
private:
	std::vector<Color> rangeColors_;
public:
	static ColorPalette createPalette(ColorPalettesClass colorPaletteType, int step);
	static void createAllPalettesTest();
public:
	ColorPaletteCreator() noexcept;
	ColorPalette createPaletteFromRangePoints(ColorPalettesClass colorPaletteType, int step);
	void addColorPaletteRangePoint(Color colorRangePoint) noexcept;
	void addColorPaletteRangePoints(std::vector<ColorsEnum> colors) noexcept;
};

