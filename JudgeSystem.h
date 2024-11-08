#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <conio.h>
#include "Competition.h"
#include "Result.h"
#include "Time.h"

using namespace std;

const string filterLine(const string& line) {
	string filteredLine = "";
	for (int i = 2, j = 0; i < line.size(); i++) {
		if (line[i] != '|') {
			if (line[i] == ' ' && filteredLine.size() > 0) {
				if (filteredLine[j - 1] == ' ') {
					continue;
				}
				else {
					filteredLine.push_back(line[i]);
					j++;
				}
			}
			else {
				filteredLine.push_back(line[i]);
				j++;
			}
		}
	}
	filteredLine.erase(0, 2);
	return filteredLine;
}

void ShowMenu(const string& username) {
	system("cls");
	cout << "Добро пожаловать, " << username << '!' << endl;
	cout << "1. Добавить соревнование" << endl;
	cout << "2. Зарегистрировать результат" << endl;
	cout << "3. Посмотреть итоги соревнований" << endl;
	cout << "4. Вывести итоги соревнования в файл" << endl;
	cout << "5. Загрузить данные из файлов" << endl;
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

void displayAll(const vector<shared_ptr<Competition>>& competitions) {
	system("cls");
	for (const auto& comp : competitions) {
		if (typeid(*comp) != typeid(TextCompetition)) comp->sortParticipantsByScore();
		cout << "Соревнование: " << comp->getName() << endl;
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
	}
	cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
	while (true) {
		if (_kbhit()) {
			while (_kbhit()) _getch();
			break;
		}
	}
}

void displayByName(const vector<shared_ptr<Competition>>& competitions) {
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

void displayTimeComp(const vector<shared_ptr<Competition>>& competitions) {
	system("cls");
	for (const auto& comp : competitions) {
		if (typeid(*comp) == typeid(TimeCompetition)) {
			comp->sortParticipantsByScore();
			cout << "Соревнование: " << comp->getName() << endl;
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
		}
	}
	cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
	while (true) {
		if (_kbhit()) {
			while (_kbhit()) _getch();
			break;
		}
	}
}

void displayScoreComp(vector<shared_ptr<Competition>>& competitions) {
	system("cls");
	for (const auto& comp : competitions) {
		if (typeid(*comp) == typeid(ScoreCompetition)) {
			comp->sortParticipantsByScore();
			cout << "Соревнование: " << comp->getName() << endl;
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
		}
	}
	cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
	while (true) {
		if (_kbhit()) {
			while (_kbhit()) _getch();
			break;
		}
	}
}

void displayTextComp(vector<shared_ptr<Competition>>& competitions) {
	system("cls");
	for (const auto& comp : competitions) {
		if (typeid(*comp) == typeid(TextCompetition)) {
			comp->sortParticipantsByScore();
			cout << "Соревнование: " << comp->getName() << endl;
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
		}
	}
	cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
	while (true) {
		if (_kbhit()) {
			while (_kbhit()) _getch();
			break;
		}
	}
}

void display(vector<shared_ptr<Competition>>& competitions) {
	system("cls");
	int choice;
	cout << "Что вывести?" << endl;
	cout << "1. Вывести все" << endl;
	cout << "2. Вывести конкретное соревнование" << endl;
	cout << "3. Вывести все соровнования с типом оценки \"Время\"" << endl;
	cout << "4. Вывести все соровнования с типом оценки \"Очки\"" << endl;
	cout << "5. Вывести все соровнования с типом оценки \"Текст\"" << endl;
	cout << "0. Вернуться назад" << endl;
	cout << "Ваш выбор: " << endl;
	while (true) {
		cin >> choice;
		if (cin.fail()) {
			cout << "Ошибка ввода!" << endl;
			cin.clear();
			cin.ignore(1000000, '\n');
			continue;
		}
		switch (choice)
		{
		case 1:
			displayAll(competitions);
			return;
		case 2:
			displayByName(competitions);
			return;
		case 3:
			displayTimeComp(competitions);
			return;
		case 4:
			displayScoreComp(competitions);
			return;
		case 5:
			displayTextComp(competitions);
			return;
		case 0:
			return;
		default:
			break;
		}
	}
}

void makeReport(vector<shared_ptr<Competition>>& competitions) {
	system("cls");
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
	string filename_and_path = "Отчёты\\Отчёт соревнования " + name + ".txt";
	ofstream file(filename_and_path);
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
			ifstream tempIn("temp\\competitions_names.txt");
			string temp;
			while (tempIn >> temp) {
				if (temp == name) {
					cout << "Отчёт создан!" << endl;
					cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
					while (true) {
						if (_kbhit()) {
							while (_kbhit()) _getch();
							break;
						}
					}
					tempIn.close();
					return;
				}
			}
			ofstream tempOut("temp\\competitions_names.txt", ios::app);
			tempOut << name << endl;
			tempOut.close();
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

void getDataFromFile(vector<shared_ptr<Competition>>& competitions) {
	ifstream temp("temp\\competitions_names.txt");
	bool filter = false, isTime = false, isScore = false;
	vector<string> names;
	string name, line;
	while (temp >> name) names.push_back(name);
	temp.close();
	for (const auto& n : names) {
		shared_ptr<TimeCompetition> timeComp = make_shared<TimeCompetition>(n);
		shared_ptr<ScoreCompetition> scoreComp = make_shared<ScoreCompetition>(n);
		shared_ptr<TextCompetition> textComp = make_shared<TextCompetition>(n);
		int minutes = 100, seconds = 100, milliseconds = 1000;
		double scr;
		string filename_and_path = "Отчёты\\Отчёт соревнования " + n + ".txt";
		ifstream in(filename_and_path);
		while (in) {
			if (filter && line[0] != '-') {
				stringstream ss(line);
				string secondName, firstName, surname, country, score;
				int age;
				ss >> secondName >> firstName >> surname >> country >> age >> score;
				Participant part(secondName, firstName, surname, country, age);
				int count = 0;
				for (const auto& ch : score) {
					if (ch == ':') count++;
				}
				if (count == 2) {
					isTime = true;
					count = 0;
					string temp = "";
					for (int i = 0; i < score.size() + 1; i++) {
						if (score[i] == ':' && count == 0) {
							count++;
							try {
								minutes = stoi(temp);
							}
							catch (const exception& e) {
								isTime = false;
								break;
							}
							temp = "";
							continue;
						}
						else if (score[i] == ':' && count == 1) {
							count++;
							try {
								seconds = stoi(temp);
							}
							catch (const exception& e) {
								isTime = false;
								break;
							}
							temp = "";
							continue;
						}
						else if (count == 2 && i == score.size()) {
							try {
								milliseconds = stoi(temp);
							}
							catch (const exception& e) {
								isTime = false;
								break;
							}
							temp = "";
							continue;
						}
						temp.push_back(score[i]);
					}
				}
				else {
					try {
						scr = stod(score);
						isScore = true;
					}
					catch (const exception& e) {
						isScore = false;
					}
				}
				if (isTime) {
					Time time(minutes, seconds, milliseconds);
					shared_ptr<TimeResult> res = make_shared<TimeResult>(part, time);
					timeComp->addParticipant(res);
					competitions.push_back(timeComp);
				}
				if (isScore) {
					shared_ptr<ScoreResult> res = make_shared<ScoreResult>(part, scr);
					scoreComp->addParticipant(res);
					competitions.push_back(scoreComp);
				}
			}
			getline(in, line);
			if (line[0] == '|') {
				line = filterLine(line);
				filter = true;
			}
		}
	}
}

void JudgeSystem(const string& username) {
	vector<shared_ptr<Competition>> competitions;
	getDataFromFile(competitions);
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
			makeReport(competitions);
			break;
		case 5:
			getDataFromFile(competitions);
			break;
		case 0:
			system("cls");
			cout << "До свидания, " << username << endl;
			cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
			while (true) {
				if (_kbhit()) {
					while (_kbhit()) _getch();
					break;
				}
			}
			return;
		default:
			cout << "Неверный выбор!" << endl;
			break;
		}
	}
}
