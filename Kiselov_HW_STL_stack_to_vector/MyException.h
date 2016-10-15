#pragma once

#include <iostream>
#include <exception>
#include <string>
#include <memory>

using std::cout;
using std::endl; 
using std::exception;
using std::string;

// ����� ��� ����������� ������ �� ����� ������ ������ 
class MyException : public exception
{
	int identEx;
public:
	MyException(const string &s, const int &i = 0) : exception(s.c_str()), identEx(i){}

	friend std::ostream & operator << (std::ostream &os, const MyException &ex)
	{
		return os << ex.what() << ", " << ex.identEx;
	}
};