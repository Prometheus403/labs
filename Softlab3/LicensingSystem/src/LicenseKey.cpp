#include "LicenseKey.h"
#include <sstream>
std::string LicenseKey::Serialize() const{
 std::ostringstream oss;
 oss<<hardwareHash<<"\n"<<expiration<<"\n"<<checksum;
 return oss.str();
}
LicenseKey LicenseKey::Deserialize(const std::string& data){
 std::istringstream iss(data);
 LicenseKey key;
 iss>>key.hardwareHash>>key.expiration>>key.checksum;
 return key;
}
