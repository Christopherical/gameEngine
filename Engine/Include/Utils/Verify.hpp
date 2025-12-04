#pragma once

#include <cassert>

// If it's in release my asserts won't remove code like loadFromFile.
#ifdef NDEBUG
    #define VERIFY(expr) void(expr)
#else
    #define VERIFY(expr) assert(expr)
#endif