#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#if defined(CreateWindow)
#undef CreateWindow
#endif

#include <iostream>
#include <stdio.h>
#include <cassert>

#include <algorithm>
#include <chrono>
#include <string>
#include <vector>

//#define GLEW_STATIC
#include <glew.h>
#include "GLFW/glfw3.h"