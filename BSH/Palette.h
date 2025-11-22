#pragma once

#define PALETTE_FILE "bsh_files/STADTFLD.COL"
#define PALETTE_HEADER_LENGTH 20

#include "Gfx.h"

class Palette
{
private:
	void readPalette(const char* colPaletteFileName);
	int argbToInt(int a, int r, int g, int b);

	//int m_palette[256];
	SPixel m_palette[256];

public:
	Palette(const char* paletteFileName);
	inline SPixel& getArray() const { return (SPixel&) m_palette; };
	void printPalette();
};

