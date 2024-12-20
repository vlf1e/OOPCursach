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
	cout << "����� ����������, " << username << '!' << endl;
	cout << "1. �������� ������������" << endl;
	cout << "2. ������� ������������" << endl;
	cout << "3. �������� ������������" << endl;
	cout << "4. ���������� ������������� � �� ������" << endl;
	cout << "0. �����" << endl;
}

void addUser() {
	try {
		system("cls");
		ofstream file("Users.txt", ios::app);
		string login, password, type;
		char ch;
		int choice;
		cout << "������� �����: ";
		if (!Input<string>::InputWithCheck(login)) return;
		cout << "������� ������: ";
		while ((ch = _getch()) != '\r') {
			password.push_back(ch);
			cout << '*';
		}
		cout << endl;
		cout << "�������� ����" << endl;
		cout << "1. �������������" << endl;
		cout << "2. �����" << endl;
		if (!Input<int>::InputWithCheck(choice)) return;
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
		default:
			break;
		}
		if (file) {
			User user(login, password, type);
			file << user << endl;
		}
		file.close();
	}
	catch (UserException& e) {
		cout << e.what() << endl;
		WaitButton();
		return;
	}
}

void deleteUser(const string& username) {
	ifstream file1("Users.txt");
	vector<unique_ptr<User>> users;
	User user;
	bool find = false;
	while (file1 >> user) {
		users.push_back(make_unique<User>(user));
	}
	file1.close();
	ofstream file2("Users.txt");
	for (const auto& usr : users) {
		if (usr->getLogin() == username) { find = true; break; }
	}
	if (!find) {
		cout << "������������ � ����� ������ �� ������!" << endl;
		WaitButton();
		return;
	}
	for (const auto& usr : users) {
		if (usr->getLogin() == username) continue;
		file2 << *usr << endl;
	}
	cout << "�������� �������!" << endl;
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
	cout << "| " << setw(20) << left << "�����"
		<< " | " << setw(20) << left << "����" << " |" << endl;
	cout << string(47, '-') << endl;
	for (const auto& usr : users) {
		cout << "| " << setw(20) << usr->getLogin()
			<< " | " << setw(20) << usr->getType() << " |" << endl;
		cout << string(47, '-') << endl;
	}
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
	cout << "| " << setw(20) << left << "�����"
		<< " | " << setw(20) << left << "����" << " |" << endl;
	cout << string(47, '-') << endl;
	for (const auto& usr : users) {
		if (usr->getType() == "�������������") {
			cout << "| " << setw(20) << usr->getLogin()
				<< " | " << setw(20) << usr->getType() << " |" << endl;
			cout << string(47, '-') << endl;
		}
	}
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
	cout << "| " << setw(20) << left << "�����"
		<< " | " << setw(20) << left << "����" << " |" << endl;
	cout << string(47, '-') << endl;
	for (const auto& usr : users) {
		if (usr->getType() == "�����") {
			cout << "| " << setw(20) << usr->getLogin()
				<< " | " << setw(20) << usr->getType() << " |" << endl;
			cout << string(47, '-') << endl;
		}
	}
	file.close();
}

void view() {
	system("cls");
	int choice;
	cout << "1. ������� ����" << endl;
	cout << "2. ������� ���������������" << endl;
	cout << "3. ������� �����" << endl;
	cout << "0. ��������� �����" << endl;
	while (true) {
		if (!Input<int>::InputWithCheck(choice)) return;
		switch (choice)
		{
		case 1:
			viewUsers();
			WaitButton();
			return;
		case 2:
			viewAdmins();
			WaitButton();
			return;
		case 3:
			viewJudges();
			WaitButton();
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
	cout << "������� ��� ������������, �������� �� ������ ��������" << endl;
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
			cout << "������� ��� ������������" << endl;
			if (!Input<string>::InputWithCheck(login)) return;
			usr->setLogin(login);
			cout << "������� ����� ������" << endl;
			if (!Input<string>::InputWithCheck(password)) return;
			usr->setPassword(password);
			cout << "�������� ��� ������� ������?" << endl;
			cout << "1. ��" << endl;
			cout << "2. ���" << endl;
			int choice2;
			while (true) {
				if (!Input<int>::InputWithCheck(choice2)) return;
				if (choice2 == 2) {
					int choice3;
					while (true) {
						cout << "�������� ����" << endl;
						cout << "1. �������������" << endl;
						cout << "2. " << endl;
						cout << "��� �����: ";
						if (!Input<int>::InputWithCheck(choice3)) return;
						switch (choice3)
						{
						case 1: user.setType("�������������"); break;
						case 2: user.setType("�����"); break;
						default: cout << "������ �����! ���������� ��� ���!" << endl; break;
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
		if (!Input<int>::InputWithCheck(choice)) AdminSystem(username);
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
			cout << "������� ��� ������������, �������� �� ������ �������" << endl;
			if (!Input<string>::InputWithCheck(username)) AdminSystem(username);
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
			cout << "�� ��������, " << username << endl;
			WaitButton();
			return;
		default:
			cout << "������ �����!" << endl;
			WaitButton();
			break;
		}
	}
}
