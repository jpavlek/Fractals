#pragma once
#pragma pack(2)
#include "Color.h"
#include <string>
#include "Bitmap.h"
#include <vector>

enum class ColorPalettesClass
{
	RGBCube3,	// 3 x 256 color transitions on a RGB cube (Blue-Green-Red-Blue, up to 768 colors in total).
	RGBCube4,	// 4 x 256 color transitions on a RGB cube (Black-Blue-Green-Red-Blue, up to 1024 colors in total).
	RGBCube5,	// 5 x 256 color transitions on a RGB cube, up to 1280 colors in total.
	RGBCube6,	// 6 x 256 color transitions on a RGB cube, up to 1536 colors in total.
	RGBCube10,	//10 x 256 color transitions on a RGB cube (Black-Blue-Green-Red-Blue-White-Green-Black-Red-White-Black, up to 2560 colors in total).
	RGBRainbow10, // Colors of the rainbow.
	RGBSpectrum10 // Spectrum of colors including black and white.
};

class ColorPalette
{
public:
	static constexpr const int COLOR_RESOLUTION = 256;
	static constexpr const int MAX_COLOR_VALUE = COLOR_RESOLUTION - 1;
	static constexpr const int MAX_PALETTE_SIZE = 10 * COLOR_RESOLUTION;
	static constexpr const int DEFAULT_PALETTE_SIZE = 4 * COLOR_RESOLUTION;
	static constexpr const int SMALL_PALETTE_SIZE = 1 * COLOR_RESOLUTION;
	static constexpr const int DEFAULT_PALETTE_BITMAP_HEIGHT = 50;

public:
	std::vector<Color> colorPalette_;
private:
	int paletteSize_ = DEFAULT_PALETTE_SIZE;
	std::string paletteName_ = "DefaultPalette";

public:
	static std::string toString(const ColorPalettesClass& colorEnum);

public:
	ColorPalette(std::string paletteName, int paletteSize, std::vector<Color> colorPalette) noexcept;
	ColorPalette() noexcept;
	ColorPalette(const ColorPalette& colorPalette) noexcept;
	ColorPalette(ColorPalette&& colorPalette) noexcept;
	ColorPalette& operator=(const ColorPalette& colorPalette) noexcept;
	ColorPalette& operator=(ColorPalette&& colorPalette) noexcept;
	~ColorPalette() noexcept;
	Color getColor(int colorIndex) const noexcept;
	int getPaletteSize() const noexcept;
	std::string getPaletteName() const noexcept;
	void saveColorPaletteAsBitmapFile(std::string fileName) noexcept;

private:
	void setPalette(int paletteSize = DEFAULT_PALETTE_SIZE) noexcept;
	void setPaletteName(std::string paleteName) noexcept;
	void saveColorPaletteAsBitmapFile() noexcept;
};

