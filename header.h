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
	Plant(const char* newName, const char newSunPrefference[MAX_SUN_PREF_LENG], int newWatering);
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
	PlantsBook(const char newBookName[MAX_FILE_NAME_LENG]);
	PlantsBook(PlantsBook const& obj);
	PlantsBook& operator=(PlantsBook const& obj);
	~PlantsBook();

	void bookRead();
	void bookWrite();
	void addPlant(char* newName, char newSunPrefference[MAX_SUN_PREF_LENG], int newWatering);
	void addNewPlant(char* newName, char newSunPrefference[MAX_SUN_PREF_LENG], int newWatering);
	bool inputNewPlant(char* plant, char* newPlant);
	void printBook();
	Plant givePlant(int pos);
	char* givePlantName(int pos);
	int giveCount();

	//void plantDelete(int pos);//temp function
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

	void add(int pos, Plant addPlant);
	void remove(int pos);
	int findEmptyPot();
	void printRow();
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

	void fillPot(const char* plantName);
	void emptyPot(const char* potRow, int pos);
	void printGH();
};

#endif // !HEADER