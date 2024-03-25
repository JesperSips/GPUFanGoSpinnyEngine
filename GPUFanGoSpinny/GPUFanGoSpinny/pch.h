#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#if defined(CreateWindow)
#undef CreateWindow
#endif

struct Vertex
{
    float pos[3] = { 0,0,0 };
    float rgb[3] = { 0,0,0 };
    float tex[2] = { 0,0 };
};

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

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "GlobalValues.h"