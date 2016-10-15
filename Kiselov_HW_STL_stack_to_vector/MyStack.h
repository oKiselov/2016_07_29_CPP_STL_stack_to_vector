#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <vector>

template<typename T>
class MyStack:public std::stack<T>
{
public:
	// Определение специальный функций-членов класса : Конструктора, деструктора и оператора присваивания 
	MyStack() :std::stack<T>(){}
	virtual ~MyStack(){}

	T&operator=(const T&mS)
	{
		*this = mS;
		return *this;
	}

	// Метод очистки стека 
	void Clear()
	{
		while (!this->empty())
		{
			this->pop(); 
		}
	}

	// Метод передачи стека в вектор 
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

