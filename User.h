#pragma once
#include <string>
#include <fstream>
#include <functional>
#include <random>
#include <ctime>
#include <algorithm>
#include <exception>

using namespace std;

class UserException : exception {
	string msg;
public:
	UserException(const string& msg) : msg(msg) {};
	virtual const char* what() const noexcept override {
		return msg.c_str();
	}
};

class User {
	string login, type, salt;
	size_t password;
	const string generateRandomString() {
		const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		srand(static_cast<unsigned>(time(nullptr)));
		size_t size = rand() % 20 + 1;
		random_device rd;
		mt19937 generator(rd());
		uniform_int_distribution<> distribution(0, characters.size() - 1);
		string random_string(size, 0);
		generate(random_string.begin(), random_string.end(), [&]() {
			return characters[distribution(generator)];
			});
		return random_string;
	}
	size_t hashPassword(const string& password, const string& salt) {
		string passWithSalt = password + salt;
		hash<string> hash_f;
		size_t hashPass = hash_f(passWithSalt);
		return hashPass;
	}
public:
	User() = default;
	User(const string& login, const string& password, const string& type) : 
		login(login), type(type) {
		if (password.size() < 8) throw UserException("ֿאנמכü המכזום סמסעמÿעü טח במכוו קול 8 סטלגמכמג!");
		this->salt = generateRandomString();
		this->password = hashPassword(password, this->salt);
	}
	bool checkpassword(string& pass) {
		size_t temp = hashPassword(pass, this->salt);
		return this->password == temp;
	}
	const string getLogin() { return login; }
	const string getType() { return type; }
	void setLogin(const string& newLogin) { login = newLogin; }
	void setType(const string& newType) { type = newType; }
	void setPassword(const string& newPassword) {
		salt = generateRandomString();
		password = hashPassword(newPassword, salt);
	}
	friend ifstream& operator>>(ifstream& i, User& u) {
		i >> u.login >> u.password >> u.salt >> u.type;
		return i;
	}
	friend ofstream& operator<<(ofstream& o, const User& u) {
		o << u.login << ' ' << u.password << ' ' << u.salt << ' ' << u.type;
		return o;
	}
};
