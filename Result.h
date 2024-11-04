#pragma once
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <any>
#include "Participant.h"
#include "Time.h"

using namespace std;

class Result {
protected:
	Participant participant;
public:
	Result(Participant& participant) :
		participant(participant) {};
	virtual void display() = 0;
	virtual any getResult() = 0;
	virtual const string getSecondName() { return participant.getSecondName(); }
	virtual const string getFirstName() { return participant.getFirstName(); }
	virtual const string getSurname() { return participant.getSurname(); }
	virtual const string getCountry() { return participant.getCountry(); }
	virtual const int getAge() { return participant.getAge(); }
};

class TimeResult : public Result {
	Time time;
public:
	TimeResult(Participant& participant, Time& time) :
		time(time), Result(participant) {};
	void display() override {
		cout << participant << setw(15) << time << " |" << endl;
	}
	any getResult() override { return time; }
	friend bool operator>(TimeResult& t1, TimeResult& t2) {
		return t1.time > t2.time;
	}
};

class ScoreResult : public Result {
	double score;
public:
	ScoreResult(Participant& participant, double& score) :
		score(score), Result(participant) {};
	void display() override {
		cout << participant << setw(15) << score << " |" << endl;
	}
	any getResult() override { return score; }
	friend bool operator>(ScoreResult& s1, ScoreResult s2) {
		return s1.score > s2.score;
	}
};

class TextResult : public Result {
	string text;
public:
	TextResult(Participant& participant, const string& text) :
		text(text), Result(participant) {};
	void display() override {
		cout << participant << setw(15) << text << " |" << endl;
	}
	any getResult() override { return text; }
	friend bool operator>(TextResult t1, TextResult t2) {
		return false;
	}
};