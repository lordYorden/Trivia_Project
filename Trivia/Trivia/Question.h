#pragma once
#include <iostream>
class Question
{
private:
	std::string _q;
	std::string correctAns;
	std::string ans2;
	std::string ans3;
	std::string ans4;
public:
	Question(std ::string q, std::string correct, std::string ans2, std::string ans3, std::string ans4) :
		_q(q), correctAns(correct), ans2(ans2), ans3(ans3), ans4(ans4)
	{
	}
	std::string getQuestion()
	{
		return std::string(_q);
	}
	std::string getPossibleAnswers()
	{
		return ans2 + "&" +ans3 + "&" + ans4;
	}
	std::string getCorrectAnswer()
	{
		return correctAns;
	}
	bool operator==(Question const& other) const
	{
		return this->_q == other._q;
	}
};
