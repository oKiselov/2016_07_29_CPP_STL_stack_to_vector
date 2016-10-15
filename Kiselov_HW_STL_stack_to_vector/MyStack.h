#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <vector>

template<typename T>
class MyStack:public std::stack<T>
{
public:
	// ����������� ����������� �������-������ ������ : ������������, ����������� � ��������� ������������ 
	MyStack() :std::stack<T>(){}
	virtual ~MyStack(){}

	T&operator=(const T&mS)
	{
		*this = mS;
		return *this;
	}

	// ����� ������� ����� 
	void Clear()
	{
		while (!this->empty())
		{
			this->pop(); 
		}
	}

	// ����� �������� ����� � ������ 
	std::vector<T> To_Vector()
	{
		MyStack tempStack; 
		tempStack = *this; 
		std::vector<T> tempVector; 
		while (!tempStack.empty())
		{
			tempVector.push_back(tempStack.top()); 
			tempStack.pop(); 
		}
		return tempVector; 
	}
};

