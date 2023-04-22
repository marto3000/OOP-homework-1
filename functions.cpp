#include <iostream>
#include <fstream>
#include "header.h"

//PLANT

Plant::Plant(const char* newName, const char newSunPrefference[MAX_SUN_PREF_LENG], int newWatering)
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

PlantsBook::PlantsBook(const char newBookName[MAX_FILE_NAME_LENG])
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
		delete plants[i];
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
		if (!strcmp(plants[i]->giveName(), newName))
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
			if (!newPlantAdded && i == count - 1)
			{
				plants[i] = newPlant;
				break;
			}
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

void PlantsBook::addNewPlant(char* newName, char newSunPrefference[MAX_SUN_PREF_LENG], int newWatering)
{
	addPlant(newName, newSunPrefference, newWatering);
	bookWrite();
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

Plant PlantsBook::givePlant(int pos)
{
	return *plants[pos];
}

char* PlantsBook::givePlantName(int pos)
{
	return plants[pos]->giveName();
}

int PlantsBook::giveCount()
{
	return count;
}

//void PlantsBook::plantDelete(int pos)
//{
//	delete plants[pos];
//	for (int i = pos - 1; i < count - 1; i++)
//	{
//		plants[i] = plants[i + 1];
//	}
//	plants[count - 1] = nullptr;
//	count--;
//}

//POT_ROW

PotRow::PotRow(int newPotsCount) : POTS_COUNT(newPotsCount)
{
	plants = new Plant * [POTS_COUNT];
	for (int i = 0; i < POTS_COUNT; i++)
	{
		plants[i] = nullptr;
	}
}

PotRow::PotRow(PotRow const& obj) : POTS_COUNT(obj.POTS_COUNT)
{
	plants = new Plant * [POTS_COUNT];
	for (int i = 0; i < POTS_COUNT; i++)
	{
		plants[i] = nullptr;
	}
}

PotRow& PotRow::operator=(PotRow const& obj)
{
	if (POTS_COUNT != obj.POTS_COUNT)
	{
		throw std::exception("different row lengths");
	}
	for (int i = 0; i < POTS_COUNT; i++)
	{
		if (!plants[i])
		{
			plants[i] = obj.plants[i];
		}
	}
	return *this;
}

PotRow::~PotRow()
{
	for (int i = 0; i < POTS_COUNT; i++)
	{
		if (!plants[i])
		{
			delete[] plants[i];
			plants[i] = nullptr;
		}
	}
	delete[] plants;
	plants = nullptr;
}

void PotRow::add(int pos, Plant addPlant)
{
	Plant* newPlant = new Plant(addPlant);
	plants[pos] = newPlant;
	newPlant = nullptr;
}

void PotRow::remove(int pos)
{
	if (plants[pos] != nullptr)
	{
		delete plants[pos];
		plants[pos] = nullptr;
	}
	else
	{
		std::cout << "the pot is already empty" << std::endl;
	}
}

int PotRow::findEmptyPot()
{
	for (int i = 0; i < POTS_COUNT; i++)
	{
		if (plants[i] == nullptr)
		{
			return i;
		}
	}
	return -1;
}

void PotRow::printRow()
{
	std::cout << POTS_COUNT << std::endl << std::endl;
	for (int i = 0; i < POTS_COUNT; i++)
	{
		if (plants[i] == nullptr)
		{
			std::cout << "no plant" << std::endl;
			std::cout << "x" << std::endl;
			std::cout << "x" << std::endl;
			std::cout << std::endl;
		}
		else
		{
			std::cout << plants[i]->giveName() << std::endl;
			std::cout << plants[i]->giveSunPref() << std::endl;
			std::cout << plants[i]->giveWatering() << std::endl;
			std::cout << std::endl;
		}
	}
}

//GREENHOUSE

Greenhouse::Greenhouse(PlantsBook newBook, int sunnRowCap, int neutralRowCap, int shadowyRowCap) : GHBook(newBook), sunnyRow(sunnRowCap), neutralRow(neutralRowCap), shadowyRow(shadowyRowCap)
{

}

Greenhouse::Greenhouse(Greenhouse const& obj) : GHBook(obj.GHBook), sunnyRow(obj.sunnyRow), neutralRow(obj.neutralRow), shadowyRow(obj.shadowyRow)
{

}

void Greenhouse::fillPot(const char* plantName)
{
	bool plantCheck = false;
	int plantPos;
	for (int i = 0; i < GHBook.giveCount(); i++)
	{
		if (!strcmp(plantName, GHBook.givePlantName(i)))
		{
			plantCheck = true;
			plantPos = i;
			break;
		}
	}
	if (!plantCheck)
	{
		std::cout << "The plant was not found in the book";
		throw std::exception("The plant was not found in the book");
	}
	Plant addPlant(GHBook.givePlant(plantPos));
	char plantSunPref[MAX_SUN_PREF_LENG];
	strcpy_s(plantSunPref, MAX_SUN_PREF_LENG, addPlant.giveSunPref());
	if (sunnyRow.findEmptyPot() == -1 && neutralRow.findEmptyPot() == -1 && shadowyRow.findEmptyPot() == -1)
	{
		throw std::exception("no empty space");
	}
	int emptyPos;
	if (!strcmp(plantSunPref, "sunny"))
	{
		emptyPos = sunnyRow.findEmptyPot();
		if (emptyPos == -1)
		{
			emptyPos = neutralRow.findEmptyPot();
			if (emptyPos == -1)
			{
				emptyPos = shadowyRow.findEmptyPot();
				int changedWatering = addPlant.giveWatering() + 2;
				Plant changedPlant(addPlant.giveName(), addPlant.giveSunPref(), changedWatering);
				shadowyRow.add(emptyPos, changedPlant);
			}
			else
			{
				int changedWatering = addPlant.giveWatering() + 1;
				Plant changedPlant(addPlant.giveName(), addPlant.giveSunPref(), changedWatering);
				neutralRow.add(emptyPos, changedPlant);
			}
		}
		else
		{
			sunnyRow.add(emptyPos, addPlant);
		}
	}
	else if (!strcmp(plantSunPref, "neutral"))
	{
		emptyPos = neutralRow.findEmptyPot();
		if (emptyPos == -1)
		{
			emptyPos = sunnyRow.findEmptyPot();
			if (emptyPos == -1)
			{
				emptyPos = shadowyRow.findEmptyPot();
				int changedWatering = addPlant.giveWatering() + 1;
				Plant changedPlant(addPlant.giveName(), addPlant.giveSunPref(), changedWatering);
				shadowyRow.add(emptyPos, changedPlant);
			}
			else
			{
				int changedWatering = addPlant.giveWatering() - 1;
				if (changedWatering < 1)
				{
					changedWatering = 1;
				}
				Plant changedPlant(addPlant.giveName(), addPlant.giveSunPref(), changedWatering);
				sunnyRow.add(emptyPos, changedPlant);
			}
		}
		else
		{
			neutralRow.add(emptyPos, addPlant);
		}
	}
	else if (!strcmp(plantSunPref, "shadowy"))
	{
		emptyPos = shadowyRow.findEmptyPot();
		if (emptyPos == -1)
		{
			emptyPos = neutralRow.findEmptyPot();
			if (emptyPos == -1)
			{
				emptyPos = sunnyRow.findEmptyPot();
				int changedWatering = addPlant.giveWatering() - 2;
				if (changedWatering < 1)
				{
					changedWatering = 1;
				}
				Plant changedPlant(addPlant.giveName(), addPlant.giveSunPref(), changedWatering);
				sunnyRow.add(emptyPos, changedPlant);
			}
			else
			{
				int changedWatering = addPlant.giveWatering() - 1;
				if (changedWatering < 1)
				{
					changedWatering = 1;
				}
				Plant changedPlant(addPlant.giveName(), addPlant.giveSunPref(), changedWatering);
				neutralRow.add(emptyPos, changedPlant);
			}
		}
		else
		{
			shadowyRow.add(emptyPos, addPlant);
		}
	}
}

void Greenhouse::emptyPot(const char* potRow, int pos)
{
	if (!strcmp(potRow, "sunny"))
	{
		sunnyRow.remove(pos);
	}
	else if (!strcmp(potRow, "neutral"))
	{
		neutralRow.remove(pos);
	}
	else
	{
		shadowyRow.remove(pos);
	}
}

void Greenhouse::printGH()
{
	std::cout << "sunny row --------------------" << std::endl << std::endl;
	sunnyRow.printRow();
	std::cout << "neutral row ------------------" << std::endl << std::endl;
	neutralRow.printRow();
	std::cout << "shadowy row ------------------" << std::endl << std::endl;
	shadowyRow.printRow();
}