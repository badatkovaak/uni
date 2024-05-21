#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>

// Unsigned int types.
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Signed int types.
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// Floating point types
typedef float f32;
typedef double f64;

typedef void* voids;
typedef char* chars;

#define nullptr ((void*)0)

// Boolean types
// typedef u8 b8;
// typedef u32 b32;

#define true 1
#define false 0

#endif  // !DEFINES_H
