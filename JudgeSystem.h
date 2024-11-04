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
	cout << "1. Добавить соревнование" << endl;
	cout << "2. Зарегистрировать результат" << endl;
	cout << "3. Посмотреть итоги соревнований" << endl;
	cout << "4. Вывести итоги соревнования в файл" << endl;
	cout << "0. Выход" << endl;
	cout << "Ваш выбор: ";
}

void addCompetition(vector<shared_ptr<Competition>>& competitions) {
	string name;
	system("cls");
	cout << "Введите имя соревнования: ";
	cin >> name;
	int type;
	cout << "Выберите тип оценивания соревнования:" << endl;
	cout << "1. Время" << endl;
	cout << "2. Очки" << endl;
	cout << "3. Текст" << endl;
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
		cout << "Неверный тип оценивания!" << endl;
		return;
	}
	competitions.push_back(competition);
	cout << "Соревнование добавлено!" << endl;
}

void addResult(vector<shared_ptr<Competition>>& competitions) {
	for (const auto& competition : competitions) {
		cout << competition->getName() << endl;
	}
	string name;
	cout << "Введите имя соревнования, в которое необходимо добавить результат: ";
	cin >> name;
	for (const auto& competition : competitions) {
		if (name == competition->getName()) {
			string secondName, firstName, surname, country;
			int age;
			cout << "Введите фамилию: ";
			cin >> secondName;
			cout << "Введите имя: ";
			cin >> firstName;
			cout << "Введите отчество: ";
			cin >> surname;
			cout << "Введите страну: ";
			cin >> country;
			cout << "Введите возраст: ";
			cin >> age;
			Participant participant(secondName, firstName, surname, country, age);
			cout << "Какой тип результата?" << endl;
			cout << "1. Время" << endl;
			cout << "2. Очки" << endl;
			cout << "3. Текст" << endl;
			int switch_on;
			cout << "Ваш выбор: ";
			cin >> switch_on;
			switch (switch_on) {
			case 1: {
				if (typeid(*competition) == typeid(TimeCompetition)) {
					cout << "Введите время (формат времени: минуты:секунды:миллисекунды): ";
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
					cout << "Результат добавлен!" << endl;
				}
				else cout << "Неверный тип" << endl;
				break;
			}
			case 2: {
				if (typeid(*competition) == typeid(ScoreCompetition)) {
					cout << "Введите очки: ";
					double score;
					cin >> score;
					shared_ptr<Result> ptr = make_shared<ScoreResult>(participant, score);
					competition->addParticipant(ptr);
					cout << "Результат добавлен!" << endl;
				}
				else cout << "Неверный тип" << endl;
				break;
			}
			case 3: {
				if (typeid(*competition) == typeid(TextCompetition)) {
					cout << "Введите вашу оценку: ";
					string text;
					cin >> text;
					shared_ptr<Result> ptr = make_shared<TextResult>(participant, text);
					competition->addParticipant(ptr);
					cout << "Результат добавлен!" << endl;
				}
				else cout << "Неверный тип" << endl;
				break;
			}
			default:
				cout << "Ошибка ввода!" << endl;
				break;
			}
			return;
		}
	}
	cout << "Соревнование не найдено!" << endl;
}

void display(const vector<shared_ptr<Competition>>& competitions) {
	for (const auto& comp : competitions) {
		cout << comp->getName() << endl;
	}
	string name;
	cout << "Введите имя соревнования, которое необходимо вывести на экран: ";
	cin >> name;
	for (const auto& comp : competitions) {
		if (comp->getName() == name) {
			comp->display();
			return;
		}
	}
	cout << "Соревнование не найдено!" << endl;
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
			// Реализация для вывода в файл
			cout << "Эта функция еще не реализована." << endl;
			break;
		case 0:
			cout << "Выход из программы." << endl;
			return;
		default:
			cout << "Неверный выбор!" << endl;
			break;
		}
	}
}