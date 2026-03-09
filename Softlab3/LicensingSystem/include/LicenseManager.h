#pragma once
#include "LicenseKey.h"

class LicenseManager {
public:
    static bool CreateLicense(bool temporary);
    static bool ValidateLicense();
};
