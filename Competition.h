#pragma once
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include "Result.h"

using namespace std;

class Competition {
public:
	virtual void addParticipant() = 0;
	virtual void removeParticipant() = 0;
	virtual void sortParticipantsByScore() = 0;
	virtual shared_ptr<Result> searchResult() = 0;
};

class TimeCompetition : Competition {
	vector<shared_ptr<TimeResult>> results;
public:
	void addParticipant(shared_ptr<TimeResult> result) { 
		results.push_back(result);
	}
	void removeParticipant(const string& secondName, const string& firstName, const string& surname) {
		results.erase(remove_if(results.begin(), results.end(),
			[&](shared_ptr<TimeResult> p) {
				return p->getSecondName() == secondName && p->getFirstName() == firstName
					&& p->getSurname() == surname;
			}));
	}
	void sortParticipantsByScore() {
		sort(results.begin(), results.end(), 
			[](shared_ptr<TimeResult> r1, shared_ptr<TimeResult> r2) {
				return r1 > r2;
			});
	}
	shared_ptr<Result> searchResult(const string& secondName, const string& firstName, const string& surname) {
		for (const auto res : results) {
			if (res->getSecondName() == secondName && res->getFirstName() == firstName
				&& res->getSurname() == surname) return res;
		}
	}
};

class ScoreCompetition : Competition {
	vector<shared_ptr<ScoreResult>> results;
public:
	void addParticipant(shared_ptr<ScoreResult> result) {
		results.push_back(result);
	}
	void removeParticipant(const string& secondName, const string& firstName, const string& surname) {
		results.erase(remove_if(results.begin(), results.end(),
			[&](shared_ptr<ScoreResult> p) {
				return p->getSecondName() == secondName && p->getFirstName() == firstName
					&& p->getSurname() == surname;
			}));
	}
	void sortParticipantsByScore() {
		sort(results.begin(), results.end(),
			[](shared_ptr<ScoreResult> r1, shared_ptr<ScoreResult> r2) {
				return r1 > r2;
			});
	}
	shared_ptr<Result> searchResult(const string& secondName, const string& firstName, const string& surname) {
		for (const auto res : results) {
			if (res->getSecondName() == secondName && res->getFirstName() == firstName
				&& res->getSurname() == surname) return res;
		}
	}
};
class TextCompetition : Competition {
	vector<shared_ptr<TextResult>> results;
public:
	void addParticipant(shared_ptr<TextResult> result) {
		results.push_back(result);
	}
	void removeParticipant(const string& secondName, const string& firstName, const string& surname) {
		results.erase(remove_if(results.begin(), results.end(),
			[&](shared_ptr<TextResult> p) {
				return p->getSecondName() == secondName && p->getFirstName() == firstName
					&& p->getSurname() == surname;
			}));
	}
	shared_ptr<Result> searchResult(const string& secondName, const string& firstName, const string& surname) {
		for (const auto res : results) {
			if (res->getSecondName() == secondName && res->getFirstName() == firstName
				&& res->getSurname() == surname) return res;
		}
	}
};
