#pragma once

#include <bitset>
#include <array>
#include <vector>

class ProcessorFeatureSet
{
private:
	std::array<int, 4> cpui;
	int nIds_;
	int nExIds_;
	std::bitset<32> f_1_ECX_{ 0 };
	std::bitset<32> f_1_EDX_{ 0 };

	std::bitset<32> f_7_EBX_{ 0 };
	std::bitset<32> f_7_ECX_{ 0 };

	std::bitset<32> f_81_ECX_{ 0 };
	std::bitset<32> f_81_EDX_{ 0 };
	std::vector<std::array<int, 4>> data_;
	std::vector<std::array<int, 4>> extdata_;
	std::string vendor_;
	std::string brand_;

public:
	static void checkProcessorFeatures();
public:
	ProcessorFeatureSet();
};

