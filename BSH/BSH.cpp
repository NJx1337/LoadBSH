#include "BSH.h"

#include "Palette.h"
#include "BSHFile.h"
#include "BSHDebug.h"

BSH::BSH(const char* bshFileName, const Palette& palette)
{
	setPalette(palette);
	BSHFile* fileHandler = new BSHFile(bshFileName, this);
	//loadBSH(bshFileName);
}

BSH::~BSH()
{
	//while (m_gfx_size > 0)
	//	free(&m_gfx[--m_gfx_size]);
	//if (m_gfx != nullptr) delete[] m_gfx;
}

void BSH::setPalette(const Palette& palette)
{
	m_pltPxl = &palette.getArray();
}

void BSH::AddGfx(int width, int height, SPixel* PixelArray)
{
	if (m_gfx_size == m_gfx_sizeAllocated) // Check if memory needs to be allocated
	{
		// Resize memory
		SGfx* tmp = (SGfx*)(m_gfx_size > 0 ? realloc(m_gfx, (m_gfx_size + 1) * sizeof(SGfx)) : malloc(1 * sizeof(SGfx)));

		if (tmp)
		{
			++m_gfx_sizeAllocated;
			m_gfx = tmp;
		}
	}

	m_gfx[m_gfx_size++] = SGfx(width, height, PixelArray);
}

void BSH::AllocateMemorySize(size_t newSize)
{
	if (newSize != m_gfx_sizeAllocated)
	{
		SGfx* tmp = (SGfx*)(m_gfx_size > 0 ? realloc(m_gfx, newSize * sizeof(SGfx)) : malloc(newSize * sizeof(SGfx)));
		
		if (tmp)
		{
			m_gfx = tmp;
			m_gfx_sizeAllocated = (int)newSize;
		}
	}
}

SPixel BSH::GetAlphaPixel() const
{
	if (!m_pltPxl) return SPixel();

	return m_pltPxl[m_alpha_paletteId];
}
