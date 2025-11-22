#include "BSHFile.h"
#include <fstream>      // std::filebuf
#include <stdlib.h>
#include <chrono>

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
	double duration_t = 0;
	auto start_t = std::chrono::high_resolution_clock::now();

	if (!m_BSH->GetPalettePixelArray()) // Palette not set!
	{
		printf("Error BSHFile::readBSH(): Palette is not set!\n");
		return;
	}

	// Get pallete, for later translation
	SPixel* pltpx = m_BSH->GetPalettePixelArray();

	char* rawBsh; // Holds all BSH data. BSH files are usually not big.
	char* rawBshHeader; // Holds the BSH header.
	int pos = 0; // Position in rawBsh

	f.open(fileName, std::ios::binary); // Open BSH file in binary
	if (f.is_open()) // Check if open was successfully
	{
		// Get filesize:
		std::streampos fsize = 0;
		fsize = f.tellg();
		f.seekg(0, std::ios::end);
		fsize = f.tellg() - fsize;

		f.seekg(0, f.beg); // Set file pos back to start
		
		// Allocate memory to load full bsh-file into memory (data + header)
		rawBsh = (char*)malloc(sizeof(char) * ((int)fsize - BSH_HEADER_LENGTH + 1));
		rawBshHeader = (char*)malloc(sizeof(char) * BSH_HEADER_LENGTH);

		double duration0 = 0;
		auto start0 = std::chrono::high_resolution_clock::now();
		//f.seekg(20, f.beg); // skip 20 bytes (BSH header) //ToDo: Add check for valid BSH header
		f.read(rawBshHeader, (int)BSH_HEADER_LENGTH);
		//pos += BSH_HEADER_LENGTH; // skip 20 bytes (BSH header) //ToDo: Add check for valid BSH header

		f.read(rawBsh, ((int)fsize - BSH_HEADER_LENGTH) * sizeof(std::streampos) + 1);

		// List of offsets to all images
		std::vector<int> offsetlist;

		// Load offsets of all images
		// - Get first offset
		//ToDo:Make the code more compact
		int firstoffset; // Get first offset
		memcpy(&firstoffset, rawBsh + pos, sizeof(int));
		pos += sizeof(int);
		//f.read(reinterpret_cast<char*>(&firstoffset), sizeof(firstoffset));
		//firstoffset += BSH_HEADER_LENGTH;

		offsetlist.push_back(firstoffset);

		// - Get all other image offsets
		//for (int offset; (int)f.tellg() + sizeof(offset) <= firstoffset;)
		for (int offset; pos + sizeof(offset) <= firstoffset;)
		{
			//f.read(reinterpret_cast<char*>(&offset), sizeof(offset));
			memcpy(&offset, rawBsh + pos, sizeof(offset));
			//offset += BSH_HEADER_LENGTH;
			pos += sizeof(offset);

			offsetlist.push_back(offset);
		}
		auto end0 = std::chrono::high_resolution_clock::now();
		duration0 = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end0 - start0).count() / 1000;
		printf(" - Read BSH offsets: %.2lfs.\n", duration0);

		double duration1 = 0;
		auto start1 = std::chrono::high_resolution_clock::now();
		auto end1 = start1;
		double duration2 = 0;
		auto start2 = std::chrono::high_resolution_clock::now();
		auto end2 = start2;
		double duration3 = 0;
		auto start3 = std::chrono::high_resolution_clock::now();
		auto end3 = start3;
		double duration4 = 0;
		auto start4 = std::chrono::high_resolution_clock::now();
		auto end4 = start4;

		//for (int i = 0; i < offsetlist.size(); i++)
		//{
		//	printf(" 0x%04X\n", offsetlist[i] + BSH_HEADER_LENGTH);
		//}

		m_BSH->AllocateMemorySize(offsetlist.size());

		const SPixel& alphaPixel = m_BSH->GetAlphaPixel();

		// Read images:
		for (int i = 0; i < offsetlist.size(); i++)
		{
			start1 = std::chrono::high_resolution_clock::now();
			pos = offsetlist[i];
			//f.seekg(offsetlist[i], f.beg);
			int x = 0;
			int y = 0;

			//printf(" 0x%04X\n", offsetlist[i] + BSH_HEADER_LENGTH);
			// Read width and height
			//uint16_t tmp;
			int width;
			int height;
			//f.read(reinterpret_cast<char*>(&width), sizeof(width));
			//f.read(reinterpret_cast<char*>(&height), sizeof(height));
			memcpy(&width, rawBsh + pos, sizeof(width));
			//tmp = *(rawBsh + pos);
			//width = (int)tmp;
			pos += sizeof(int);
			memcpy(&height, rawBsh + pos, sizeof(height));
			//tmp = *(rawBsh + pos);
			//height = (int)tmp;
			pos += sizeof(int);
			//printf(" 0x%04X\n", offsetlist[i] + BSH_HEADER_LENGTH);
			//printf(" Img 0x%04X (%d,%i)\n", offsetlist[i] + BSH_HEADER_LENGTH, width, height);
			//printf("Img (%d,%d)\n", width, height);

			// Check if the image has a valid size
			if (width <= 0 || height <= 0)
			{
				printf("Invalid image size!\n");
				printf(" 0x%04X\n", offsetlist[i] + BSH_HEADER_LENGTH);
				return;
			}

			end1 = std::chrono::high_resolution_clock::now();
			duration1 += (double)std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count() / 1000;

			start2 = std::chrono::high_resolution_clock::now();
			SPixel* pxArray = (SPixel*)malloc(width * height * sizeof(SPixel)); // allocate for known image with width & height
			end2 = std::chrono::high_resolution_clock::now();
			duration2 += (double)std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count() / 1000;

			start3 = std::chrono::high_resolution_clock::now();
			// Skip 8 unknown bytes
			//f.ignore(8);
			pos += 8;

			// Read until we reach the end marker
			while (true)
			{
				//char b;
				//f.read(&b, 1);
				//memcpy(&b, rawBsh + pos, sizeof(char));
				//uint8_t numAlpha = b; // transparent pixel count before actual pixel
				uint8_t numAlpha = *(rawBsh + pos); // transparent pixel count before actual pixel
				pos += sizeof(char);

				// End marker
				if (numAlpha == 255)
				{
					if (x < width)
					{
						// Add remaining alpha pixels in current y row
						for (; x < width; ++x)
						{
							int idx = width * y + x;
							pxArray[idx] = alphaPixel;
						}

					}
					++y; // Increment y by one to prevent overwriting previous row.
					if (y < height)
					{
						// Add remaining alpha pixels in current y row
						for (; y < height; ++y)
						{
							for (x = 0; x < width; ++x)
							{
								int idx = width * y + x;
								//printf("%d\n", y);
								pxArray[idx] = alphaPixel;
							}
						}

					}

					break;
				}

				// End of row
				if (numAlpha == 254)
				{
					if (x < width)
					{
						// Add remaining alpha pixels in current y row
						for (; x < width; ++x)
						{
							int idx = width * y + x;
							pxArray[idx] = alphaPixel;
						}

					}

					x = 0;
					++y;
					continue;
				}

				// Pixel data
				for (int i = 0; i < numAlpha; ++i)
				{
					int idx = width * y + x;
					pxArray[idx] = alphaPixel;
					++x;
				}

				// Get color pixel:
				//f.read(&b, 1);
				//memcpy(&b, rawBsh + pos, sizeof(char));
				//uint8_t numPixels = b;
				uint8_t numPixels = *(rawBsh + pos);
				pos += sizeof(char);

				for (int i = 0; i < numPixels; ++i)
				{
					//f.read(&b, 1);
					//memcpy(&b, rawBsh + pos, sizeof(char));
					//uint8_t clrIdx = b; // color index of current pixel in palette
					uint8_t clrIdx = *(rawBsh + pos); // color index of current pixel in palette
					pos += sizeof(char);

					int idx = width * y + x;
					pxArray[idx] = pltpx[clrIdx];

					++x;
				}
			}

			//f.seekg(offsetlist[i], f.beg);
			end3 = std::chrono::high_resolution_clock::now();
			duration3 += (double)std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3).count() / 1000;

			start4 = std::chrono::high_resolution_clock::now();
			m_BSH->AddGfx(width, height, pxArray);
			end4 = std::chrono::high_resolution_clock::now();
			duration4 += (double)std::chrono::duration_cast<std::chrono::milliseconds>(end4 - start4).count() / 1000;
		}

		free(rawBsh);
		free(rawBshHeader);

		auto end_t = std::chrono::high_resolution_clock::now();
		duration_t = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count() / 1000;
		printf("Read BSH images in %.2lfs. fread{h:%.2lfs, b:%.2lfs}, struct:{alloc:%.2lfs, fill:%.2lfs}.\n", (duration_t), duration1, duration3, duration2, duration4);
	}
}
