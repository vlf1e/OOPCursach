#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "Competition.h"
#include "Result.h"
#include "Time.h"

using namespace std;

void ShowMenu() {
	//system("cls");
	cout << "1. �������� ������������" << endl;
	cout << "2. ���������������� ���������" << endl;
	cout << "3. ���������� ����� ������������" << endl;
	cout << "4. ������� ����� ������������ � ����" << endl;
	cout << "0. �����" << endl;
	cout << "��� �����: ";
}

void addCompetition(vector<shared_ptr<Competition>>& competitions) {
	string name;
	system("cls");
	cout << "������� ��� ������������: ";
	cin >> name;
	int type;
	cout << "�������� ��� ���������� ������������:" << endl;
	cout << "1. �����" << endl;
	cout << "2. ����" << endl;
	cout << "3. �����" << endl;
	cin >> type;
	shared_ptr<Competition> competition;
	switch (type) {
	case 1:
		competition = make_shared<TimeCompetition>(name);
		break;
	case 2:
		competition = make_shared<ScoreCompetition>(name);
		break;
	case 3:
		competition = make_shared<TextCompetition>(name);
		break;
	default:
		cout << "�������� ��� ����������!" << endl;
		return;
	}
	competitions.push_back(competition);
	cout << "������������ ���������!" << endl;
}

void addResult(vector<shared_ptr<Competition>>& competitions) {
	for (const auto& competition : competitions) {
		cout << competition->getName() << endl;
	}
	string name;
	cout << "������� ��� ������������, � ������� ���������� �������� ���������: ";
	cin >> name;
	for (const auto& competition : competitions) {
		if (name == competition->getName()) {
			string secondName, firstName, surname, country;
			int age;
			cout << "������� �������: ";
			cin >> secondName;
			cout << "������� ���: ";
			cin >> firstName;
			cout << "������� ��������: ";
			cin >> surname;
			cout << "������� ������: ";
			cin >> country;
			cout << "������� �������: ";
			cin >> age;
			Participant participant(secondName, firstName, surname, country, age);
			if (typeid(*competition) == typeid(TimeCompetition)) {
				cout << "������� ����� (������ �������: ������:�������:������������): ";
				Time time;
				try
				{
					cin >> time;
				}
				catch (const TimeException& e)
				{
					cerr << e.what() << endl;
				}

				shared_ptr<Result> ptr = make_shared<TimeResult>(participant, time);
				competition->addParticipant(ptr);
				cout << "��������� ��������!" << endl;
				return;
			}
			if (typeid(*competition) == typeid(ScoreCompetition)) {
				cout << "������� ����: ";
				double score;
				cin >> score;
				shared_ptr<Result> ptr = make_shared<ScoreResult>(participant, score);
				competition->addParticipant(ptr);
				cout << "��������� ��������!" << endl;
				return;
			}
			if (typeid(*competition) == typeid(TextCompetition)) {
				cout << "������� ���� ������: ";
				string text;
				cin.ignore();
				getline(cin, text);
				shared_ptr<Result> ptr = make_shared<TextResult>(participant, text);
				competition->addParticipant(ptr);
				cout << "��������� ��������!" << endl;
				return;
			}
		}
	}
	cout << "������������ �� �������!" << endl;
}

void display(const vector<shared_ptr<Competition>>& competitions) {
	for (const auto& comp : competitions) {
		cout << comp->getName() << endl;
	}
	string name;
	cout << "������� ��� ������������, ������� ���������� ������� �� �����: ";
	cin >> name;
	for (const auto& comp : competitions) {
		if (comp->getName() == name) {
			cout << "������������: " << name << endl;
			cout << string(120, '-');
			cout << "| " << setw(22) << left << "�������"
				<< " | " << setw(15) << left << "���"
				<< " | " << setw(18) << left << "��������"
				<< " | " << setw(16) << left << "������"
				<< " | " << setw(10) << left << "�������"
				<< " | " << setw(20) << left << "���������"
				<< " |" << endl;
			cout << string(120, '-');
			comp->display();
			return;
		}
	}
	cout << "������������ �� �������!" << endl;
}

void JudgeSystem() {
	vector<shared_ptr<Competition>> competitions;
	while (true) {
		ShowMenu();
		int choice;
		cin >> choice;
		switch (choice) {
		case 1:
			addCompetition(competitions);
			break;
		case 2:
			addResult(competitions);
			break;
		case 3:
			display(competitions);
			break;
		case 4:
			break;
		case 0:
			cout << "����� �� ���������." << endl;
			return;
		default:
			cout << "�������� �����!" << endl;
			break;
		}
	}
}