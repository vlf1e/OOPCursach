#pragma once
#include <iostream>
#include <fstream>
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
};

class TimeResult : public Result {
	Time time;
public:
	TimeResult(Participant& participant, Time& time) : 
		time(time), Result(participant) {};
	void display() override {
		cout << participant << "result: " << time << endl;
	}
	any getResult() override { return time; }
};

class ScoreResult : public Result {
	double score;
public:
	ScoreResult(Participant& participant, double& score) : 
		score(score), Result(participant) {};
	void display() override {
		cout << participant << "result: " << score << endl;
	}
	any getResult() override { return score; }
};

class TextResult : public Result {
	string text;
public:
	TextResult(Participant& participant, const string& text) : 
		text(text), Result(participant) {};
	void display() override {
		cout << participant << "result: " << text << endl;
	}
	any getResult() override { return text; }
};