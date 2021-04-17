#pragma once
#pragma pack(2)
#include <memory>
#include <string>

namespace Colors
{
	struct Color;
}

namespace FileSystem
{

	class Bitmap
	{
	private:
		int width_{ 0 };
		int height_{ 0 };
		std::unique_ptr<uint8_t[]> pPixels_{ nullptr };
	public:
		Bitmap(int width, int height);
		void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
		void setPixel(int x, int y, const Colors::Color& color);
		bool write(const std::string& filename);
		virtual ~Bitmap();
		Bitmap(const Bitmap&) = default;
		Bitmap(Bitmap&&) = default;

		Bitmap& operator=(const Bitmap&) = default;
		Bitmap& operator=(Bitmap&&) = default;
	};

}
