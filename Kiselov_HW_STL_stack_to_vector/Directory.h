#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <io.h>
#include "MyException.h"

class Directory
{
	std::list<std::string> listPath; 
public:
	// Определение специальный функций-членов класса : Конструктора, деструктора и оператора присваивания 
	Directory() : listPath(std::list<std::string>()){}
	virtual ~Directory(){}

	Directory & operator=(const Directory&dr)
	{
		*this = dr; 
		return *this; 
	}

	// Метод обход директории и возврата списка файлов и папок 
	std::list<string> List_Pathes(const std::string &strPath)
	{
		try
		{
			// Обяъвление строкового потока - объекта класса ostringstream для указания пути поиска файла 
			std::ostringstream os;
			// формирование пути поиска и маски поиска 
			os << strPath << "\\*.*";

			// объявление структуры, в которой хранится информация о файлах 
			_finddata_t fd = { 0 };
			// Объявление переменной для поиска файлов 
			intptr_t handle = _findfirst(os.str().c_str(), &fd);
			// Проверка на ошибки 
			if (handle == -1)
			{
				throw MyException("Error findfirst", errno);
			}

			do
			{
				// В случае нахождения папок, символизирующих подкаталог для ОС 
				if (string(fd.name) == string(".") || string(fd.name) == string(".."))
					continue;
				// в случае нахождения директории		
				if (fd.attrib & _A_SUBDIR)
				{
					// Обнуление потока
					std::ostringstream os;
					// формирование нового пути с учетом имени директории 
					os << strPath << "\\" << fd.name;

					try
					{
						// Вход в рекурсивную функцию 
						List_Pathes(os.str());
					}
					catch (const MyException &ex)
					{
						// Страховка от вылета программы к строке return из рекурсии
						std::cout << ex << std::endl;
					}
				}
				else
				{
					string str_to_list(strPath);
					str_to_list += "\\\\";
					str_to_list += fd.name;
					str_to_list += "\r\n";
					this->listPath.push_back(str_to_list);
				}
				// работа цикла, пока есть в директории что искать
			} while (!_findnext(handle, &fd));
			// Закрытие поиска 
			_findclose(handle);

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
		return this->listPath;
	}

	// Метод удаления файла 
	void RemoveFile(const std::string &strPath)
	{
		int file_remove = remove(strPath.c_str());
		if (file_remove)
			cout << "File " << strPath << " is not deleted" << endl;
		else
			cout << "Delete operation was succesfull" << endl; 
	}

	// Метод сохранения списка файлов в файл Current directory.txt
	void Save_to_File(std::list<std::string>&list_of_Pathes)
	{
		try 
		{
			std::list<std::string> list_copy(list_of_Pathes); 
			std::ofstream ofs("Current directory.txt");
			if (!ofs.is_open())
				throw "Error open file for writing";
			while (!list_of_Pathes.empty())
			{
				ofs.write(&list_of_Pathes.front()[0], list_of_Pathes.front().length()); 
				list_of_Pathes.pop_front(); 
			}		
			ofs.close(); 
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
		return;
	}
};

