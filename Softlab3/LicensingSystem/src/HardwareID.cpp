#include "HardwareID.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <vector>
#include <netpacket/packet.h> // needed for sockaddr_ll

// Helper: SHA-256 hashing
static std::string sha256(const std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)str.c_str(), str.size(), hash);

    std::ostringstream oss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    return oss.str();
}

// Helper: get CPU model
static std::string getCPUModel() {
    std::ifstream f("/proc/cpuinfo");
    std::string line, result;
    while (std::getline(f, line)) {
        if (line.find("model name") != std::string::npos)
            result += line;
    }
    return result.empty() ? "CPU-UNKNOWN" : result;
}

// Helper: get motherboard serial
static std::string getMotherboardSerial() {
    std::ifstream f("/sys/class/dmi/id/board_serial");
    std::string serial;
    if (f.is_open())
        std::getline(f, serial);
    if (serial.empty())
        serial = "MB-SERIAL-ACADEMIC";
    return serial;
}

// Helper: get MAC address
static std::string getMACAddress() {
    struct ifaddrs *ifap, *ifa;
    char mac[18] = "00:00:00:00:00:00";

    if (getifaddrs(&ifap) == 0) {
        for (ifa = ifap; ifa != nullptr; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_PACKET) {
                struct sockaddr_ll* s = (struct sockaddr_ll*)ifa->ifa_addr;
                if (s->sll_halen == 6) { // check MAC length
                    snprintf(mac, sizeof(mac), "%02x:%02x:%02x:%02x:%02x:%02x",
                             s->sll_addr[0], s->sll_addr[1], s->sll_addr[2],
                             s->sll_addr[3], s->sll_addr[4], s->sll_addr[5]);
                    break;
                }
            }
        }
        freeifaddrs(ifap);
    }
    return std::string(mac);
}

// Class method: Generate hardware hash
std::string HardwareID::GenerateHardwareHash() {
    std::string combined = getCPUModel() + getMotherboardSerial() + getMACAddress();
    return sha256(combined);
}
