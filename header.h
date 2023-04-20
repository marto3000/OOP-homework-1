#ifndef HEADER
#define HEADER

const int MAX_SUN_PREF_LENG = 8;

class Plant
{
	char* name;
	char sunPrefference[MAX_SUN_PREF_LENG];
	int watering;
	//int count;
public:
	Plant(char* newName, char newSunPrefference[MAX_SUN_PREF_LENG], int newWatering);
	Plant(Plant const& obj);
	Plant& operator= (Plant const& obj);
	~Plant();
};

#endif // !HEADER