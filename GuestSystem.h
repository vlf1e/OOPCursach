#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
#include "InputWithCheck.h"

using namespace std;

void ShowGuestMenu() {
	system("cls");
	cout << "����� ����������, �����!" << endl;
	cout << "1. ���������� ����� ������������" << endl;
	cout << "0. �����" << endl;
	cout << "��� �����: ";
}
void viewCompetitions() {
	system("cls");
	string name,filename_and_path;
	ifstream temp("temp\\competitions_names.txt");
	cout << "| " << setw(20) << left << "��� ������������" << " |" << endl;
	cout << string(24, '-') << endl;
	while (temp >> name) {
		cout << "| " << setw(20) << left << name << " |" << endl;
		cout << string(24, '-') << endl;
	}
	temp.close();
	cout << "������� ��� ������������, ������� ���������� �������" << endl;
	if (!Input<string>::InputWithCheck(name)) return;
	system("cls");
	filename_and_path = "������\\����� ������������ " + name + ".txt";
	ifstream file(filename_and_path);
	if (!file) cout << "������ ������ �����!" << endl;
	cout << file.rdbuf();
	WaitButton();
	return;

}
void GuestSystem() {
	int choice;
	while (true) {
		ShowGuestMenu();
		if (!Input<int>::InputWithCheck(choice)) GuestSystem;
		switch (choice)
		{
		case 1:
		{
			viewCompetitions();
			break;
		}
		case 0:
		{
			system("cls");
			cout << "�� ��������" << endl;
			cout << "������� ����� ������, ����� ����������" << endl;
			while (true) {
				if (_kbhit()) {
					while (_kbhit()) _getch();
					break;
				}
			}
			return;
		}
		default:
			break;
		}
	}
	
}