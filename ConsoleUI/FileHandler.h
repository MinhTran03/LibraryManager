#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

enum FileHandlerResult
{
	Exist,
	Not_Exist,
	Empty,
};
enum IosMode
{
	Replace,
	WriteNext,
};

struct FILEHANDLER
{
	string filePath;
	string delimiter = "-";
	FILEHANDLER(string filePath) : filePath(filePath)
	{
	}

	FileHandlerResult IsValidFile(string filePath)
	{
		ifstream fileInput(filePath);
		if (fileInput.fail())
		{
			fileInput.close();
			return FileHandlerResult::Not_Exist;
		}
		else
		{
			bool fileEmpty = false;
			char temp;
			fileInput >> temp;
			if (temp == -52) fileEmpty = true;
			fileInput.close();
			if (fileEmpty)
			{
				return FileHandlerResult::Empty;
			}
			else
			{
				return FileHandlerResult::Exist;
			}
		}
	}

	string** GetTokens(int& count, string delimiter = "-")
	{
		if (IsValidFile(this->filePath) == Not_Exist)
		{
			string temp = this->filePath;
			temp.erase(temp.begin(), temp.begin() + temp.find_last_of('\\') + 1);
			throw runtime_error("Failed to open " + temp + "!!!");
		}
		else
		{
			ifstream fileInput(filePath);
			string** result = NULL;
			string line;
			size_t posLine = 0;
			while (!fileInput.eof())
			{
				getline(fileInput, line);
				line += delimiter;
				size_t pos = 0;
				string* token = NULL;
				size_t posToken = 0;
				int count2 = 0;
				while ((pos = line.find(delimiter)) != string::npos)
				{
					//token.push_back(line.substr(0, pos));
					PushBack(token, line.substr(0, pos), count2);
					line.erase(0, pos + delimiter.length());
				}
				//result.push_back(token);
				PushBack(result, token, count);
				posLine++;
			}
			fileInput.close();
			return result;
		}
	}

	string* GetLinesString()
	{
		if (IsValidFile(this->filePath) == Not_Exist)
		{
			throw runtime_error("Failed to open this file!");
		}
		else
		{
			ifstream fileInput(filePath);
			string* result = NULL;
			string line;
			int count = 0;
			while (!fileInput.eof())
			{
				getline(fileInput, line);
				PushBack(result, line, count);
			}
			fileInput.close();
			return result;
		}
	}

	int* GetLinesInt()
	{
		if (IsValidFile(this->filePath) == Not_Exist)
		{
			throw runtime_error("Failed to open this file!");
		}
		else
		{
			ifstream fileInput(filePath);
			int* result = NULL;
			string line;
			int count = 0;
			while (!fileInput.eof())
			{
				getline(fileInput, line);
				auto tem = stoi(line);
				PushBack(result, tem, count);
			}
			fileInput.close();
			return result;
		}
	}

	// mode = ios::
	bool WriteToFile(string* data, IosMode mode, int totalLine)
	{
		if (IsValidFile(this->filePath) == Not_Exist)
		{
			ofstream outfile(filePath);
		}

		// 2. Mở file
		ofstream f;
		if(mode == Replace)
			f.open(filePath, ios::trunc);
		else
			f.open(filePath, ios::app);

		// 3. Ghi dữ liệu vào file, trường hợp này ta có data là dữ liệu
		for (int i = 0; i < totalLine; i++)
		{
			f << data[i];
		}

		// 4. Đóng file
		f.close();
		return true;
	}
};