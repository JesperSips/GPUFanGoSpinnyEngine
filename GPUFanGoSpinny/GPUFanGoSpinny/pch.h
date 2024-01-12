#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#if defined(CreateWindow)
#undef CreateWindow
#endif

#include <stdio.h>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <string>