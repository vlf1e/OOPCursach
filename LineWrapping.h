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
            cout << line << endl; // ������� ������� ������
            line = word; // �������� ����� ������
        }
        else {
            if (!line.empty()) {
                line += ' '; // ��������� ������ ����� ������, ���� ������ �� ������
            }
            line += word; // ��������� ����� � ������� ������
        }
    }
    if (!line.empty()) {
        cout << line << endl; // ������� ��������� ������
    }
}