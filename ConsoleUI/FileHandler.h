#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
	std::string filePath;
	std::string delimiter = "-";
	FILEHANDLER(std::string filePath) : filePath(filePath)
	{
	}

	FileHandlerResult IsValidFile(std::string filePath)
	{
		std::ifstream fileInput(filePath);
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

	std::vector<std::vector<std::string>> GetTokens(std::string delimiter = "-")
	{
		if (IsValidFile(this->filePath) == Not_Exist)
		{
			throw std::runtime_error("Failed to open this file!");
		}
		else
		{
			std::ifstream fileInput(filePath);
			std::vector<std::vector<std::string>> result;
			std::string line;
			size_t posLine = 0;
			while (!fileInput.eof())
			{
				getline(fileInput, line);
				line += delimiter;
				size_t pos = 0;
				std::vector<std::string> token;
				size_t posToken = 0;
				while ((pos = line.find(delimiter)) != std::string::npos)
				{
					token.push_back(line.substr(0, pos));
					line.erase(0, pos + delimiter.length());
				}
				result.push_back(token);
				posLine++;
			}
			fileInput.close();
			return result;
		}
	}

	std::vector<std::string> GetLinesString()
	{
		if (IsValidFile(this->filePath) == Not_Exist)
		{
			throw std::runtime_error("Failed to open this file!");
		}
		else
		{
			std::ifstream fileInput(filePath);
			std::vector<std::string> result;
			std::string line;
			while (!fileInput.eof())
			{
				getline(fileInput, line);
				result.push_back(line);
			}
			fileInput.close();
			return result;
		}
	}

	int* GetLinesInt()
	{
		if (IsValidFile(this->filePath) == Not_Exist)
		{
			throw std::runtime_error("Failed to open this file!");
		}
		else
		{
			std::ifstream fileInput(filePath);
			int* result = NULL;
			std::string line;
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
	bool WriteToFile(std::string* data, IosMode mode)
	{
		if (IsValidFile(this->filePath) == Not_Exist)
		{
			std::ofstream outfile(filePath);
		}

		// 2. Mở file
		std::ofstream f;
		if(mode == Replace)
			f.open(filePath, std::ios::trunc);
		else
			f.open(filePath, std::ios::app);

		// 3. Ghi dữ liệu vào file, trường hợp này ta có data là dữ liệu
		for (int i = 0; i < SizeOfT(data); i++)
		{
			f << data[i];
		}

		// 4. Đóng file
		f.close();
		return true;
	}
};