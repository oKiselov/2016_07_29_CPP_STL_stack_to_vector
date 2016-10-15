#include <iostream>
#include <string>
#include <stack>
#include <list>
#include "MyStack.h"
#include "Directory.h"

using std::cout; 
using std::cin; 
using std::endl; 
using std::string; 
using std::list; 
using std::stack; 


int main()
{
	try
	{
		cout << "Exercise 1" << endl << endl;

		// Создание и наполнение стека значениями 
		MyStack<string> mStack;
		mStack.push("Pirate");
		mStack.push("Bay");
		mStack.push("Coast");

		// Копирование стека 
		MyStack<string> mStackCopy;
		mStackCopy = mStack;
		//Провека на пустоту 
		if (!mStackCopy.empty())
			cout << "mStackCopy isn't empty!" << endl;

		// Метод удаления стека 
		mStack.Clear();
		if (mStack.empty())
			cout << "mStack is empty!" << endl;
		//Создание и передача в вектор 
		std::vector<string> mVctr;
		mVctr = mStackCopy.To_Vector();

		cout << "Here is the vector contains all elements from mStackCopy: ";
		for (auto cit = mVctr.cbegin(); cit != mVctr.cend(); ++cit)
			cout << *cit << " ";
		cout << endl;

		cout << endl << endl << "Exercise 2" << endl << endl;

		//Получение адреса к текстовому файлу и помещение его в объект строки  
		cout << "Enter the path to text file (example: \"F:\") : ";
		string strGlobePath;
		getline(cin, strGlobePath);

		// Создание объекта класса Директори и передача в список всех файлов и папок 
		Directory myDir;
		list<string> listPathes(myDir.List_Pathes(strGlobePath));

		// Вывод на экран содержимого списка 
		for (auto cit = listPathes.cbegin(); cit != listPathes.cend(); ++cit)
			cout << *cit << " ";
		cout << endl;

		// Метод сохранения в файл списка 
		myDir.Save_to_File(listPathes);

		// Удаление файла 
		cout << "Choose file for deleting: "; 
		string strForDel; 
		std::getline(cin, strForDel); 
		myDir.RemoveFile(strForDel); 

		cout << "Done!" << endl;
	}
	catch (const char *msg)
	{
		cout << msg << endl;
	}
	catch (const exception &ex)
	{
		cout << ex.what() << endl;
	}
	catch (...)
	{
		cout << "Unhandled exception" << endl;
	}
	return 0;
}