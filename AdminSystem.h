#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <conio.h>
#include "User.h"

using namespace std;

void showMenu(const string& username) {
	system("cls");
	cout << "����� ���������� " << username << '!' << endl;
	cout << "1. �������� ������������" << endl;
	cout << "2. ������� ������������" << endl;
	cout << "3. ���������� ������������� � �� ������" << endl;
	cout << "0. �����" << endl;
}
void addUser() {
	system("cls");
	ofstream file("Users.txt", ios::app);
	string login, password, type;
	int choice;
	cout << "������� �����: ";
	cin >> login;
	cout << "������� ������: ";
	cin >> password;
	cout << "�������� ����" << endl;
	cout << "1. �������������" << endl;
	cout << "2. �����" << endl;
	cout << "3. �����" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		type = "�������������";
		break;
	}
	case 2:
	{
		type = "�����";
		break;
	}
	case 3:
	{
		type = "�����";
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
	cout << "�������� �������!" << endl;
	cout << "������� ����� ������, ����� ����������" << endl;
	while (true) {
		if (_kbhit()) {
			while (_kbhit()) _getch();
			break;
		}
	}
}
void viewUsers() {
	system("cls");
	ifstream file("Users.txt");
	vector<unique_ptr<User>> users;
	User user;
	while (file >> user) {
		users.push_back(make_unique<User>(user));
	}
	cout << "| " << setw(20) << left << "�����"
		<< " | " << setw(20) << left << "����" << " |" << endl;
	cout << string(47, '-') << endl;
	for (const auto& usr : users) {
		cout << "| " << setw(20) << usr->getLogin() 
			<< " | " << setw(20) << usr->getType() << " |" << endl;
		cout << string(47, '-') << endl;
	}
	cout << "������� ����� ������, ����� ����������" << endl;
	while (true) {
		if (_kbhit()) {
			while (_kbhit()) _getch();
			break;
		}
	}
	file.close();
}
void AdminSystem(const string& username) {
	int choice;
	while (true) {
		showMenu(username);
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(100000000, '\n');
			cout << "������ �����!" << endl;
			continue;
		}
		switch (choice)
		{
		case 1:
			addUser();
			break;
		case 2:
		{
			system("cls");
			string username;
			cout << "������� ��� ������������, �������� �� ������ �������" << endl;
			cin >> username;
			deleteUser(username);
			break;
		}
			
		case 3:
		{
			viewUsers();
			break;
		}	
		case 0:
			return;
		default:
			cout << "������ �����!" << endl;
			break;
		}
	}
}