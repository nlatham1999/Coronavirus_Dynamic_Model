//Population.h
//Nick Latham 2/26/2020
//

#pragma once
#include "person.h"
#include <vector>

using namespace std;

class Population
{
private:
	vector<Person> pop; //list of people
	vector<Person> inCirculation; // {x in pop | x ! sick && x ! recovered} 
	//vector<Person> sick;
	int sick;
	int dead;
	int recovered;
	vector<vector<int>>groups;
public:
	Population(int populationNumber, int kid, int adult, int middle);

	void organizeIntoFamilies();

	void printPop();

	int getInfected();

	int getRandom(int low, int high);

	void infect(int chance);
};

