#pragma once
#pragma pack(2)
#include <vector>

namespace Colors
{
	struct Color;
	class ColorPalette;
	enum class ColorPalettesClass;
	enum class ColorsEnum : uint32_t;

	class ColorPaletteCreator
	{
	private:
		std::vector<Color> rangeColors_;
	public:
		static ColorPalette createPalette(const ColorPalettesClass& colorPaletteType, int step);
		static void createAllPalettesTest();
	public:
		ColorPaletteCreator() noexcept;
		ColorPalette createPaletteFromRangePoints(const ColorPalettesClass& colorPaletteType, int step);
		void addColorPaletteRangePoint(const Color& colorRangePoint) noexcept;
		void addColorPaletteRangePoints(const std::vector<ColorsEnum>& colors) noexcept;
	};

}