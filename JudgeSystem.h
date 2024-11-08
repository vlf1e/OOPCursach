#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <conio.h>
#include "Competition.h"
#include "Result.h"
#include "Time.h"

using namespace std;

void ShowMenu(const string& username) {
	system("cls");
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
	if (cin.fail()) {
		cout << "Ошибка ввода!" << endl;
		cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
		while (true) {
			if (_kbhit()) {
				while (_kbhit()) _getch();
				break;
			}
		}
		cin.clear();
		return;
	}
	int type;
	cout << "Выберите тип оценивания соревнования:" << endl;
	cout << "1. Время" << endl;
	cout << "2. Очки" << endl;
	cout << "3. Текст" << endl;
	cin >> type;
	if (cin.fail()) {
		cout << "Ошибка ввода!" << endl;
		cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
		while (true) {
			if (_kbhit()) {
				while (_kbhit()) _getch();
				break;
			}
		}
		cin.clear();
		return;
	}
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
	cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
	while (true) {
		if (_kbhit()) {
			while (_kbhit()) _getch();
			break;
		}
	}
}

void addResult(vector<shared_ptr<Competition>>& competitions) {
	system("cls");
	cout << "| " << setw(30) << left << "Имя соревнования" << " |" << endl;
	cout << string(34, '-') << endl;
	for (const auto& competition : competitions) {
		cout << "| " << setw(30) << left << competition->getName() << " |" << endl;
		cout << string(34, '-') << endl;
	}
	string name;
	cout << "Введите имя соревнования, в которое необходимо добавить результат: ";
	cin >> name;
	if (cin.fail()) {
		cout << "Ошибка ввода!" << endl;
		cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
		while (true) {
			if (_kbhit()) {
				while (_kbhit()) _getch();
				break;
			}
		}
		cin.clear();
		return;
	}
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
			if (cin.fail()) {
				cout << "Ошибка ввода!" << endl;
				cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
				while (true) {
					if (_kbhit()) {
						while (_kbhit()) _getch();
						break;
					}
				}
				cin.clear();
				return;
			}
			Participant participant(secondName, firstName, surname, country, age);
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
				cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
				while (true) {
					if (_kbhit()) {
						while (_kbhit()) _getch();
						break;
					}
				}
				return;
			}
			if (typeid(*competition) == typeid(ScoreCompetition)) {
				cout << "Введите очки: ";
				double score;
				cin >> score;
				if (cin.fail()) {
					cout << "Ошибка ввода!" << endl;
					cin.clear();
					return;
				}
				shared_ptr<Result> ptr = make_shared<ScoreResult>(participant, score);
				competition->addParticipant(ptr);
				cout << "Результат добавлен!" << endl;
				cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
				while (true) {
					if (_kbhit()) {
						while (_kbhit()) _getch();
						break;
					}
				}
				return;
			}
			if (typeid(*competition) == typeid(TextCompetition)) {
				cout << "Введите вашу оценку: ";
				string text;
				cin.ignore();
				getline(cin, text);
				if (cin.fail()) {
					cout << "Ошибка ввода!" << endl;
					cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
					while (true) {
						if (_kbhit()) {
							while (_kbhit()) _getch();
							break;
						}
					}
					cin.clear();
					return;
				}
				shared_ptr<Result> ptr = make_shared<TextResult>(participant, text);
				competition->addParticipant(ptr);
				cout << "Результат добавлен!" << endl;
				cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
				while (true) {
					if (_kbhit()) {
						while (_kbhit()) _getch();
						break;
					}
				}
				return;
			}
		}
	}
	cout << "Соревнование не найдено!" << endl;
	cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
	while (true) {
		if (_kbhit()) {
			while (_kbhit()) _getch();
			break;
		}
	}
}

void display(const vector<shared_ptr<Competition>>& competitions) {
	system("cls");
	cout << "| " << setw(30) << left << "Имя соревнования" << " |" << endl;
	cout << string(34, '-') << endl;
	for (const auto& competition : competitions) {
		cout << "| " << setw(30) << left << competition->getName() << " |" << endl;
		cout << string(34, '-') << endl;
	}
	string name;
	cout << "Введите имя соревнования, которое необходимо вывести на экран: ";
	cin >> name;
	if (cin.fail()) {
		cout << "Ошибка ввода!" << endl;
		cin.clear();
		cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
		while (true) {
			if (_kbhit()) {
				while (_kbhit()) _getch();
				break;
			}
		}
		return;
	}
	for (const auto& comp : competitions) {
		if (comp->getName() == name) {
			if (typeid(*comp) != typeid(TextCompetition)) comp->sortParticipantsByScore();
			cout << "Соревнование: " << name << endl;
			cout << string(120, '-');
			cout << "| " << setw(5) << left << "Место"
				<< " | " << setw(17) << left << "Фамилия"
				<< " | " << setw(15) << left << "Имя"
				<< " | " << setw(15) << left << "Отчество"
				<< " | " << setw(16) << left << "Страна"
				<< " | " << setw(10) << left << "Возраст"
				<< " | " << setw(20) << left << "Результат"
				<< " |" << endl;
			cout << string(120, '-');
			comp->display();
			cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
			while (true) {
				if (_kbhit()) {
					while (_kbhit()) _getch();
					break;
				}
			}
			return;
		}
	}
	cout << "Соревнование не найдено!" << endl;
	cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
	while (true) {
		if (_kbhit()) {
			while (_kbhit()) _getch();
			break;
		}
	}
}
void outputToFile(vector<shared_ptr<Competition>>& competitions) {
	cout << "| " << setw(30) << left << "Имя соревнования" << " |" << endl;
	cout << string(34, '-') << endl;
	for (const auto& competition : competitions) {
		cout << "| " << setw(30) << left << competition->getName() << " |" << endl;
		cout << string(34, '-') << endl;
	}
	string name;
	cout << "Введите имя соревнования, для которого необходимо составить отчёт: ";
	cin >> name;
	if (cin.fail()) {
		cout << "Ошибка ввода!" << endl;
		cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
		while (true) {
			if (_kbhit()) {
				while (_kbhit()) _getch();
				break;
			}
		}
		cin.clear();
		return;
	}
	ofstream file("Отчёт.txt");
	for (const auto& comp : competitions) {
		int i = 1;
		if (comp->getName() == name) {
			if (typeid(*comp) != typeid(TextCompetition)) comp->sortParticipantsByScore();
			file << "Соревнование: " << name << endl;
			file << string(120, '-') << endl;
			file << "| " << setw(5) << left << "Место"
				<< " | " << setw(17) << left << "Фамилия"
				<< " | " << setw(15) << left << "Имя"
				<< " | " << setw(15) << left << "Отчество"
				<< " | " << setw(16) << left << "Страна"
				<< " | " << setw(10) << left << "Возраст"
				<< " | " << setw(20) << left << "Результат"
				<< " |" << endl;
			file << string(120, '-') << endl;
			comp->outputToFile(file);
			file.close();
			cout << "Отчёт создан!" << endl;
			cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
			while (true) {
				if (_kbhit()) {
					while (_kbhit()) _getch();
					break;
				}
			}
			return;
		}
	}
}
void JudgeSystem(const string& username) {
	vector<shared_ptr<Competition>> competitions;
	while (true) {
		ShowMenu(username);
		int choice;
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(100000000, '\n');
			cout << "Ошибка ввода!" << endl;
			continue;
		}
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
			outputToFile(competitions);
			break;
		case 0:
			system("cls");
			cout << "Выход из программы." << endl;
			return;
			break;
		default:
			cout << "Неверный выбор!" << endl;
			break;
		}
	}
}