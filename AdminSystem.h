#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <conio.h>
#include "User.h"
#include "InputWithCheck.h"

using namespace std;

void showMenu(const string& username) {
	system("cls");
	cout << "Добро пожаловать, " << username << '!' << endl;
	cout << "1. Добавить пользователя" << endl;
	cout << "2. Удалить пользователя" << endl;
	cout << "3. Изменить пользователя" << endl;
	cout << "4. Посмотреть пользователей и их данные" << endl;
	cout << "0. Выход" << endl;
}

void addUser() {
	system("cls");
	ofstream file("Users.txt", ios::app);
	string login, password, type;
	char ch;
	int choice;
	cout << "Введите логин: ";
	Input<string>::InputWithCheck(login);
	cout << "Введите пароль: ";
	while ((ch = _getch()) != '\r') {
		password.push_back(ch);
		cout << '*';
	}
	cout << endl;
	cout << "Выберите роль" << endl;
	cout << "1. Администратор" << endl;
	cout << "2. Судья" << endl;
	cout << "3. Гость" << endl;
	Input<int>::InputWithCheck(choice);
	switch (choice)
	{
	case 1:
	{
		type = "Администратор";
		break;
	}
	case 2:
	{
		type = "Судья";
		break;
	}
	case 3:
	{
		type = "Гость";
		break;
	}
	default:
		break;
	}
	if (file) {
		User user(login, password, type);
		file << user << endl;
	}
	file.close();
}

void deleteUser(const string& username) {
	ifstream file1("Users.txt");
	vector<unique_ptr<User>> users;
	User user;
	while (file1 >> user) {
		users.push_back(make_unique<User>(user));
	}
	file1.close();
	ofstream file2("Users.txt");
	for (const auto& usr : users) {
		if (usr->getLogin() == username) continue;
		file2 << *usr << endl;
	}
	cout << "Удаление успешно!" << endl;
	WaitButton();
}

void viewUsers() {
	system("cls");
	ifstream file("Users.txt");
	vector<unique_ptr<User>> users;
	User user;
	while (file >> user) {
		users.push_back(make_unique<User>(user));
	}
	cout << "| " << setw(20) << left << "Логин"
		<< " | " << setw(20) << left << "Роль" << " |" << endl;
	cout << string(47, '-') << endl;
	for (const auto& usr : users) {
		cout << "| " << setw(20) << usr->getLogin()
			<< " | " << setw(20) << usr->getType() << " |" << endl;
		cout << string(47, '-') << endl;
	}
	WaitButton();
	file.close();
}

void viewAdmins() {
	system("cls");
	ifstream file("Users.txt");
	vector<unique_ptr<User>> users;
	User user;
	while (file >> user) {
		users.push_back(make_unique<User>(user));
	}
	cout << "| " << setw(20) << left << "Логин"
		<< " | " << setw(20) << left << "Роль" << " |" << endl;
	cout << string(47, '-') << endl;
	for (const auto& usr : users) {
		if (usr->getType() == "Администратор") {
			cout << "| " << setw(20) << usr->getLogin()
				<< " | " << setw(20) << usr->getType() << " |" << endl;
			cout << string(47, '-') << endl;
		}
	}
	WaitButton();
	file.close();
}

void viewJudges() {
	system("cls");
	ifstream file("Users.txt");
	vector<unique_ptr<User>> users;
	User user;
	while (file >> user) {
		users.push_back(make_unique<User>(user));
	}
	cout << "| " << setw(20) << left << "Логин"
		<< " | " << setw(20) << left << "Роль" << " |" << endl;
	cout << string(47, '-') << endl;
	for (const auto& usr : users) {
		if (usr->getType() == "Судья") {
			cout << "| " << setw(20) << usr->getLogin()
				<< " | " << setw(20) << usr->getType() << " |" << endl;
			cout << string(47, '-') << endl;
		}
	}
	cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
	while (true) {
		if (_kbhit()) {
			while (_kbhit()) _getch();
			break;
		}
	}
	file.close();
}

void view() {
	system("cls");
	int choice;
	cout << "1. Вывести всех" << endl;
	cout << "2. Вывести администраторов" << endl;
	cout << "3. Вывести судей" << endl;
	cout << "0. Вернуться назад" << endl;
	while (true) {
		Input<int>::InputWithCheck(choice);
		switch (choice)
		{
		case 1:
			viewUsers();
			return;
		case 2:
			viewAdmins();
			return;
		case 3:
			viewJudges();
			return;
		case 0:
			return;
		default:
			break;
		}
	}
}

void editUser() {
	system("cls");
	cout << "Введите имя пользователя, которого вы хотите изменить" << endl;
	viewUsers();
	ifstream file("Users.txt");
	vector<unique_ptr<User>> users;
	User user;
	while (file >> user) {
		users.push_back(make_unique<User>(user));
	}
	string username;
	for (const auto& usr : users) {
		if (usr->getLogin() == username) {
			string login, password;
			cout << "Введите имя пользователя" << endl;
			Input<string>::InputWithCheck(login);
			usr->setLogin(login);
			cout << "Введите новый пароль" << endl;
			Input<string>::InputWithCheck(password);
			usr->setPassword(password);
			cout << "Оставить тип учетной записи?" << endl;
			cout << "1. Да" << endl;
			cout << "2. Нет" << endl;
			int choice2;
			while (true) {
				Input<int>::InputWithCheck(choice2);
				if (choice2 == 2) {
					int choice3;
					while (true) {
						cout << "Выберите роль" << endl;
						cout << "1. Администратор" << endl;
						cout << "2. " << endl;
						cout << "Ваш выбор: ";
						Input<int>::InputWithCheck(choice3);
						switch (choice3)
						{
						case 1: user.setType("Администратор"); break;
						case 2: user.setType("Судья"); break;
						default: cout << "Ошибка ввода! Попробуйте ещё раз!" << endl; break;
						}
					}
				}
			}
		}
	}
}

void AdminSystem(const string& username) {
	int choice;
	while (true) {
		showMenu(username);
		Input<int>::InputWithCheck(choice);
		switch (choice)
		{
		case 1:
			addUser();
			break;
		case 2:
		{
			system("cls");
			viewUsers();
			string username;
			cout << "Введите имя пользователя, которого вы хотите удалить" << endl;
			Input<string>::InputWithCheck(username);
			deleteUser(username);
			break;
		}
		case 3:
		{
			editUser();
			break;
		}
		case 4:
		{
			view();
			break;
		}	
		case 0:
			cout << "До свидания, " << username << endl;
			WaitButton();
			return;
		default:
			cout << "Ошибка ввода!" << endl;
			WaitButton();
			break;
		}
	}
}
