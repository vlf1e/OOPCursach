#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Participant.h"

using namespace std;

void ShowMenu() {
	cout << "1. Добавить соревнование" << endl;
	cout << "2. Зарегестрировать участника" << endl;
	cout << "3. Посмотреть итоги соревнований" << endl;
	cout << "4. Вывести итоги соревнования в файл" << endl;
	cout << "0. Выход" << endl;
}