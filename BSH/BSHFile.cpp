#include "BSHFile.h"
#include <fstream>      // std::filebuf

#include "BSH.h"
#include "Gfx.h"

BSHFile::BSHFile(const char* bshFileName, BSH* bshObj)
{
	m_BSH = bshObj;
	readBSH(bshFileName);
}

void BSHFile::readBSH(const char* fileName)
{
	if (!m_BSH) return; // BSH object not loaded!

	std::ifstream f;

	if (!m_BSH->GetPalettePixelArray()) // Palette not set!
	{
		printf("Error BSHFile::readBSH(): Palette is not set!\n");
		return;
	}

	SPixel* pltpx = m_BSH->GetPalettePixelArray();

	f.open(fileName, std::ios::binary); // Open BSH file in binary
	if (f.is_open()) // Check if open was successfully
	{
		f.seekg(20, f.beg); // skip 20 bytes (BSH header) //ToDo: Add check for valid BSH header

		// Print header:
		//char c;
		//for (int i = 0; i < 20; ++i)
		//{
		//	f.read(&c, 1);
		//	//printf("%c", c);
		//	printf("\\%02hhx", c);
		//}
		//printf("\n");

		// List of offsets to all images
		std::vector<int> offsetlist;

		// Get all other image offsets
		for (int offset; offsetlist.size() < 1 || ((int)f.tellg() + sizeof(offset)) <= offsetlist[0];) // Iterate through first offset address
		{
			f.read(reinterpret_cast<char*>(&offset), sizeof(offset));
			offset += BSH_HEADER_LENGTH;

			offsetlist.push_back(offset);
		}
		///printf("offs-size: %d\n", (int) offsetlist.size());

		//for (int i = 0; i < offsetlist.size(); i++)
		//{
			//std::cout << "O(" << f.tellg() << "): " << offsetlist[i] << std::endl;
			//printf("O(%d): %d\n", (int)f.tellg(), offsetlist[i]);
		//}

		// Read images:
		for (int i = 0; i < offsetlist.size(); i++)
		{
			f.seekg(offsetlist[i], f.beg);
			//int x = 0;
			//int y = 0;

			// Read width and height
			int width, height;
			f.read(reinterpret_cast<char*>(&width), sizeof(width));
			f.read(reinterpret_cast<char*>(&height), sizeof(height));
			//printf("Img (%d,%d)\n", width, height);

			//ToDo:Continue with Bitmap class and store pixel then save .bmp

			///Image8 img(width, height);
			///img.SetPalette(m_palette);

			// Skip 8 bytes:
			f.ignore(8);

			// allocate for known image with width & height
			SPixel* pxArray = (SPixel*)malloc(width * height * sizeof(SPixel));

			// Temporary byte used to get different values
			char c;
			bool ignoreLine = false; // Color pixel got written to the last pixel, alpha pixel override of line ignored

			for (int y = 0; y < height;)
			{
				bool clrPxlMode = false; // If true: Handles color pixels, if false: handles pre alpha pixels of line

				//int x = 0;
				for (int x = 0; x < width;)
				{
					f.read(&c, 1); // Get byte
					uint8_t b = c;

					if (b >= 254) // End of y row or end of image
					//if (b == 254 || b == 255) // End of y row or end of image
					{
						//printf(b == 254 ? "EoR: %d\n" : ">>>>>EoI: %d\n", b);

						// Add remaining alpha pixels in current y row if x hasn't finished yet

						if (!ignoreLine)
						{
							for (; x < width; ++x)
							{
								int idx = width * y + x;
								pxArray[idx] = m_BSH->GetAlphaPixel();
							}
						}

						if (b == 255) // End of image
						{
							//printf(">>>>>EoI: %d (y:%d, w:%d)\n", b, y, height);
							// Add remaining alpha pixels in next y rows
							for (y += 1; y < height; ++y) // start with next y row
							{
								for (x = 0; x < width; ++x)
								{
									int idx = width * y + x;
									pxArray[idx] = m_BSH->GetAlphaPixel();
								}
							}
						}
						else
						{
							//if (i == 0) printf("\n");
							++y;
							x = 0;
							ignoreLine = false;
						}
					}
					else
					{
						if (!clrPxlMode) // Get pre alpha pixels
						{
							// Get count of alpha pixels before the first color pixel starts:
							uint8_t preAlphaPixelNum = b;
							//printf("preAlphaPixelNum: %d\n", preAlphaPixelNum);

							//if (i == 0) printf("a%d ", y);
							for (preAlphaPixelNum += x; x < preAlphaPixelNum; ++x)
							{
								int idx = width * y + x;
								pxArray[idx] = m_BSH->GetAlphaPixel();
							}

							clrPxlMode = true;
							ignoreLine = false;
						}
						else // Get color pixels
						{
							uint8_t colorPixelNum = b;

							//if (i == 0) printf("c%d ", y);
							//printf("clrPxl: %d\n", colorPixelNum);
							for (colorPixelNum += x; x < colorPixelNum; ++x)
							{
								f.read(&c, 1);
								uint8_t pltIdx = c; // Color index of current pixel in palette
								//printf("pltIdx: %d\n", pltIdx);

								int idx = width * y + x;
								pxArray[idx] = pltpx[pltIdx];
							}
							//if (x == width) --x;
							clrPxlMode = false;

							ignoreLine = x == width ? true : false;
						}
					}
				}
			}
			//printf("nexoffs\n");
			//f.seekg(offsetlist[i], f.beg);

			m_BSH->AddGfx(width, height, pxArray);
			//if (i == 0) BSHDebug::ShowBSHIdx(m_BSH, 0);
			//printf("m_BSH->AddGfx()\n");
			//m_images.push_back(img);
			//img.GetCImg().display("img8 test");
		}
	}
}
