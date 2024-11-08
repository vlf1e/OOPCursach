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

void ShowGuestMenu() {
	system("cls");
	cout << "Добро пожаловать, Гость!" << endl;
	cout << "1. Посмотреть итоги соревнований" << endl;
	cout << "0. Выход" << endl;
	cout << "Ваш выбор: ";
}
void GuestSystem() {
	int choice;
	while (true) {
		ShowGuestMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			break;
		}
		case 0:
		{
			cout << "До свидания" << endl;
			cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
			while (true) {
				if (_kbhit()) {
					while (_kbhit()) _getch();
					break;
				}
			}
		}
		default:
			break;
		}
	}
	
}