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

// OpenGL specific headers, currently commented out to avoid errors
#ifdef OpenGL
//#define GLEW_STATIC
#include <glew.h>
#endif

// DirectX12 specific headers
#ifdef DX12
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>

#include <DirectXMath.h>
#endif

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_NATIVE_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <GLFW/glfw3native.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <wrl.h>

#include "GlobalValues.h"