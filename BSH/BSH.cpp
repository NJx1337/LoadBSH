#include "BSH.h"

#include "Palette.h"
#include "BSHFile.h"
#include "BSHDebug.h"

BSH::BSH(const char* bshFileName, Palette* palette)
{
	setPalette(palette);
	BSHFile* fileHandler = new BSHFile(bshFileName, this);
	//loadBSH(bshFileName);
}

void BSH::setPalette(Palette* palette)
{
	m_pltPxl = palette->getArray();
}

void BSH::AddGfx(int width, int height, SPixel* PixelArray)
{
	if (m_gfx_size == m_gfx_sizeAllocated) // Check if memory needs to be allocated
	{
		// Resize memory
		SGfx* tmp = (SGfx*)(m_gfx_size > 0 ? realloc(m_gfx, (m_gfx_size + 1) * sizeof(SGfx)) : malloc(1 * sizeof(SGfx)));

		if (tmp)
		{
			++m_gfx_size;
			++m_gfx_sizeAllocated;
			m_gfx = tmp;
		}
	}

	//STileTypeInfo* ref = ParentId == -1 ? &m_Defaults_TileTypeInfo : &m_TileTypes[ParentId];
	//memcpy(&m_TileTypes[m_TileTypes_size - 1], &m_Defaults_TileTypeInfo, sizeof(STileTypeInfo));
	//memcpy(&m_TileTypes[m_TileTypes_size - 1], ParentId == -1 ? &m_Defaults_TileTypeInfo : &m_TileTypes[ParentId], sizeof(STileTypeInfo));

	m_gfx[m_gfx_size - 1] = SGfx(width, height, PixelArray);

	///memcpy(&m_TileTypes[m_TileTypes_size - 1], ParentId != -1 && ParentId < (m_TileTypes_size - 1) ? &m_TileTypes[ParentId] : &m_Defaults_TileTypeInfo, sizeof(STileTypeInfo));
}

SPixel BSH::GetAlphaPixel() const
{
	if (!m_pltPxl) return SPixel();

	return m_pltPxl[m_alpha_paletteId];
}
