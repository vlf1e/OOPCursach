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
	cout << "Добро пожаловать, Гость!" << endl;
	cout << "1. Посмотреть итоги соревнований" << endl;
	cout << "0. Выход" << endl;
	cout << "Ваш выбор: ";
}
void viewCompetitions() {
	system("cls");
	string name,filename_and_path;
	ifstream temp("temp\\competitions_names.txt");
	cout << "| " << setw(20) << left << "Имя соревнования" << " |" << endl;
	cout << string(24, '-') << endl;
	while (temp >> name) {
		cout << "| " << setw(20) << left << name << " |" << endl;
		cout << string(24, '-') << endl;
	}
	temp.close();
	cout << "Введите имя соревнования, которое необходимо вывести" << endl;
	if (!Input<string>::InputWithCheck(name)) return;
	system("cls");
	filename_and_path = "Отчёты\\Отчёт соревнования " + name + ".txt";
	ifstream file(filename_and_path);
	if (!file) cout << "Ошибка чтения файла!" << endl;
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
			cout << "До свидания" << endl;
			cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
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