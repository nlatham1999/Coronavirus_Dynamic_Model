#include "Population.h"
#include <iostream>

Population::Population(int populationNumber, int kid, int adult, int middle) {
	for (int i = 0; i < populationNumber; i++) {
		string gender = "male";
		string age = "old";
		//half the people will be female half will be male
		if (i % 2 == 0) {
			gender = "female";
		}
		//seperates the ages according to the demographics provided
		if (i * 100 / populationNumber < kid) {
			age = "kid";
		}
		else if (i * 100 / populationNumber < kid+adult) {
			age = "adult";
		}
		else if (i * 100 / populationNumber < kid+adult+middle) {
			age = "middle";
		}
		Person tempPerson(age, gender);
		pop.push_back(tempPerson);
	}
}

void Population::printPop() {
	for (int i = 0; i < pop.size(); i++) {
		cout << "age: " << pop[i].getAge() << "\tgender: " << pop[i].getGender() << endl;
	}
}
