#pragma once

class BSH;

class BSHFile
{
public:
	BSHFile(const char* bshFileName, BSH* bshObj);

	inline BSH* GetBSH() const { return m_BSH; }

private:
	BSH* m_BSH = nullptr;

	void readBSH(const char* fileName);

	// Reads Images from BSH file:
	void readImagesPixelArray(); // Store images in traditional Pixelarray (RGBA/pixel)
	void readImagesPixelLines(); // Store only visible pixel of images in lines (RGBA/pixel)

};

