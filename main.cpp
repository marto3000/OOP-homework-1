#include <iostream>
#include <fstream>
#include "header.h"

int main()
{
	char fileName[MAX_FILE_NAME_LENG] = "file.bin";
	PlantsBook book1{ fileName };
	//char* tempPlantName = new char[1000];
	//strcpy_s(tempPlantName, 1000, "aloe");
	//char tempSunPref[MAX_SUN_PREF_LENG] = "shadowy";
	//book1.addNewPlant(tempPlantName, tempSunPref, 6);
	//delete[] tempPlantName;
	book1.printBook();

	return 0;
}