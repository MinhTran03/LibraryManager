#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Enums.h"

using namespace std;

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
void FormatWord(string& fullName);
void FormatName(string& name);
int NumberLength(unsigned int num);
// merge number vào sau word
void MergeWordWithNumber(char*& word, unsigned int number, unsigned int maxLengthWord);
void MergeWordWithNumber(string& word, unsigned int number, unsigned int maxLengthWord);
string* Split(string, string delimiter = " ");
void StringToCharArray(string source, char dest[]);
string ToLowerString(string text);
string ToUpperString(string text);
string Trim(string text);
char* StringToCharArray(string source);
bool IsNumber(string text);

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

//template <class T>
//int SizeOfT(T* list)
//{
//	if (list == NULL) return 0;
//	int s = *(((int*)list) - 1);
//	return s;
//}

template <class T>
bool Erase(T*& list, int at, int size)
{
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

//template <class T>
//bool Erase(T*& list, int at)
//{
//	int size = SizeOfT(list);
//	for (int i = 0; i < size; i++)
//	{
//		if (i == at)
//		{
//			list[i] = list[size - 1];
//			ResizeArray(list, size, size - 1);
//			return true;
//		}
//	}
//	return false;
//}