#pragma once

/// @brief Popular macro for the C macro preprocessor

#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))
#define CONSTSTRLEN(s) (sizeof(s)-1)
