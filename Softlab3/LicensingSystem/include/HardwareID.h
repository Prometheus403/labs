#pragma once
#include <string>

class HardwareID {
public:
    static std::string GetCPUId();
    static std::string GetMotherboardSerial();
    static std::string GetMACAddress();
    static std::string GenerateHardwareHash();
};
