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
	int sick;
	int dead;
	int recovered;
public:
	Population(int populationNumber, int kid, int adult, int middle);

	void printPop();
};

