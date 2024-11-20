#include <Windows.h>
#include "JudgeSystem.h"
#include "AdminSystem.h"
#include "GuestSystem.h"
#include "InputWithCheck.h"
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

void loginUser(vector<unique_ptr<User>>& users, const string& username) {
	for (const auto& user : users) {
		if (user->getLogin() == username) {
			string password = "";
			char ch;
			while (true) {
				cout << "Введите пароль: ";
				while ((ch = _getch()) != '\r') {
					password.push_back(ch);
					cout << '*';
				}
				if (user->checkpassword(password)) {
					if (user->getType() == "Администратор") {
						AdminSystem(user->getLogin());
						return;
					}
					if (user->getType() == "Судья") {
						JudgeSystem(user->getLogin());
						return;
					}
				}
				else {
					system("cls");
					cout << "Неверный пароль!";
					WaitButton();
				}
			}
		}
	}
	cout << "Пользователь с таким логином не найден";
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector<unique_ptr<User>> users;
	User user, Admin("Admin", "Admin123", "Администратор");
	users.push_back(make_unique<User>(Admin));
	ifstream file("Users.txt");
	while (file >> user) {
		users.push_back(make_unique<User>(user));
	}
	int choice;
	while (true) {
		system("cls");
		showProgramMenu();
		Input<int>::InputWithCheck(choice);
		switch (choice)
		{
		case 1:
		{
			system("cls");
			string username;
			cout << "Введите логин:" << endl;
			Input<string>::InputWithCheck(username);
			loginUser(users, username);
			break;
		}
		case 2:
		{
			GuestSystem();
			break;
		}
		case 0:
		{
			system("cls");
			cout << "До свидания!";
			return 0;
		}
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