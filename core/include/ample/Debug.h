#pragma once
#include <cassert>
#include <iostream>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define DEBUG(expr) std::cerr << __FILENAME__ << ' ' << __LINE__ << ": " << (expr) << std::endl
#ifdef NDEBUG
#define ASSERT(EX)
#else
#define ASSERT(EX) (void)((EX) || (__assert(#EX, __FILE__, __LINE__), 0))
#endif
