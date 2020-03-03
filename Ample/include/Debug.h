#pragma once
#include <string.h>
#include <iostream>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define DEBUG(expr) std::cerr << __FILENAME__ << ' ' << __LINE__ << ": " << (expr) << std::endl
