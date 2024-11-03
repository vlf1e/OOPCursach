#pragma once
#include <string>
#include <functional>
#include <random>
#include <ctime>
#include <algorithm>
#include <exception>

using namespace std;

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
	User(const string& login, const string& password, const string& type) : 
		login(login), type(type) {
		this->salt = generateRandomString();
		this->password = hashPassword(password, this->salt);
	}
	
	bool checkpassword(string& pass) {
		size_t temp = hashPassword(pass, this->salt);
		return this->password == temp;
	}
};
