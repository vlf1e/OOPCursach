#include "JudgeSystem.h"
#include "AdminSystem.h"
#include "User.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <string>

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	//AdminSystem("loh");
	vector<unique_ptr<User>> users;
	User user;
	ifstream file("Users.txt");
	while (file >> user) {
		users.push_back(make_unique<User>(user));
	}
	while (true) {
		system("cls");
		string login, password;
		cout << "Введите логин" << endl;
		cin >> login;
		if (login != "Guest") {
			bool found = 0;
			for (const auto& usr : users) {
				if (usr->getLogin() == login) {
					found = 1;
					while (true) {
						cout << "Введите пароль: " << endl;
						cin >> password;
						if (usr->checkpassword(password)) {
							if (usr->getType() == "Администратор") {
								AdminSystem(usr->getLogin());
								break;
							}
							else if (usr->getType() == "Судья") {
								JudgeSystem(usr->getLogin());
								break;
							}
							else return 0;
						}
						else cout << "Неверный пароль!" << endl;
					}
				}
			}
			if(!found) cout << "Неверный логин!" << endl;
		}
		else if (login == "Guest" || login == "guest") {
			//guestMenu()
		}
	}
	return 0;
}