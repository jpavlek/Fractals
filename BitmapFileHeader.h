#pragma once

#pragma pack(2)

struct BitmapFileHeader
{
	int32_t filesize_{ -1 };
	int32_t reserved_{ 0 };
	int32_t dataOffset_{ -1 };
	char header_[2]{'B', 'M'};
};