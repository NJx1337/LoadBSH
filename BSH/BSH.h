#pragma once

#include <vector>
//#include "Image8.h"
#include "Gfx.h"

#define BSH_HEADER_LENGTH 20

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
	BSH(const char* bshFileName, const Palette& palette);
	~BSH();

	void setPalette(const Palette& palette);
	///inline Palette* GetPalette() const { return m_palette; }
	inline SPixel* GetPalettePixelArray() const { return m_pltPxl; }

	// Adds an image to the SPixel array
	void AddGfx(int width, int height, SPixel* PixelArray);

	// Pre allocate memory size on known bsh-image-count
	void AllocateMemorySize(size_t newSize);

	SPixel GetAlphaPixel() const;
	inline int GetGfxArraySize() const { return m_gfx_size; }
	inline SGfx GetGfxId(int Idx) const { return m_gfx[Idx]; }
};

