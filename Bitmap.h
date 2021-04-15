#pragma once
#include <memory>
#include <string>
#pragma pack(2)
struct Color;

class Bitmap
{
private:
	int width_{ 0 };
	int height_{ 0 };
	std::unique_ptr<uint8_t[]> pPixels_{ nullptr };
public:
	Bitmap(int width, int height);
	void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
	void setPixel(int x, int y, Color color);
	bool write(std::string filename);
	virtual ~Bitmap();
	Bitmap(const Bitmap&) = default;
	Bitmap(Bitmap&&) = default;

	Bitmap& operator=(const Bitmap&) = default;
	Bitmap& operator=(Bitmap&&) = default;
};