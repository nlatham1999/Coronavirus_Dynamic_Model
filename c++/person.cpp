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
	groupId = 0;
}

Person::Person(string a, string g) {
	age = a;
	daysSick = 0;
	sick = false;
	recovered = false;
	gender = g;
	groupId = 0;
}

string Person::getAge() {
	return age;
}

string Person::getGender() {
	return gender;
}