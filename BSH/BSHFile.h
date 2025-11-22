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
	void readBSHOld(const char* fileName); // Slow method, remove

};

