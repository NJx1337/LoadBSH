#include "BSHDebug.h"
#include "BSH.h"
#include "Gfx.h"
#include "../CImg.h"

void BSHDebug::ShowBSHIdx(BSH* bshIn, int idx)
{
	const SGfx& gfx = bshIn->GetGfxId(idx);

	cimg_library::CImg<unsigned char> img(gfx.Width, gfx.Height, 1, 3);

	for (int y = 0; y < gfx.Height; y++)
	{
		for (int x = 0; x < gfx.Width; x++)
		{
			//int pixelID = y * gfx.Width + x;
			int idx = gfx.Width * y + x;
			const SPixel& px = gfx.PixelArray[idx];
			if (y == 0 && x < 2)
			{
				printf("0x%.2X%.2X%.2X\n", px.r, px.g, px.b);
			}
			const float color[] = { (float)px.r, (float)px.g, (float)px.b };
			img.draw_point(x, y, color);
		}
	}

	img.display("img8 test");
}

void BSHDebug::displayAllImages(BSH* bshIn)
{
	for (int i = 0; i < bshIn->GetGfxArraySize(); i++)
	{
		//m_images[i].GetCImg().display("img8 displayAllImages()");
		ShowBSHIdx(bshIn, i);
	}
}
