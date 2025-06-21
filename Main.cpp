#include "BSH/Palette.h"
#include "BSH/BSH.h"
#include "BSH/BSHDebug.h"

int main()
{

	Palette* palette = new Palette(PALETTE_FILE);
	//palette->printPalette();

	BSH* bauship6 = new BSH("bsh_files/Bauship6.bsh", palette);

	BSHDebug::ShowBSHIdx(bauship6, 0);

	//BSH* numbers = new BSH("bsh_files/NUMBERS.bsh", palette);
	//BSH* symbol = new BSH("bsh_files/SYMBOL.bsh", palette);
	//BSH* effekte = new BSH("bsh_files/EFFEKTE.bsh", palette);
	//BSH* gaukler = new BSH("bsh_files/GAUKLER.bsh", palette);
	//BSH* schatten = new BSH("bsh_files/SCHATTEN.bsh", palette);
	//BSH* soldat = new BSH("bsh_files/SOLDAT.bsh", palette);
	BSH* stadtfld = new BSH("bsh_files/STADTFLD.bsh", palette);
	//BSH* traeger = new BSH("bsh_files/TRAEGER.bsh", palette);

	for (int i = 0; i < stadtfld->GetGfxArraySize(); i++)
		BSHDebug::ShowBSHIdx(stadtfld, i);

	return 0;
}