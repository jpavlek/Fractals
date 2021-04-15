#pragma once
#pragma pack(2)

struct BitmapInfoHeader
{
	int32_t headerSize_{ 40 };
	int32_t width_{ 0 };
	int32_t heigth_{ 0 };
	int32_t compression_{ 0 };
	int32_t dataSize_{ 0 };
	int32_t horizontalResolution_{ 2400 };
	int32_t verticalResolution_{ 2400 };
	int32_t colors_{ 0 };
	int32_t importantColors_{ 0 };
	int16_t planes_{ 1 };
	int16_t bitsPerPixel_{ 24 };
};