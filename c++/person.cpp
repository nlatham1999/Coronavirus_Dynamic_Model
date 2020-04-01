//Person.cpp
//Nick Latham 3/26/2020

#include "Person.h"
#include <string>

using namespace std;

Person::Person() {
	age = "kid";
	daysSick = 0;
	sick = false;
	recovered = false;
	gender = "male";
	id = 0;
	groupId = 0;
}

Person::Person(string a, string g, int i) {
	age = a;
	daysSick = 0;
	sick = false;
	recovered = false;
	gender = g;
	groupId = 0;
	id = i;	
}

string Person::getAge() {
	return age;
}

string Person::getGender() {
	return gender;
}

void Person::setGroupId(int i) {
	groupId = i;
}

int Person::getGroupId() {
	return groupId;
}

int Person::getId() {
	return id;
}

void Person::setSick(bool s) {
	sick = s;
}


bool Person::isSick() {
	return sick;
}
