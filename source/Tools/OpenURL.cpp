#include "OpenURL.hpp"

void openURL(std::string url) {
	std::string str;
    switch (getOS()) {
        case OS::OS_WINDOWS:
            str = "explorer";
            break;
        case OS::OS_LINUX:
            str = "xdg-open";
            break;
        case OS::OS_MAC:
            str = "open";
            break;
        default:
            std::cout << "Should never happen on the 3 defined platforms"
                      << std::endl;
    }
    str.append(" " + url);
    std::system(str.data());
}