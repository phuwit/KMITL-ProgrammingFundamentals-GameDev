#include "GetOS.hpp"

OS getOS() {
    #ifdef _WIN32
    return OS::OS_WINDOWS;
    #elif _WIN64
    return OS::OS_WINDOWS;
    #elif __linux__
    return OS::OS_LINUX;
    #elif __APPLE__ || __MACH__
    return OS::OS_MAC;
    #else
    return OS::OS_OTHER;
    #endif
}