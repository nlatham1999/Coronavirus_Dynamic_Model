//Person.h
//Nick Latham 3/26/2020

#include <string>

using namespace std;

class Person
{
private:
	string age; // kid (0-18) adult (19-44) middle (45-64) old (65-) 
	string gender;
	int daysSick;
	bool sick;
	bool recovered;
	bool recievingMedicalCare;
	int groupId;
	int id;

public:

	Person();

	Person(string a, string g, int i);

	string getAge();
	
	string getGender();

	void setGroupId(int i);

	int getGroupId();

	int getId();

	void setSick(bool s);

	bool isSick();



};
