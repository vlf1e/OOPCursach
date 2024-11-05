#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include "Result.h"

using namespace std;

class Competition {
protected:
	string name;
public:
	Competition(const string& name) : name(name) {}
	virtual const string getName() const { return name; }
	virtual void addParticipant(shared_ptr<Result>) = 0;
	virtual void removeParticipant(const string& secondName, const string& firstName, const string& surname) = 0;
	virtual void sortParticipantsByScore() = 0;
	virtual void display() = 0;
	virtual shared_ptr<Result> searchResult(const string& secondName, const string& firstName, const string& surname) = 0;
};

class TimeCompetition : public Competition {
public:
	vector<shared_ptr<TimeResult>> results;
	TimeCompetition(const string& name) : Competition(name) {}

	void addParticipant(shared_ptr<Result> result) override {
		results.push_back(static_pointer_cast<TimeResult>(result));
	}

	void removeParticipant(const string& secondName, const string& firstName, const string& surname) override {
		results.erase(remove_if(results.begin(), results.end(),
			[&](shared_ptr<TimeResult> p) {
				return p->getSecondName() == secondName && p->getFirstName() == firstName
					&& p->getSurname() == surname;
			}), results.end());
	}

	void sortParticipantsByScore() override {
		sort(results.begin(), results.end(),
			[](const shared_ptr<TimeResult>& r1, const shared_ptr<TimeResult>& r2) {
				return r1 > r2;
			});
	}

	void display() override {
		for (const auto& res : results) {
			res->display();
		}
	}

	shared_ptr<Result> searchResult(const string& secondName, const string& firstName, const string& surname) override {
		for (const auto& res : results) {
			if (res->getSecondName() == secondName && res->getFirstName() == firstName
				&& res->getSurname() == surname) return res;
		}
		return nullptr;
	}
};

class ScoreCompetition : public Competition {
public:
	vector<shared_ptr<ScoreResult>> results;
	ScoreCompetition(const string& name) : Competition(name) {}

	void addParticipant(shared_ptr<Result> result) override {
		results.push_back(static_pointer_cast<ScoreResult>(result));
	}

	void removeParticipant(const string& secondName, const string& firstName, const string& surname) override {
		results.erase(remove_if(results.begin(), results.end(),
			[&](shared_ptr<ScoreResult> p) {
				return p->getSecondName() == secondName && p->getFirstName() == firstName
					&& p->getSurname() == surname;
			}), results.end());
	}

	void sortParticipantsByScore() override {
		sort(results.begin(), results.end(),
			[](const shared_ptr<ScoreResult>& r1, const shared_ptr<ScoreResult>& r2) {
				return r1 > r2;
			});
	}

	void display() override {
		for (const auto& res : results) {
			res->display();
		}
	}

	shared_ptr<Result> searchResult(const string& secondName, const string& firstName, const string& surname) override {
		for (const auto& res : results) {
			if (res->getSecondName() == secondName && res->getFirstName() == firstName
				&& res->getSurname() == surname) return res;
		}
		return nullptr;
	}
};

class TextCompetition : public Competition {
public:
	vector<shared_ptr<TextResult>> results;
	TextCompetition(const string& name) : Competition(name) {}

	void addParticipant(shared_ptr<Result> result) override {
		results.push_back(static_pointer_cast<TextResult>(result));
	}

	void removeParticipant(const string& secondName, const string& firstName, const string& surname) override {
		results.erase(remove_if(results.begin(), results.end(),
			[&](shared_ptr<TextResult> p) {
				return p->getSecondName() == secondName && p->getFirstName() == firstName
					&& p->getSurname() == surname;
			}), results.end());
	}

	void sortParticipantsByScore() override {
		cout << "Текстовая форма оценивания не подлежит сортировке!" << endl;
	}

	void display() override {
		for (const auto& res : results) {
			res->display();
		}
	}

	shared_ptr<Result> searchResult(const string& secondName, const string& firstName, const string& surname) override {
		for (const auto& res : results) {
			if (res->getSecondName() == secondName && res->getFirstName() == firstName
				&& res->getSurname() == surname) return res;
		}
		return nullptr;
	}
};