#include <iostream>
#include <fstream>
#include "header.h"

int main()
{
	char fileName[MAX_FILE_NAME_LENG] = "file.bin";
	PlantsBook book1{ fileName };
	char* tempPlantName = new char[1000];
	strcpy_s(tempPlantName, 1000, "carrot");
	char tempSunPref[MAX_SUN_PREF_LENG] = "sunny";
	//book1.addPlant(tempPlantName, tempSunPref, 1);
	//book1.bookWrite();
	book1.addPlant(tempPlantName, tempSunPref, 2);
	strcpy_s(tempPlantName, 1000, "potatoe");
	strcpy_s(tempSunPref, MAX_SUN_PREF_LENG, "neutral");
	book1.addPlant(tempPlantName, tempSunPref, 5);
	book1.printBook();
	delete[] tempPlantName;

	return 0;
}