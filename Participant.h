#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <exception>

using namespace std;

class ParticipantException : exception {
	string msg;
public:
	ParticipantException(const string& msg) : msg(msg) {};
	virtual const char* what() const noexcept override {
		return msg.c_str();
	}
};

class Participant {
	string secondName, firstName, surname, country;
	int age;
public:
	Participant(const string& secondName, const string& firstName,
		const string& surname, const string& country, const int& age) :
		secondName(secondName), firstName(firstName), surname(surname), country(country) {
		if (age > 100) throw ParticipantException("¬озраст участника не может быть больше 100 лет!\n");
		this->age = age;
	};
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
		o << "| " << setw(17) << left << p.secondName
			<< " | " << setw(15) << left << p.firstName
			<< " | " << setw(15) << left << p.surname
			<< " | " << setw(16) << left << p.country
			<< " | " << setw(10) << left << p.age
			<< " | ";
		return o;
	}
};