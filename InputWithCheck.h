#pragma once
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

void WaitButton() {
	cout << "Нажмите любую кнопку, чтобы продолжить...";
	while (true) {
		if (_kbhit()) {
			while (_kbhit()) _getch();
			break;
		}
	}
}

template <typename T>
class Input {
public:
	static void InputWithCheck(T& obj) {
		cin >> obj;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000000, '\n');
			cout << "Ошибка ввода!" << endl;
			WaitButton();
		}
	}
};