#include "Palette.h"
#include <fstream>      // std::filebuf

void Palette::readPalette(const char* paletteFileName)
{
	std::ifstream f;
	char b;

	f.open(paletteFileName, std::ifstream::binary);
	if (f.is_open()) {
		f.seekg(PALETTE_HEADER_LENGTH, f.beg); // skip 20 bytes
		for (int i = 0; i < sizeof(m_palette) / sizeof(m_palette[0]); i++) // Loop through bytes
		{
			f.read(&b, 1);
			uint8_t c_r = b;
			f.read(&b, 1);
			uint8_t c_g = b;
			f.read(&b, 1);
			uint8_t c_b = b;

			f.read(&b, 1); // Skip 1 byte

			//m_palette[i] = (0 << 24) | (c_r << 16) | (c_g << 8) | (c_b << 0);
			m_palette[i] = SPixel(c_r, c_g, c_b);
		}

		f.close();
	}
}

void Palette::printPalette()
{
	printf("Palette:\n");
	for (int i = 0; i < sizeof(m_palette); i++)
	{
		if (i > 0) printf(", ");;
		printf("0x%.2X", m_palette[i].r);
		printf("%.2X", m_palette[i].g);
		printf("%.2X", m_palette[i].b);
	}

	printf(";\n");
}

Palette::Palette(const char* paletteFileName)
{
	readPalette(paletteFileName);
}
