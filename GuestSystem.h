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
	cout << "����� ����������, �����!" << endl;
	cout << "1. ���������� ����� ������������" << endl;
	cout << "0. �����" << endl;
	cout << "��� �����: ";
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
			cout << "�� ��������" << endl;
			cout << "������� ����� ������, ����� ����������" << endl;
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