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

template <class T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}