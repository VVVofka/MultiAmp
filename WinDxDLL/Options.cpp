#include "pch.h"
#ifdef MODEA

#include "Options.h"

Options::Options(){
	bool isload = loadAuto();
	if(!isload)
		setDefault();
} // //////////////////////////////////////////////////////////////////////////////////
bool Options::saveAuto() const{
	bool ret = save(autoDirsFName);
	return ret;
} // ///////////////////////////////////////////////////////////////////////////
bool Options::loadAuto(){
	bool ret = load(autoDirsFName);
	if(ret)
		loadAll();
	return ret;
} // ///////////////////////////////////////////////////////////////////////////
int Options::showDlg(){
	//-int ret = openDlgOptions(iArr, dArr);
	//if(ret != 0){
	//	save(autoDirsFName);
	//	loadAll();
	//}
	//-return ret;
	return 0;
} // ///////////////////////////////////////////////////////////////////////////
bool Options::setDefault(){
	blocks2D2.setDefault();
	blocks2D2.toDirs(dirs());
	iArr[InpOptions::NormDir] = 1;
	iArr[InpOptions::LaysSzUpY] = 1;
	iArr[InpOptions::LaysSzUpX] = 1;
	iArr[InpOptions::LaysSzDn] = 1024;
	iArr[InpOptions::SeedRnd] = -1;
	iArr[InpOptions::LaysCnt] = 10;
	iArr[InpOptions::Restart] = 0;
	for(int j = 0; j < _countof(AMask); j++)
		iArr[InpOptions::AMasks + j] = AMask[j];

	dArr[InpOptions::kFillRnd] = 0.035;
	dArr[InpOptions::kSigmaY] = 0.45;
	dArr[InpOptions::kSigmaX] = 0.45;
	dArr[InpOptions::kInertion] = 0.0;
	dArr[InpOptions::kBorder] = 0.0;
	for(int j = 0; j < InpOptions::LaysCntReserv; j++)
		dArr[InpOptions::kLays + j] = 1.0;

	bool ret = save(autoDirsFName);
	return ret;
} // ///////////////////////////////////////////////////////////////////////////
bool Options::save(const char* fname) const{
	FILE* f;
	errno_t err = fopen_s(&f, fname, "wb");
	if(err == 0 && f != 0){
		int sziwrite = (int)fwrite(iArr, sizeof(iArr[0]), sziArr, f);
		if(sziwrite != sziArr){
			fclose(f);
			MessageBoxA(NULL, fname, "Error#1 write i file!", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}
		int checki = 10;
		for(int j = 0; j < sziArr; j++)
			checki += iArr[j];
		sziwrite = (int)fwrite(&checki, sizeof(checki), 1, f);

		int szdwrite = (int)fwrite(dArr, sizeof(dArr[0]), szdArr, f);
		if(szdwrite != szdArr){
			fclose(f);
			MessageBoxA(NULL, fname, "Error#1 write d file!", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}
		double checkd = 10.0;
		for(int j = 0; j < szdArr; j++)
			checkd += dArr[j];
		szdwrite = (int)fwrite(&checkd, sizeof(checkd), 1, f);
		fclose(f);
		if(szdwrite == 1 && sziwrite == 1)
			return true;
	}
	MessageBoxA(NULL, fname, "Error#2 write file!", MB_ICONEXCLAMATION | MB_OK);
	return false;
} // ///////////////////////////////////////////////////////////////////////////
bool Options::load(const char* fname){
	FILE* f;
	errno_t err = fopen_s(&f, fname, "rb");
	if(err == 0 && f != 0){
		int sziread = (int)fread(iArr, sizeof(iArr[0]), sziArr, f);
		if(sziread != sziArr){
			fclose(f);
			MessageBoxA(NULL, fname, "Error#1 read i file!", MB_ICONEXCLAMATION | MB_OK);
			remove(fname);
			return false;
		}
		int checki = 10;
		for(int j = 0; j < sziArr; j++)
			checki += iArr[j];
		int checkiread = -1;
		sziread = (int)fread(&checkiread, sizeof(checkiread), 1, f);

		int szdread = (int)fread(dArr, sizeof(dArr[0]), szdArr, f);
		if(szdread != szdArr){
			fclose(f);
			MessageBoxA(NULL, fname, "Error#1 read d file!", MB_ICONEXCLAMATION | MB_OK);
			remove(fname);
			return false;
		}
		double checkd = 10.0;
		for(int j = 0; j < szdArr; j++)
			checkd += dArr[j];
		double checkdread = -1.0;
		szdread = (int)fread(&checkdread, sizeof(checkdread), 1, f);

		fclose(f);
		if(sziread == 1 && szdread == 1 && checkiread == checki && checkdread == checkd)
			return true;
		else
			remove(fname);
	}
	MessageBoxA(NULL, fname, "Error#2 read file!", MB_ICONEXCLAMATION | MB_OK);
	return false;
} // ///////////////////////////////////////////////////////////////////////////
void Options::loadAll(){
	blocks2D2.fromDirs(dirs());// TODO: add other parametrs
} // ///////////////////////////////////////////////////////////////////////////
#endif  // MODEA

