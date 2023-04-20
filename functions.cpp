#include <iostream>
#include "header.h"

//PLANT

Plant::Plant(char* newName, char newSunPrefference[MAX_SUN_PREF_LENG], int newWatering)
{
	int nameLeng = strlen(newName) + 1;
	name = new char[nameLeng];
	strcpy_s(name, nameLeng, newName);
	strcpy_s(sunPrefference, MAX_SUN_PREF_LENG, newSunPrefference);
	watering = newWatering;
}

Plant::Plant(Plant const& obj)
{
	int nameLeng = strlen(obj.name) + 1;
	name = new char[nameLeng];
	strcpy_s(name, nameLeng, obj.name);
	strcpy_s(sunPrefference, MAX_SUN_PREF_LENG, obj.sunPrefference);
	watering = obj.watering;
}

Plant& Plant::operator= (Plant const& obj)
{
	int nameLeng = strlen(obj.name) + 1;
	delete[] name;
	name = new char[nameLeng];
	strcpy_s(name, nameLeng, obj.name);
	strcpy_s(sunPrefference, MAX_SUN_PREF_LENG, obj.sunPrefference);
	watering = obj.watering;

	return *this;
}

Plant::~Plant()
{
	delete[] name;
	name = nullptr;
}