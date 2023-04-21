#ifndef HEADER
#define HEADER

const int MAX_SUN_PREF_LENG = 8;
const int MAX_FILE_NAME_LENG = 128 + 1;

class Plant
{
	char* name;
	char sunPrefference[MAX_SUN_PREF_LENG];
	int watering;
public:
	Plant(char* newName, char newSunPrefference[MAX_SUN_PREF_LENG], int newWatering);
	Plant(Plant const& obj);
	Plant& operator=(Plant const& obj);
	~Plant();

	char* giveName();
	char* giveSunPref();
	int giveWatering();
};

class PlantsBook
{
	Plant** plants;
	char bookName[MAX_FILE_NAME_LENG];
	int count;
public:
	PlantsBook(char newBookName[MAX_FILE_NAME_LENG]);
	PlantsBook(PlantsBook const& obj);
	PlantsBook& operator=(PlantsBook const& obj);
	~PlantsBook();

	void bookRead();
	void bookWrite();
	//void addPlantFromUser();
	void addPlant(char* newName, char newSunPrefference[MAX_SUN_PREF_LENG], int newWatering);
	bool inputNewPlant(char* plant, char* newPlant);
	void printBook();
};

class PotRow
{
	const int POTS_COUNT;
	Plant** plants;
public:
	PotRow(int newPotsCount);
	PotRow(PotRow const& obj);
	PotRow& operator=(PotRow const& obj);
	~PotRow();

	void fillPot(int pos, Plant plant);//future implementation
	void emptyPot(int pos);//future implementation
};

class Greenhouse
{
	PlantsBook GHBook;
	PotRow sunnyRow;
	PotRow neutralRow;
	PotRow shadowyRow;
public:
	Greenhouse(PlantsBook newBook, int sunnRowCap, int neutralRowCap, int shadowyRowCap);
	Greenhouse(Greenhouse const& obj);
};

#endif // !HEADER