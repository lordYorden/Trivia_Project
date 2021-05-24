#pragma once
#include <iostream>
class Question
{
private:
	char* _q;
	char* correctAns;
	char* ans2;
	char* ans3;
	char* ans4;
public:
	Question(char* q, char* correct, char* ans2, char*, char* ans4) :
		_q(q), correctAns(correct), ans2(ans2), ans3(ans3), ans4(ans4)
	{
	}
};
