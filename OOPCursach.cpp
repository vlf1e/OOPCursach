#include <Windows.h>
#include "JudgeSystem.h"
#include "AdminSystem.h"
#include "GuestSystem.h"
#include "User.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <string>

using namespace std;

namespace Color {
	enum TextColor {
		DEFAULT = 7,
		RED = 4,
		GREEN = 2,
		BLUE = 1,
		YELLOW = 6,
		MAGENTA = 5,
		CYAN = 3,
		WHITE = 15
	};

	void setTextColor(TextColor color) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	}

	void resetTextColor() {
		setTextColor(DEFAULT);
	}
}

void showProgramMenu() {
	system("cls");
	Color::setTextColor(Color::MAGENTA);
	cout << "Добро пожаловать в автоматизированную систему судейства по различным видам спорта!" << endl;
	Color::resetTextColor();
	cout << "Что хотите сделать:" << endl;
	cout << "1. Зайти в аккаунт" << endl;
	cout << "2. Использовать гостевой доступ" << endl;
	cout << "0. Выход" << endl;
	cout << "Ваш выбор: ";
}

int main()
{
	setlocale(LC_ALL, "");
	vector<unique_ptr<User>> users;
	User user;
	ifstream file("Users.txt");
	while (file >> user) {
		users.push_back(make_unique<User>(user));
	}
	int choice;
	while (true) {
		showProgramMenu();
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(100000000, '\n');
			cout << "Ошибка ввода!" << endl;
			cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
			while (true) {
				if (_kbhit()) {
					while (_kbhit()) _getch();
					break;
				}
			}
			continue;
		}
		switch (choice)
		{
		case 1:
		{
			system("cls");
			string login, password = "";
			cout << "Введите логин" << endl;
			cin >> login;
			if (login != "Guest") {
				bool found = 0;
				for (const auto& usr : users) {
					if (usr->getLogin() == login) {
						found = 1;
						while (true) {
							char ch;
							cout << "Введите пароль: " << endl;
							while ((ch = _getch()) != '\r') {
								password.push_back(ch);
								cout << '*';
							}
							cout << endl;
							if (usr->checkpassword(password)) {
								if (usr->getType() == "Администратор") {
									AdminSystem(usr->getLogin());
									break;
								}
								else if (usr->getType() == "Судья") {
									JudgeSystem(usr->getLogin());
									break;
								}
								else return 0;
							}
							else {
								password = "";
								cout << "Неверный пароль!" << endl;
							}
						}
					}
				}
				if (!found) cout << "Неверный логин!" << endl;
			}
			continue;
		}
		case 2:
			GuestSystem();
			break;
		case 0:
			system("cls");
			cout << "До свидания!";
			return 0;
		default:
			system("cls");
			cout << "Ошибка ввода!" << endl;
			cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
			while (true) {
				if (_kbhit()) {
					while (_kbhit()) _getch();
					break;
				}
			}
			break;
		}
	}
	return 0;
}