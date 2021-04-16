#include "ProcessorFeatureSet.h"

#ifdef _WIN32
#include <intrin.h>
#endif

#include <stdio.h>
#include <iostream>
#include <string>

void ProcessorFeatureSet::checkProcessorFeatures()
{
    ProcessorFeatureSet PFS;

    std::cout << "CPU Vendor: " << PFS.vendor_ << "\n";
    std::cout << "Brand: " << PFS.brand_ << "\n";

    std::string supportedEnhancedInstructionSets = "Enhanced Instruction Sets Supported: ";
    if (PFS.f_1_EDX_[25])
    {
        supportedEnhancedInstructionSets += "| SSE ";
    }
    if (PFS.f_1_EDX_[26])
    {
        supportedEnhancedInstructionSets += "| SSE2 ";
    }
    if (PFS.f_1_ECX_[19])
    {
        supportedEnhancedInstructionSets += "| SSE41 ";
    }
    if (PFS.f_1_ECX_[20])
    {
        supportedEnhancedInstructionSets += "| SSE42 ";
    }
    if (PFS.f_1_ECX_[28])
    {
        supportedEnhancedInstructionSets += "| AVX ";
    }

    if (PFS.f_7_EBX_[5])
    {
        supportedEnhancedInstructionSets += "| AVX2 ";
    }

    if (PFS.f_7_EBX_[16])
    {
        supportedEnhancedInstructionSets += "| AVX512F ";
    }

    supportedEnhancedInstructionSets += "|\n\n";
    std::cout << supportedEnhancedInstructionSets;
}

ProcessorFeatureSet::ProcessorFeatureSet()
{
    // Calling __cpuid with 0x0 as the function_id argument
    // gets the number of the highest valid function ID.
    __cpuid(cpui.data(), 0);
    nIds_ = cpui[0];

#ifdef _DEBUG
    std::cout << "nIds_: " << std::to_string(nIds_) << "\n";
#endif // _DEBUG

    for (int i = 0; i <= nIds_; ++i)
    {
        __cpuidex(cpui.data(), i, 0);
        data_.push_back(cpui);
    }

    // load bitset with flags for function 0x00000001
    if (nIds_ >= 1)
    {
        f_1_ECX_ = data_[1][2];
        f_1_EDX_ = data_[1][3];
    }

    // load bitset with flags for function 0x00000007
    if (nIds_ >= 7)
    {
        f_7_EBX_ = data_[7][1];
        f_7_ECX_ = data_[7][2];
    }

    // Capture vendor string
    char vendor[0x20];
    memset(vendor, 0, sizeof(vendor));
    *reinterpret_cast<int*>(vendor) = data_[0][1];
    *reinterpret_cast<int*>(vendor + 4) = data_[0][3];
    *reinterpret_cast<int*>(vendor + 8) = data_[0][2];
    vendor_ = vendor;

    // Calling __cpuid with 0x80000000 as the function_id argument
    // gets the number of the highest valid extended ID.
    __cpuid(cpui.data(), 0x80000000);
    nExIds_ = cpui[0];

    char brand[0x40];
    memset(brand, 0, sizeof(brand));

    for (int i = 0x80000000; i <= nExIds_; ++i)
    {
        __cpuidex(cpui.data(), i, 0);
        extdata_.push_back(cpui);
    }

    // load bitset with flags for function 0x80000001
    if (nExIds_ >= 0x80000001)
    {
        f_81_ECX_ = extdata_[1][2];
        f_81_EDX_ = extdata_[1][3];
    }

    // Interpret CPU brand string if reported
    if (nExIds_ >= 0x80000004)
    {
        memcpy(brand, extdata_[2].data(), sizeof(cpui));
        memcpy(brand + 16, extdata_[3].data(), sizeof(cpui));
        memcpy(brand + 32, extdata_[4].data(), sizeof(cpui));
        brand_ = brand;
    }
}
