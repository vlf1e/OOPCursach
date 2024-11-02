#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <exception>
#include <string>

using namespace std;

class TimeException : public exception{
	string msg;
public:
	TimeException(const string& msg) : msg(msg) {};
	virtual const char* what() const noexcept override {
		return msg.c_str();
	}
};

class Time {
	int minutes, seconds, milliseconds;
public:
	Time(const int min, const int sec, const int millsec) {
		if (min > 60 && sec > 60 && millsec > 1000) {
			throw TimeException("Некорректные данные\n");
		}
		this->minutes = min;
		this->seconds = sec;
		this->milliseconds = millsec;
	}
	friend istream& operator>>(istream& i, Time& t) {
		char ch;
		i >> t.minutes >> ch >> t.seconds >> ch >> t.milliseconds;
		return i;
	}
	friend ostream& operator<<(ostream& o, const Time& t) {
		o << t.minutes << ':' << t.seconds << ':' << t.milliseconds << endl;
		return o;
	}
	friend ifstream& operator>>(ifstream& i, Time& t) {
		char ch;
		i >> t.minutes >> ch >> t.seconds >> ch >> t.milliseconds;
		return i;
	}
	friend ofstream& operator<<(ofstream& o, const Time& t) {
		o << t.minutes << ':' << t.seconds << ':' << t.milliseconds << endl;
		return o;
	}
};