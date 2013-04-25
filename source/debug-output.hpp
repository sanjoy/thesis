#ifndef __DEBUG_OUTPUT_HPP
#define __DEBUG_OUTPUT_HPP

#ifdef NDEBUG
#define PRINTF(...) do {} while(0)
#define FPRINTF(...) do {} while(0)
#else

#include <cstdio>

#define PRINTF(...) std::fprintf(stderr, __VA_ARGS__)
#define FPRINTF std::fprintf

#endif

#endif // __DEBUG_OUTPUT_HPP
