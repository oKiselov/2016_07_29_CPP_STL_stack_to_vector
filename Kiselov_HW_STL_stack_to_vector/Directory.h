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
	// ����������� ����������� �������-������ ������ : ������������, ����������� � ��������� ������������ 
	Directory() : listPath(std::list<std::string>()){}
	virtual ~Directory(){}

	Directory & operator=(const Directory&dr)
	{
		*this = dr; 
		return *this; 
	}

	// ����� ����� ���������� � �������� ������ ������ � ����� 
	std::list<string> List_Pathes(const std::string &strPath)
	{
		try
		{
			// ���������� ���������� ������ - ������� ������ ostringstream ��� �������� ���� ������ ����� 
			std::ostringstream os;
			// ������������ ���� ������ � ����� ������ 
			os << strPath << "\\*.*";

			// ���������� ���������, � ������� �������� ���������� � ������ 
			_finddata_t fd = { 0 };
			// ���������� ���������� ��� ������ ������ 
			intptr_t handle = _findfirst(os.str().c_str(), &fd);
			// �������� �� ������ 
			if (handle == -1)
			{
				throw MyException("Error findfirst", errno);
			}

			do
			{
				// � ������ ���������� �����, ��������������� ���������� ��� �� 
				if (string(fd.name) == string(".") || string(fd.name) == string(".."))
					continue;
				// � ������ ���������� ����������		
				if (fd.attrib & _A_SUBDIR)
				{
					// ��������� ������
					std::ostringstream os;
					// ������������ ������ ���� � ������ ����� ���������� 
					os << strPath << "\\" << fd.name;

					try
					{
						// ���� � ����������� ������� 
						List_Pathes(os.str());
					}
					catch (const MyException &ex)
					{
						// ��������� �� ������ ��������� � ������ return �� ��������
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
				// ������ �����, ���� ���� � ���������� ��� ������
			} while (!_findnext(handle, &fd));
			// �������� ������ 
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

	// ����� �������� ����� 
	void RemoveFile(const std::string &strPath)
	{
		int file_remove = remove(strPath.c_str());
		if (file_remove)
			cout << "File " << strPath << " is not deleted" << endl;
		else
			cout << "Delete operation was succesfull" << endl; 
	}

	// ����� ���������� ������ ������ � ���� Current directory.txt
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

