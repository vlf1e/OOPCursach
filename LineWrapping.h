#pragma once
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


void printWithWordWrap(const string& text, size_t width) {
    istringstream words(text);
    string word;
    string line;

    while (words >> word) {
        if (line.size() + word.size() + 1 > width) {
            cout << line << endl; // Выводим текущую строку
            line = word; // Начинаем новую строку
        }
        else {
            if (!line.empty()) {
                line += ' '; // Добавляем пробел перед словом, если строка не пустая
            }
            line += word; // Добавляем слово к текущей строке
        }
    }
    if (!line.empty()) {
        cout << line << endl; // Выводим последнюю строку
    }
}