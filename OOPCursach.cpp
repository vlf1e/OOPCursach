#include "JudgeSystem.h"
#include "LineWrapping.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	JudgeSystem();
	//cout << lineWrapping("qqqqqqqqqqqqqqqqq qqqqqqqqqqqqqqqqqq");
	cout << '|' << string(24, ' ') << '|' << string(17, ' ') << '|' << string(20, ' ') << '|'
		<< string(18, ' ') << '|' << string(12, ' ') << '|' << string(22, ' ') << '|';
	return 0;
}
/*
1
qq
3
2
qq
qq
qq
qq
qq
11
qqqqqqqqqqqqqq qqqqqqqqqqqqqq qqqqqqqqqqqqq
3
*/