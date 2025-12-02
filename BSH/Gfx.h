#pragma once
#include <widemath.h>

#define C_SPIXEL_DEFAULT 0xFF00FF // Default value (standard alpha)

struct SPixel
{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	SPixel()
		: r(255), g(0), b(255)
	{
	}
	SPixel(uint8_t r_in, uint8_t g_in, uint8_t b_in)
		: r(r_in), g(g_in), b(b_in)
	{
	}
};

struct SGfx
{
	int Width;
	int Height;
	SPixel* PixelArray;

	//SGfx()
	//	: Width(1), Height(1), PixelArray(nullptr)
	//{}

	SGfx(int _Width, int _Height)
		: Width(_Width), Height(_Height), PixelArray(nullptr)
	{
		//mem alloc w*h
	}

	SGfx(int _Width, int _Height, SPixel* _PixelArray)
		: Width(_Width), Height(_Height), PixelArray(_PixelArray)
	{ }
};
