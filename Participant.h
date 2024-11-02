#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Participant {
	string secondName, firstName, surname, country;
	int age;
public:
	Participant(const string& secondName, const string& firstName,
		const string& surname, const string& country, const int& age) :
		secondName(secondName), firstName(firstName), surname(surname), country(country), age(age) {};
	const string getSecondName() { return secondName; }
	const string getFirstName() { return firstName; }
	const string getSurname() { return surname; }
	const string getCountry() { return country; }
	const int getAge() { return age; }
	void setSecondName(const string& secondName) { this->secondName = secondName; }
	void setFirstName(const string& firstName) { this->firstName = firstName; }
	void setSurname(const string& surname) { this->surname; }
	void setCountry(const string& country) { this->country = country; }
	void setAge(const int& age) { this->age; }
	friend ostream& operator<<(ostream& o, const Participant& p) {
		o << p.secondName << ' ' << p.firstName << ' ' 
			<< p.surname << ' ' << p.age << ' ' << p.country << endl;
		return o;
	}
};