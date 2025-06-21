#pragma once

#include <vector>
//#include "Image8.h"
#include "Gfx.h"

#define BSH_HEADER_LENGTH 20

class Image8;
class Palette;
//class BSHFile;

class BSH
{
private:
	//std::vector<Image8> m_images;
	SPixel* m_pltPxl = nullptr;
	SGfx* m_gfx = nullptr;
	int m_gfx_size = 0; // Size of Array with Gfx
	int m_gfx_sizeAllocated = 0; // Gfx-ArraySize that is preallocated in memory

	uint8_t m_alpha_paletteId = 253;

public:
	//BSH(const char* bshFileName);
	BSH(const char* bshFileName, Palette* palette);

	void setPalette(Palette* palette);
	///inline Palette* GetPalette() const { return m_palette; }
	void AddGfx(int width, int height, SPixel* PixelArray);
	inline SPixel* GetPalettePixelArray() const { return m_pltPxl; }
	inline int GetGfxArraySize() const { return m_gfx_size; }

	SPixel GetAlphaPixel() const;

	inline SGfx GetGfxId(int Idx) const { return m_gfx[Idx]; }
};

