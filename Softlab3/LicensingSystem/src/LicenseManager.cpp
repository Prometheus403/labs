#include "LicenseManager.h"
#include "HardwareID.h"
#include <fstream>
#include <ctime>
bool LicenseManager::CreateLicense(bool temporary){
 LicenseKey key;
 key.hardwareHash=HardwareID::GenerateHardwareHash();
 key.expiration=temporary?std::time(nullptr)+30*24*60*60:0;
 key.checksum=key.hardwareHash+std::to_string(key.expiration);
 std::ofstream file("license.dat");
 file<<key.Serialize();
 file.close();
 return true;
}
bool LicenseManager::ValidateLicense(){
 std::ifstream file("license.dat");
 if(!file) return false;
 std::string content((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
 file.close();
 LicenseKey key=LicenseKey::Deserialize(content);
 if(HardwareID::GenerateHardwareHash()!=key.hardwareHash) return false;
 if(key.expiration!=0 && std::time(nullptr)>key.expiration) return false;
 return true;
}
