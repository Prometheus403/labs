cmake_minimum_required(VERSION 3.15)
project(LicensingSystem VERSION 1.0 LANGUAGES CXX)

# ── C++ standard ──────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Find OpenSSL ──────────────────────────────────────────────────────────────
find_package(OpenSSL REQUIRED)

# ── Sources ───────────────────────────────────────────────────────────────────
set(SOURCES
    src/HardwareID.cpp
    src/LicenseKey.cpp
    src/LicenseManager.cpp
    src/main.cpp
)

# ── Executable ────────────────────────────────────────────────────────────────
add_executable(LicensingSystem ${SOURCES})

target_include_directories(LicensingSystem
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(LicensingSystem
    PRIVATE
        OpenSSL::Crypto
)

# ── Compiler warnings ─────────────────────────────────────────────────────────
target_compile_options(LicensingSystem PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

# ── Install rules (optional) ──────────────────────────────────────────────────
install(TARGETS LicensingSystem DESTINATION bin)
