#include "Population.h"
#include <iostream>
#include <random>

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
		Person tempPerson(age, gender, i);
		pop.push_back(tempPerson);
	}

	int temp = pop.size() / 2;
	pop[temp].setSick(true);

	organizeIntoFamilies();
}

//families are groups of people that are living togethor
//different groups:
//	2 elderly
//	1 elderly
//	2 middle + chance 1 elderly + chance 2 kids
//	1 middle + chance 1 elderly + chance 2 kids
//	2 adult  + chance 2 kids
//	1 adult  + chance 2 kids

void Population::organizeIntoFamilies() {
	vector<Person> kids;
	vector<Person> adults;
	vector<Person> middles;
	vector<Person> elderly;
	vector<Person> sorted;

	//fill up the age vectors
	for (int i = 0; i < pop.size(); i++) {
		if (pop[i].getAge() == "kid")
			kids.push_back(pop[i]);
		else if (pop[i].getAge() == "adult")
			adults.push_back(pop[i]);
		else if (pop[i].getAge() == "middle")
			middles.push_back(pop[i]);
		else
			elderly.push_back(pop[i]);
	}
	int familyIdCount = 0;

	//pair up adults and middles
	for (int i = 0; i < adults.size(); i++) {
		adults[i].setGroupId(familyIdCount);
		if (getRandom(1, 100) < 30) {
			sorted.push_back(adults[i]);
		}else{
			if (i + 1 < adults.size()) {
				adults[i + 1].setGroupId(familyIdCount);
				sorted.push_back(adults[i + 1]);
				i++;
			}
		}
		familyIdCount++;
	}
	for (int i = 0; i < middles.size(); i++) {
		middles[i].setGroupId(familyIdCount);
		if (getRandom(1, 100) < 20) {
			sorted.push_back(middles[i]);
		}
		else {
			if (i + 1 < middles.size()) {
				middles[i + 1].setGroupId(familyIdCount);
				sorted.push_back(middles[i + 1]);
				i++;
			}
		}
		familyIdCount++;
	}

	//add children to families
	int sortedIndex = 0;
	for (int i = 0; i < kids.size(); i++) {
		kids[i].setGroupId(sorted[sortedIndex].getGroupId());
		if (i + 1 < kids.size()) {
			kids[i+1].setGroupId(sorted[sortedIndex].getGroupId());
			i++;
		}
		//update the sorted index
		if (sortedIndex + 1 < sorted.size()) {
			if (sorted[sortedIndex].getGroupId() == sorted[sortedIndex + 1].getGroupId()) {
				if (sortedIndex + 2 < sorted.size()) {
					sortedIndex += 2;
				}
			}else{
				sortedIndex++;
			}
		}
	}

	//add elderly to families
	sortedIndex = 0;
	for (int i = 0; i < elderly.size(); i++) {
		if (getRandom(1, 100) < 30) { //chance of elderly liveing with adult or middle
			elderly[i].setGroupId(sorted[sortedIndex].getGroupId());
			if (sortedIndex + 1 < sorted.size()) {
				if (sorted[sortedIndex].getGroupId() == sorted[sortedIndex + 1].getGroupId()) {
					if (sortedIndex + 2 < sorted.size()) {
						sortedIndex += 2;
					}
				}
				else {
					sortedIndex++;
				}
			}
		}else { //else they live by themselves or with another old
			elderly[i].setGroupId(familyIdCount);
			if (getRandom(1, 100) > 30) {
				if (i + 1 < elderly.size()) {
					elderly[i + 1].setGroupId(familyIdCount);
					i++;
				}
			}
			familyIdCount++;
		}
	}

	familyIdCount--;
	//groups.resize(familyIdCount);

	//add back all the vectors to the population
	for (int i = 0; i < kids.size(); i++) {
		pop[kids[i].getId()] = kids[i];
		//groups[kids[i].getGroupId()].push_back(kids[i].getId());
	}
	for (int i = 0; i < adults.size(); i++) {
		pop[adults[i].getId()] = adults[i];
		//groups[adults[i].getGroupId()].push_back(kids[i].getId());
	}
	for (int i = 0; i < middles.size(); i++) {
		pop[middles[i].getId()] = middles[i];
		//groups[middles[i].getGroupId()].push_back(kids[i].getId());
	}
	for (int i = 0; i < elderly.size(); i++) {
		pop[elderly[i].getId()] = elderly[i];
		//groups[elderly[i].getGroupId()].push_back(kids[i].getId());
	}
}

void Population::printPop() {
	for (int i = 0; i < pop.size(); i++) {
		cout << "id: " << pop[i].getId() << "\tage: " << pop[i].getAge() << "\tgender: " << pop[i].getGender() << "\tgroup: " <<
			pop[i].getGroupId() << "\tsick?: " << pop[i].isSick() << endl;
	}
}

int Population::getInfected() {
	return sick;
}

int Population::getRandom(int low, int high) {
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<std::mt19937::result_type> dist6(low, high); // distribution in range [1, 6]

	return dist6(rng);
}

//number of ifections, 
//parameter passed in the number of people the sick will infect
//later will implement it affected groups
void Population::infect(int chance) {
	vector<Person> tempPop = pop;//temporary vector for the next 'turn'
	for (int i = 0; i < pop.size(); i++){
		if (pop[i].isSick()) {
			vector<Person> tempPop2 = pop;  //second temperory vector to remove current person and people already infected by that person in the turn
			tempPop2.erase(tempPop2.begin() + i);
			for (int j = 0; j < chance; j++) {
				int temp = getRandom(0, tempPop2.size() - 1);
				tempPop[tempPop2[temp].getId()].setSick(true);
				tempPop2.erase(tempPop2.begin() + i);
			}
		}
	}
	pop = tempPop;
}
