#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include "User.h"

using namespace std;

void showMenu(const string& username) {
	system("cls");
	cout << "Добро пожаловать " << username << '!' << endl;
	cout << "1. Добавить пользователя" << endl;
	cout << "2. Удалить пользователя" << endl;
	cout << "3. Посмотреть пользователя" << endl;
	cout << "0. Выход" << endl;
}
void addUser() {
	ofstream file("Users.txt", ios::app);
	string login, password, type;
	int choice;
	cout << "Введите логин: ";
	cin >> login;
	cout << "Введите пароль: ";
	cin >> password;
	cout << "Выберите роль" << endl;
	cout << "1. Администратор" << endl;
	cout << "2. Судья" << endl;
	cout << "3. Гость" << endl;
	cin >> choice;
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
}
void AdminSystem(const string& username) {
	int choice;
	while (true) {
		showMenu(username);
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(100000000, '\n');
			cout << "Ошибка ввода!" << endl;
			continue;
		}
		switch (choice)
		{
		case 1:
			addUser();
			break;
		case 2:
		{
			string username;
			cout << "Введите имя пользователя, которого вы хотите удалить" << endl;
			cin >> username;
			deleteUser(username);
			break;
		}
			
		case 3:
		{
			ifstream file("Users.txt");
			cout << file.rdbuf();
			file.close();
			break;
		}	
		case 0:
			return;
		default:
			cout << "Ошибка ввода!" << endl;
			break;
		}
	}
}