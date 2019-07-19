#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Enums.h"

// count các từ có trong word phân cách bằng separator(mặc định là whitespace)
int WordCount(char* word, const char* separator = " ");
// in char* ra màn hình
void WriteLine(char* word);
// split word phân cách bằng separator(mặc định là whitespace) vào arrTokens
void Split(char**& arrTokens, char* word, const char* separator = " ");
// Merge các token trong arrTokens lại thành chuỗi -> dest, nTokens: số token có trong arrTokens
void MergeTokens(char*& dest, char** arrTokens, int nTokens);
bool IsCapitalLetter(char c);
bool IsLowerLetter(char c);
// format full name ( " tRaN  COng mINH " => "Tran Cong Minh" )
void FormatWord(char*& fullName, WordType type);
void FormatWord(std::string& fullName);
int NumberLength(unsigned int num);
// merge number vào sau word
void MergeWordWithNumber(char*& word, unsigned int number, unsigned int maxLengthWord);
void MergeWordWithNumber(std::string& word, unsigned int number, unsigned int maxLengthWord);
std::vector<std::string> Split(std::string, std::string delimiter = " ");
void StringToCharArray(std::string source, char dest[]);
std::string ToLowerString(std::string text);
std::string ToUpperString(std::string text);
std::string Trim(std::string text);
char* StringToCharArray(std::string source);
void VTString2ArrString(std::vector<std::string> data, std::string result[]);

template <class T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

// thay doi kich co cua mang con tro
template <class T>
void ResizeArray(T*& list, int oldSize, int newSize)
{
	if (oldSize == 0)
	{
		list = new T[newSize];
		return;
	}
	T* temp = new T[oldSize];

	for (int i = 0; i < oldSize; i++)
	{
		temp[i] = list[i];
	}

	delete[] list;

	list = new T[newSize];

	int min = oldSize < newSize ? oldSize : newSize;

	for (int i = 0; i < min; i++)
	{
		list[i] = temp[i];
	}

	delete[] temp;
}

template <class T>
void PushBack(T*& list, T obj, int& count)
{
	ResizeArray(list, count, count + 1);
	list[count] = obj;
	count++;
}

template <class T>
int SizeOfT(T* list)
{
	if (list == NULL) return 0;
	return *(((int*)list) - 1);
}

template <class T>
bool Erase(T*& list, int at)
{
	int size = SizeOfT(list);
	for (int i = 0; i < size; i++)
	{
		if (i == at)
		{
			list[i] = list[size - 1];
			ResizeArray(list, size, size - 1);
			return true;
		}
	}
	return false;
}