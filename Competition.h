#pragma once
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include "Result.h"

using namespace std;

class Competition {
	vector<shared_ptr<Result>> results;
public:
	void addParticipant(shared_ptr<Result> result) { results.push_back(result); }
	void removeParticipant(const string& secondName, const string& firstName, const string& surname) {
		results.erase(remove_if(results.begin(), results.end(),
			[&](shared_ptr<Result> p) {
				return p->getSecondName() == secondName && p->getFirstName() == firstName
					&& p->getSurname() == surname;
			}));
	}
	void sortParticipantsByScore() {
		sort(results.begin(), results.end(), 
			[](shared_ptr<Result> r1, shared_ptr<Result> r2) {
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