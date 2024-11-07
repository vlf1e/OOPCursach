#pragma once
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const string lineWrapping(const string str) {
	string output = "", word, line = "",
		newstr = '|' + string(7, ' ') + '|' + string(19, ' ') + '|' + string(17, ' ') + '|' + string(17, ' ') +
		'|' + string(18, ' ') + '|' + string(12, ' ') + "| ";
	stringstream stream(str);
	if (str.size() < 23) {
		line = str + string(21 - str.size(), ' ') + '|';
		return line;
	}
	bool flag = false;
	while (stream >> word) {
		if (line.size() + word.size() < 23) {
			line += word;
		}
		else {
			line += string(20 - line.size(), ' ');
			line += " |\n";
			if (flag) output += newstr;
			flag = true;
			output += line;
			line = word;
		}
	}
	line += string(20 - line.size(), ' ');
	line += " |\n";
	output += newstr;
	output += line;
	return output;
}
