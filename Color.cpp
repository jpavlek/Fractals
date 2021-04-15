#include "Color.h"
#include <iostream>
#include <string>

void Color::setColor(uint8_t red, uint8_t green, uint8_t blue) noexcept
{
	red_ = red;
	green_ = green;
	blue_ = blue;
}

void Color::setColor(ColorsEnum colorEnum) noexcept
{
	red_ = static_cast<int>(colorEnum) % 0x1000000;
	green_ = static_cast<int>(colorEnum) % 0x10000;
	blue_ = static_cast<int>(colorEnum) % 0x100;

#ifdef DEBUG
	std::cout << "setColor(" << (int)red_ << ", " << (int)green_ << ", " << (int)blue_ << ") ";
#endif // DEBUG
}

void Color::setColor(Color color) noexcept
{
	red_ = color.red_;
	green_ = color.green_;
	blue_ = color.blue_;
}

void Color::setColor(ColorInt color) noexcept
{
	red_ = (uint8_t) color.red_;
	green_ = (uint8_t) color.green_;
	blue_ = (uint8_t) color.blue_;
}

std::string Color::toString(const ColorsEnum colorEnum)
{
	std::string colorName = "";
	switch (colorEnum)
	{
	case ColorsEnum::Black:
		colorName = "Black";
		break;
	case ColorsEnum::Blue:
		colorName = "Blue";
		break;
	case ColorsEnum::Cyan:
		colorName = "Cyan";
		break;
	case ColorsEnum::Green:
		colorName = "Green";
		break;
	case ColorsEnum::Indigo:
		colorName = "Indigo";
		break;
	case ColorsEnum::Magenta:
		colorName = "Magenta";
		break;
	case ColorsEnum::Orange:
		colorName = "Orange";
		break;
	case ColorsEnum::Purple:
		colorName = "Purple";
		break;
	case ColorsEnum::Red:
		colorName = "Red";
		break;
	case ColorsEnum::Violet:
		colorName = "Violet";
		break;
	case ColorsEnum::White:
		colorName = "White";
		break;
	case ColorsEnum::Yellow:
		colorName = "Yellow";
		break;
	default:
		colorName = "DefaultColor";
		break;
	}
	return colorName;
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue) noexcept:
	red_{red}, 
	green_{green}, 
	blue_{blue}
{
}

Color::Color(ColorsEnum colorEnum) noexcept:
	red_{ (uint8_t) (static_cast<int>(colorEnum) >> 16) },
	green_{ (uint8_t) (static_cast<int>(colorEnum) << 16 >> 24) },
	blue_{ (uint8_t) (static_cast<int>(colorEnum) << 24 >> 24) }
{
}

Color Color::operator-(const Color& other) noexcept
{
	uint8_t red = (red_ > other.red_) ? red_ - other.red_ : 256 + red_ - other.red_;
	uint8_t green = (green_ > other.green_) ? green_ - other.green_ : 256 + green_ - other.green_;
	uint8_t blue = (blue_ > other.blue_) ? blue_ - other.blue_ : 256 + blue_ - other.blue_;
	Color result(red, green, blue);
	return result;
}

Color Color::operator+(const Color& other) noexcept
{
	Color result(red_ + other.red_, green_ + other.green_, blue_ + other.blue_);
	return result;
}

ColorInt Color::operator+(const ColorInt&& other) noexcept
{
	return ColorInt((int) red_ + other.red_, (int) green_ + other.green_, (int) blue_ + other.blue_);
}

Color Color::operator/(const int divisor)
{
	int red = (red_ == 255) ? red_ + 1 : red_;
	int green = (green_ == 255) ? green_ + 1 : green_;
	int blue = (blue_ == 255) ? blue_ + 1 : blue_;
	Color result(red/divisor, green/divisor, blue/divisor);
	return result;
}

Color Color::operator*(const int multiplicator) noexcept
{
	Color result(red_ * multiplicator, green_ * multiplicator, blue_ * multiplicator);
	return result;
}

ColorInt ColorInt::operator-(const Color& other) noexcept
{
	int red = red_ - (int) other.red_;
	int green = green_ - (int) other.green_;
	int blue = blue_ - (int) other.blue_;
	ColorInt result(red, green, blue);
	return result;
}

ColorInt ColorInt::operator+(const Color& other) noexcept
{
	int red = red_ + (int)other.red_;
	int green = green_ + (int)other.green_;
	int blue = blue_ + (int)other.blue_;
	ColorInt result(red, green, blue);
	return result;
}

ColorInt ColorInt::operator+(const ColorInt&& other) noexcept
{
	red_ += (int)other.red_;
	green_ += (int)other.green_;
	blue_ += (int)other.blue_;
	return *this;
}

ColorInt& ColorInt::operator=(const ColorInt&& other) noexcept
{
	if (this != &other)
	{
		red_ = (int)other.red_;
		green_ = (int)other.green_;
		blue_ = (int)other.blue_;
	}
	return *this;
}

ColorInt& ColorInt::operator=(ColorInt&& other) noexcept
{
	if (this != &other)
	{
		red_ = (int)other.red_;
		green_ = (int)other.green_;
		blue_ = (int)other.blue_;
	}
	return *this;
}

ColorInt::ColorInt(int red, int green, int blue) noexcept:
	red_{ red },
	green_{ green },
	blue_{ blue }
{
}

ColorInt::ColorInt(const Color& other) noexcept:
	red_{ other.red_ },
	green_{ other.green_ },
	blue_{ other.blue_ }
{
}

ColorInt::ColorInt(ColorInt& other) noexcept:
	red_{ other.red_ },
	green_{ other.green_ },
	blue_{ other.blue_ }
{
}

ColorInt ColorInt::operator/(const int divisor)
{
	int red = (red_ == 255) ? red_ + 1 : red_;
	int green = (green_ == 255) ? green_ + 1 : green_;
	int blue = (blue_ == 255) ? blue_ + 1 : blue_;
	ColorInt result(red / divisor, green / divisor, blue / divisor);
	return result;
}

ColorInt ColorInt::operator()(const Color& other) noexcept
{
	return ColorInt(other.red_, other.green_, other.blue_);
}

ColorInt ColorInt::operator*(const int multiplicator) noexcept
{
	return ColorInt(red_ * multiplicator, green_ * multiplicator, blue_ * multiplicator);
}

ColorInt::ColorInt(ColorInt&& other) noexcept:
	red_{ std::move(other.red_) },
	green_{ std::move(other.green_) },
	blue_{ std::move(other.blue_) }
{
}
