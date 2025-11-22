#include "BSH/Palette.h"
#include "BSH/BSH.h"
#include "BSH/BSHDebug.h"

int main()
{
	Palette palette = Palette(PALETTE_FILE);
	//palette->printPalette();

	//BSH bsh("bsh_files/NUMBERS.BSH", palette);
	///BSH bsh("bsh_files/Bauship6.bsh", palette);
	//BSH bsh("bsh_files/SYMBOL.BSH", palette);
	//BSH bsh("bsh_files/EFFEKTE.BSH", palette);
	//BSH bsh("bsh_files/GAUKLER.BSH", palette);
	//BSH bsh("bsh_files/SCHATTEN.BSH", palette);
	//BSH bsh("bsh_files/SOLDAT.BSH", palette);
	//BSH bsh("bsh_files/STADTFLD.BSH", palette);
	//BSH bsh("bsh_files/TIERE.BSH", palette);
	//BSH bsh("bsh_files/TRAEGER.BSH", palette);

	//BSH* bauship6 = new BSH("bsh_files/Bauship6.bsh", palette);
	//BSHDebug::displayAllImages(bauship6);
	//BSH* numbers = new BSH("bsh_files/NUMBERS.bsh", palette);
	//BSH* symbol = new BSH("bsh_files/SYMBOL.bsh", palette);
	//BSH* effekte = new BSH("bsh_files/EFFEKTE.bsh", palette);
	//BSH* gaukler = new BSH("bsh_files/GAUKLER.bsh", palette);
	//BSH* schatten = new BSH("bsh_files/SCHATTEN.bsh", palette);
	//BSH* soldat = new BSH("bsh_files/SOLDAT.bsh", palette);
	BSH* stadtfld = new BSH("bsh_files/STADTFLD.bsh", palette);
	stadtfld = new BSH("bsh_files/STADTFLD.bsh", palette);
	stadtfld = new BSH("bsh_files/STADTFLD.bsh", palette);
	stadtfld = new BSH("bsh_files/STADTFLD.bsh", palette);
	stadtfld = new BSH("bsh_files/STADTFLD.bsh", palette);
	stadtfld = new BSH("bsh_files/STADTFLD.bsh", palette);
	stadtfld = new BSH("bsh_files/STADTFLD.bsh", palette);
	stadtfld = new BSH("bsh_files/STADTFLD.bsh", palette);
	stadtfld = new BSH("bsh_files/STADTFLD.bsh", palette);
	stadtfld = new BSH("bsh_files/STADTFLD.bsh", palette);
	//BSH* traeger = new BSH("bsh_files/TRAEGER.bsh", palette);

	//BSHDebug::displayAllImages(bauship6);
	//BSHDebug::displayAllImages(stadtfld);
	//BSHDebug::displayAllImages(gaukler);

	//BSHDebug::ShowBSHIdx(bauship6, 0);
	//BSHDebug::ShowBSHIdx(bauship6, 1);
	//BSHDebug::ShowBSHIdx(bauship6, 2);
	//BSHDebug::ShowBSHIdx(bauship6, 3);
	//BSHDebug::ShowBSHIdx(soldat, 21);

	return 0;
}