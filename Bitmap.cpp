#pragma pack(2)
#include "Bitmap.h"
#include "Color.h"
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"
#include <fstream>
#include <iostream>

namespace Colors
{
	struct Color;
}

namespace FileSystem
{

	Bitmap::Bitmap(int width, int height) :
		width_(width),
		height_(height),
		pPixels_(new uint8_t[width * height * 3])
	{
	}

	void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
	{
		uint8_t* pPixel = pPixels_.get();
		pPixel += (y * 3) * width_ + (x * 3);
		pPixel[0] = blue;
		pPixel[1] = green;
		pPixel[2] = red;
	}

	void Bitmap::setPixel(int x, int y, const Colors::Color& color)
	{
		uint8_t red = color.red_;
		uint8_t green = color.green_;
		uint8_t blue = color.blue_;
		setPixel(x, y, red, green, blue);
	}

	bool Bitmap::write(const std::string& filename)
	{
		BitmapFileHeader fileHeader;
		BitmapInfoHeader infoHeader;

		fileHeader.dataOffset_ = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

		fileHeader.filesize_ = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + width_ * height_ * 3;
		infoHeader.width_ = width_;
		infoHeader.heigth_ = height_;

		std::ofstream file;
		file.open(filename, std::ios::out | std::ios::binary);

		if (!file)
		{
			std::cout << "\nFile: " << filename << " could not be opened...\n";
			return false;
		}

		file.write((char*)&fileHeader, sizeof(fileHeader));
		file.write((char*)&infoHeader, sizeof(infoHeader));
		file.write((char*)pPixels_.get(), width_ * height_ * 3);

		file.close();

		if (!file)
		{
			return false;
		}

		return true;
	}

	Bitmap::~Bitmap()
	{
	}

}