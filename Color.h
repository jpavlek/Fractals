#pragma once
#include <cstdint>
#include <string>

namespace Colors
{
	/**
	* Spectral region
	* Range of wavelength in nm	Subregion
	* Ultraviolet
	* 100 - 280	UV - C
	* 280 - 315	UV - B
	* 315 - 380	UV - A
	* Visible
	* 380 - 430	Violet
	* 430 - 500	Blue
	* 520 - 565	Green
	* 565 - 580	Yellow
	* 580 - 625	Orange
	* 625 - 740	Red
	* Infrared
	* 740 - 1400	Near IR
	*1400 - 10000	Far IR
	*/
	enum class ColorsEnum : uint32_t
	{
		Black = 0x00000000,
		Indigo = 0x004B0082,	//Indigo:	445-464 nm
		Purple = 0x006000C0,
		Violet = 0x008000FF,	//Violet:	380–430 nm(688–789 THz frequency)
		Blue = 0x000000FF,	//Blue:		450–495 nm
		Cyan = 0x0000FFFF,	//Cyan:		500-520 nm
		Green = 0x0000FF00,	//Green:	495–570 nm
		White = 0x00FFFFFF,	//White:	380<577<750 nm
		Yellow = 0x00FFFF00,	//Yellow:	570–590 nm
		Orange = 0x00FF8000,	//Orange:	590–620 nm
		Red = 0x00FF0000,	//Red:		620–750 nm(400–484 THz frequency)
		Magenta = 0x00FF00FF,
	};

	struct Color;
	struct ColorInt
	{
	public:
		int red_ = 0;
		int green_ = 0;
		int blue_ = 0;
	public:
		ColorInt(int red = 0, int green = 0, int blue = 0) noexcept;
		ColorInt(const Color& other) noexcept;
		ColorInt(ColorInt& other) noexcept;
		ColorInt(ColorInt&& other) noexcept;
		ColorInt operator-(const Color& other) noexcept;
		ColorInt operator+(const Color& other) noexcept;
		ColorInt operator+(const ColorInt&& other) noexcept;
		ColorInt& operator=(const ColorInt&& other) noexcept;
		ColorInt& operator=(ColorInt&& other) noexcept;
		ColorInt operator/(const int divisor);
		ColorInt operator()(const Color& other) noexcept;
		ColorInt operator*(const int multiplicator) noexcept;
	};

	struct Color
	{
	public:
		uint8_t red_ = 0;
		uint8_t green_ = 0;
		uint8_t blue_ = 0;
	public:
		static std::string toString(const ColorsEnum colorEnum);
	public:
		Color(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0) noexcept;
		Color(ColorsEnum colorEnum) noexcept;
		Color operator-(const Color& other) noexcept;
		Color operator+(const Color& other) noexcept;
		ColorInt operator+(const ColorInt&& other) noexcept;
		Color operator/(const int divisor);
		Color operator*(const int multiplicator) noexcept;
		void setColor(ColorsEnum colorEnum) noexcept;
		void setColor(Color color) noexcept;
		void setColor(ColorInt color) noexcept;
		void setColor(uint8_t red, uint8_t green, uint8_t blue) noexcept;
	};

} // namespace Colors