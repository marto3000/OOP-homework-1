#include <iostream>
#include <fstream>
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
	std::cout << "deleted plant";
}

char* Plant::giveName()
{
	return name;
}

char* Plant::giveSunPref()
{
	return sunPrefference;
}

int Plant::giveWatering()
{
	return watering;
}

//PLANTS_BOOK

PlantsBook::PlantsBook(char newBookName[MAX_FILE_NAME_LENG])
{
	strcpy_s(bookName, MAX_FILE_NAME_LENG, newBookName);
	count = 0;
	plants = new Plant * [count];
	bookRead();
}

PlantsBook::PlantsBook(PlantsBook const& obj)
{
	strcpy_s(bookName, MAX_FILE_NAME_LENG, obj.bookName);
	count = 0;
	plants = new Plant * [count];
	bookRead();
}

PlantsBook& PlantsBook::operator=(PlantsBook const& obj)
{
	for (int i = 0; i < count; i++)
	{
		delete[] plants[i];
		plants[i] = nullptr;
	}
	delete[] plants;
	strcpy_s(bookName, MAX_FILE_NAME_LENG, obj.bookName);
	count = 0;
	plants = new Plant * [count];
	bookRead();

	return *this;
}

PlantsBook::~PlantsBook()
{
	for (int i = 0; i < count; i++)
	{
		delete[] plants[i];
		plants[i] = nullptr;
	}
	delete[] plants;
	plants = nullptr;
}

void PlantsBook::bookRead()
{
	std::ifstream bookFile(bookName, std::ios::binary);
	if (!bookFile)
	{
		std::cout << "File not found";
		return;
	}
	if (!bookFile.eof())
	{
		int plantsCount = 0;
		bookFile.read((char*)&plantsCount, sizeof(int));
		bookFile.ignore();
		for (int i = 0; i < plantsCount; i++)
		{
			int nameLeng = 0;
			bookFile.read((char*)&nameLeng, sizeof(int));
			bookFile.ignore();
			char* newName = new char[nameLeng];
			bookFile.read(newName, nameLeng);
			bookFile.ignore();
			char newSunPref[MAX_SUN_PREF_LENG];
			bookFile.read(newSunPref, MAX_SUN_PREF_LENG);
			bookFile.ignore();
			int newWatering = 0;
			bookFile.read((char*)&newWatering, sizeof(int));
			bookFile.ignore();
			addPlant(newName, newSunPref, newWatering);
			delete[] newName;
			newName = nullptr;
		}
	}
	else
	{
		std::cout << "The file is empty.";
	}
	bookFile.close();
}

void PlantsBook::bookWrite()
{
	std::ofstream bookFile(bookName, std::ios::binary, std::ios::trunc);
	char newLn = '\n';
	char space = ' ';
	bookFile.write((const char*)&count, sizeof(int));
	bookFile.write((const char*)&newLn, sizeof('\n'));
	for (int i = 0; i < count; i++)
	{
		int writeNameLeng = strlen(plants[i]->giveName()) + 1;
		bookFile.write((const char*)&writeNameLeng, sizeof(int));
		bookFile.write((const char*)&space, sizeof(' '));
		char* writeName = new char[writeNameLeng];
		strcpy_s(writeName, writeNameLeng, plants[i]->giveName());
		bookFile.write(writeName, writeNameLeng);
		bookFile.write((const char*)&space, sizeof(' '));
		delete[] writeName;
		writeName = nullptr;
		char writeSunPref[MAX_SUN_PREF_LENG];
		strcpy_s(writeSunPref, MAX_SUN_PREF_LENG, plants[i]->giveSunPref());
		bookFile.write(writeSunPref, MAX_SUN_PREF_LENG);
		bookFile.write((const char*)&space, sizeof(' '));
		int writeWatering = plants[i]->giveWatering();
		bookFile.write((const char*)&writeWatering, sizeof(int));
		bookFile.write((const char*)&newLn, sizeof('\n'));
	}
	bookFile.close();
}

void PlantsBook::addPlant(char* newName, char newSunPrefference[MAX_SUN_PREF_LENG], int newWatering)
{
	for (int i = 0; i < count; i++)
	{
		if (plants[i]->giveName() == newName)
		{
			throw std::exception("the plant already exists");
		}
	}
	Plant* newPlant = new Plant (newName, newSunPrefference, newWatering);
	Plant** tempPlants = plants;
	count++;
	plants = new Plant * [count];
	if (count == 1)
	{
		plants[count - 1] = newPlant;
	}
	else
	{
		bool newPlantAdded = false;
		for (int i = 0; i < count; i++)
		{
			if (newPlantAdded)
			{
				plants[i] = tempPlants[i - 1];
			}
			else
			{
				if (inputNewPlant(tempPlants[i]->giveName(), newPlant->giveName()))
				{
					plants[i] = newPlant;
					newPlantAdded = true;
				}
				else
				{
					plants[i] = tempPlants[i];
				}
			}
		}
	}
	tempPlants = nullptr;
}

bool PlantsBook::inputNewPlant(char* plant, char* newPlant)
{
	if (strcmp(plant, newPlant) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PlantsBook::printBook()
{
	std::cout << bookName << std::endl;
	std::cout << count << std::endl;
	for (int i = 0; i < count; i++)
	{
		std::cout << std::endl;
		std::cout << plants[i]->giveName() << std::endl;
		std::cout << plants[i]->giveSunPref() << std::endl;
		std::cout << plants[i]->giveWatering() << std::endl;
	}
}