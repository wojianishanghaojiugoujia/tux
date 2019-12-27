#pragma once
#include <iostream>

#ifdef DEBUG
#define TUX_DEBUG(x) std::cout << __DATE__ << " " << __TIME__ << "[TUX DEBUG] " \
                               << x << std::endl;
#else
#define TUX_DEBUG(x) \
    do               \
    {                \
    } while (0);
#endif

#define TUX_INFO(x) std::clog << __DATE__ << " " << __TIME__ << "[TUX INFO] " \
                              << x << std::endl;

#define TUX_ERROR(x) std::cerr << __DATE__ << " " << __TIME__ << "[TUX ERROR] " \
                               << " " << x << " FILE:" << __FILE__ << "#" << __LINE__ << std::endl;
