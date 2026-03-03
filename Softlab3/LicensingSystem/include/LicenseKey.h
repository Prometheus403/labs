#pragma once
#include <string>
#include <ctime>
struct LicenseKey{
 std::string hardwareHash;
 std::time_t expiration;
 std::string checksum;
 std::string Serialize() const;
 static LicenseKey Deserialize(const std::string& data);
};
