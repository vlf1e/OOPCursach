#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <conio.h>
#include <iomanip>
#include "Competition.h"
#include "Result.h"
#include "Time.h"
#include "InputWithCheck.h"

using namespace std;

void ShowMenu(const string& username) {
    system("cls");
    cout << "Добро пожаловать, " << username << '!' << endl;
    cout << "1. Добавить соревнование" << endl;
    cout << "2. Зарегистрировать результат" << endl;
    cout << "3. Вывод результатов" << endl;
    cout << "4. Создание отчета" << endl;
    cout << "0. Выход" << endl;
    cout << "Ваш выбор: ";
}

void addCompetition(vector<shared_ptr<Competition>>& competitions) {
    string name;
    system("cls");
    cout << "Введите имя соревнования: ";
    cin >> name;
    Input<string>::InputWithCheck(name);
    int type;
    cout << "Выберите тип результата:" << endl;
    cout << "1. Время" << endl;
    cout << "2. Очки" << endl;
    cout << "3. Текст" << endl;
    Input<int>::InputWithCheck(type);
    shared_ptr<Competition> competition;
    switch (type) {
    case 1:
        competition = make_shared<TimeCompetition>(name);
        break;
    case 2:
        competition = make_shared<ScoreCompetition>(name);
        break;
    case 3:
        competition = make_shared<TextCompetition>(name);
        break;
    default:
        cout << "Ошибка ввода! Попробуйте ещё раз!" << endl;
        return;
    }
    competitions.push_back(competition);
    WaitButton();
}

void addResult(vector<shared_ptr<Competition>>& competitions) {
    system("cls");
    cout << "| " << setw(30) << left << "Имя соревнования" << " |" << endl;
    cout << string(34, '-') << endl;
    for (const auto& competition : competitions) {
        cout << "| " << setw(30) << left << competition->getName() << " |" << endl;
        cout << string(34, '-') << endl;
    }
    string name;
    cout << "Введите имя соревнования: ";
    Input<string>::InputWithCheck(name);
    auto competitionIt = find_if(competitions.begin(), competitions.end(),
        [&name](const shared_ptr<Competition>& comp) { return comp->getName() == name; });
    if (competitionIt == competitions.end()) {
        cout << "Соревнование не найдено!" << endl;
        WaitButton();
        return;
    }

    string secondName, firstName, surname, country;
    int age;
    cout << "Введите фамилию: ";
    Input<string>::InputWithCheck(secondName);
    cout << "Введите имя: ";
    Input<string>::InputWithCheck(firstName);
    cout << "Введите отчество: ";
    Input<string>::InputWithCheck(surname);
    cout << "Введите страну: ";
    Input<string>::InputWithCheck(country);
    cout << "Введите возраст: ";
    Input<int>::InputWithCheck(age);

    Participant participant(secondName, firstName, surname, country, age);
    if (typeid(**competitionIt) == typeid(TimeCompetition)) {
        cout << "Введите время (Пример: минуты:секунды:миллисекунды): ";
        Time time;
        try {
            cin >> time;
            auto result = make_shared<TimeResult>(participant, time);
            (*competitionIt)->addParticipant(result);
        }
        catch (const TimeException& e) {
            cerr << e.what() << endl;
            WaitButton();
            return;
        }
    }
    else if (typeid(**competitionIt) == typeid(ScoreCompetition)) {
        cout << "Введите очки: ";
        double score;
        Input<double>::InputWithCheck(score);
        auto result = make_shared<ScoreResult>(participant, score);
        (*competitionIt)->addParticipant(result);
    }
    else if (typeid(**competitionIt) == typeid(TextCompetition)) {
        cout << "Введите оценку: ";
        string text;
        cin.ignore();
        getline(cin, text);
        auto result = make_shared<TextResult>(participant, text);
        (*competitionIt)->addParticipant(result);
    }

    cout << "Результат добавлен!" << endl;
    WaitButton();
}

void displayAll(const vector<shared_ptr<Competition>>& competitions) {
    system("cls");
    for (const auto& comp : competitions) {
        if (typeid(*comp) != typeid(TextCompetition))
            comp->sortParticipantsByScore();

        cout << "Соревнование: " << comp->getName() << endl;
        cout << string(120, '-') << endl;
        cout << "| " << setw(5) << left << "Место"
            << " | " << setw(17) << left << "Фамилия"
            << " | " << setw(15) << left << "Имя"
            << " | " << setw(15) << left << "Отчество"
            << " | " << setw(16) << left << "Страна"
            << " | " << setw(10) << left << "Возраст"
            << " | " << setw(20) << left << "Результат"
            << " |" << endl;
        cout << string(120, '-') << endl;
        comp->display();
    }
    WaitButton();
}

void displayByName(const vector<shared_ptr<Competition>>& competitions) {
    system("cls");
    cout << "| " << setw(30) << left << "Имя соревнования" << " |" << endl;
    cout << string(34, '-') << endl;
    for (const auto& competition : competitions) {
        cout << "| " << setw(30) << left << competition->getName() << " |" << endl;
        cout << string(34, '-') << endl;
    }
    string name;
    cout << "Введите имя соревнования, которое необходимо вывести: ";
    Input<string>::InputWithCheck(name);
    for (const auto& comp : competitions) {
        if (comp->getName() == name) {
            if (typeid(*comp) != typeid(TextCompetition)) comp->sortParticipantsByScore();
            cout << "Соревнвание: " << name << endl;
            cout << string(120, '-');
            cout << "| " << setw(5) << left << "Место"
                << " | " << setw(17) << left << "Фамилия"
                << " | " << setw(15) << left << "Имя"
                << " | " << setw(15) << left << "Отчество"
                << " | " << setw(16) << left << "Страна"
                << " | " << setw(10) << left << "Возраст"
                << " | " << setw(20) << left << "Результат"
                << " |" << endl;
            cout << string(120, '-');
            comp->display();
            WaitButton();
            return;
        }
        cout << "Ошибка ввода!" << endl;
        cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
        while (true) {
            if (_kbhit()) {
                while (_kbhit()) _getch();
                break;
            }
        }
    }
}

void displayTimeComp(const vector<shared_ptr<Competition>>& competitions) {
    system("cls");
    for (const auto& comp : competitions) {
        if (typeid(*comp) == typeid(TimeCompetition)) {
            comp->sortParticipantsByScore();
            cout << "Соревнование: " << comp->getName() << endl;
            cout << string(120, '-');
            cout << "| " << setw(5) << left << "Место"
                << " | " << setw(17) << left << "Фамилия"
                << " | " << setw(15) << left << "Имя"
                << " | " << setw(15) << left << "Отчество"
                << " | " << setw(16) << left << "Страна"
                << " | " << setw(10) << left << "Возраст"
                << " | " << setw(20) << left << "Результат"
                << " |" << endl;
            cout << string(120, '-');
            comp->display();
        }
    }
    WaitButton();
}

void displayScoreComp(vector<shared_ptr<Competition>>& competitions) {
    system("cls");
    for (const auto& comp : competitions) {
        if (typeid(*comp) == typeid(ScoreCompetition)) {
            comp->sortParticipantsByScore();
            cout << "Соревнование: " << comp->getName() << endl;
            cout << string(120, '-');
            cout << "| " << setw(5) << left << "Место"
                << " | " << setw(17) << left << "Фамилия"
                << " | " << setw(15) << left << "Имя"
                << " | " << setw(15) << left << "Отчество"
                << " | " << setw(16) << left << "Страна"
                << " | " << setw(10) << left << "Возраст"
                << " | " << setw(20) << left << "Результат"
                << " |" << endl;
            cout << string(120, '-');
            comp->display();
        }
    }
    WaitButton();
}

void displayTextComp(vector<shared_ptr<Competition>>& competitions) {
    system("cls");
    for (const auto& comp : competitions) {
        if (typeid(*comp) == typeid(TextCompetition)) {
            comp->sortParticipantsByScore();
            cout << "Соревнование: " << comp->getName() << endl;
            cout << string(120, '-');
            cout << "| " << setw(5) << left << "Место"
                << " | " << setw(17) << left << "Фамилия"
                << " | " << setw(15) << left << "Имя"
                << " | " << setw(15) << left << "Отчество"
                << " | " << setw(16) << left << "Страна"
                << " | " << setw(10) << left << "Возраст"
                << " | " << setw(20) << left << "Результат"
                << " |" << endl;
            cout << string(120, '-');
            comp->display();
        }
    }
    WaitButton();
}

void display(vector<shared_ptr<Competition>>& competitions) {
    system("cls");
    int choice;
    cout << "Что вывести?" << endl;
    cout << "1. Вывести всё" << endl;
    cout << "2. Вывести конкретное соревнование" << endl;
    cout << "3. Вывести все соревноавния с типом оценивания \"Время\"" << endl;
    cout << "4. Вывести все соревноавния с типом оценивания \"Очки\"" << endl;
    cout << "5. Вывести все соревноавния с типом оценивания \"Текст\"" << endl;
    cout << "0. Вернутся назад" << endl;
    cout << "Ваш выбор: " << endl;
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            cout << "Ошибка ввода! Попробуйте ещё раз!" << endl;
            cin.clear();
            cin.ignore(1000000, '\n');
            continue;
        }
        switch (choice)
        {
        case 1:
            displayAll(competitions);
            return;
        case 2:
            displayByName(competitions);
            return;
        case 3:
            displayTimeComp(competitions);
            return;
        case 4:
            displayScoreComp(competitions);
            return;
        case 5:
            displayTextComp(competitions);
            return;
        case 0:
            return;
        default:
            break;
        }
    }
}

void makeReport(vector<shared_ptr<Competition>>& competitions) {
    system("cls");
    cout << "| " << setw(30) << left << "Имя соревнования" << " |" << endl;
    cout << string(34, '-') << endl;
    for (const auto& competition : competitions) {
        cout << "| " << setw(30) << left << competition->getName() << " |" << endl;
        cout << string(34, '-') << endl;
    }
    string name;
    cout << "Введите имя соревнования, для которого необходимо составить отчёт: ";
    cin >> name;
    if (cin.fail()) {
        cout << "Ошибка ввода!" << endl;
        cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
        while (true) {
            if (_kbhit()) {
                while (_kbhit()) _getch();
                break;
            }
        }
        cin.clear();
        return;
    }
    string filename_and_path = "Отчёты\\Отчёт соревнования " + name + ".txt";
    ofstream file(filename_and_path);
    for (const auto& comp : competitions) {
        int i = 1;
        if (comp->getName() == name) {
            if (typeid(*comp) != typeid(TextCompetition)) comp->sortParticipantsByScore();
            file << "Соревнование: " << name << endl;
            file << string(120, '-') << endl;
            file << "| " << setw(5) << left << "Место"
                << " | " << setw(17) << left << "Фамилия"
                << " | " << setw(15) << left << "Имя"
                << " | " << setw(15) << left << "Отчество"
                << " | " << setw(16) << left << "Страна"
                << " | " << setw(10) << left << "Возраст"
                << " | " << setw(20) << left << "Результат"
                << " |" << endl;
            file << string(120, '-') << endl;
            comp->outputToFile(file);
            file.close();
            ifstream tempIn("temp\competitions_names.txt");
            string temp;
            while (tempIn >> temp) {
                if (temp == name) {
                    cout << "Ошибка ввода!" << endl;
                    cout << "Нажмите любую кнопку, чтобы продолжить" << endl;
                    while (true) {
                        if (_kbhit()) {
                            while (_kbhit()) _getch();
                            break;
                        }
                    }
                    tempIn.close();
                    return;
                }
            }
            ofstream tempOut("temp\competitions_names.txt", ios::app);
            tempOut << name << endl;
            tempOut.close();
            cout << "Отчёт создан!" << endl;
            WaitButton();
            return;
        }
    }
}

void JudgeSystem(const string& username) {
    vector<shared_ptr<Competition>> competitions;
    while (true) {
        ShowMenu(username);
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000000, '\n');
            cout << "Ошибка ввода!" << endl;
            continue;
        }
        switch (choice) {
        case 1:
            addCompetition(competitions);
            break;
        case 2:
            addResult(competitions);
            break;
        case 3:
            displayAll(competitions);
            break;
        case 4:
            makeReport(competitions);
            break;
        case 0:
            system("cls");
            cout << "До свидания, " << username << "!" << endl;
            WaitButton();
            return;
        default:
            cout << "Неверный выбор!" << endl;
            break;
        }
    }
}