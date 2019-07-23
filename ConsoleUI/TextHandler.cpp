#include "TextHandler.h"

int WordCount(char* word, const char* separator)
{
	//const char* separator = " .,;:\n\t";
	int nWords = 0;
	char* temp = new char[strlen(word) + 1];
	strcpy(temp, word);
	char* token = strtok(temp, separator);
	while (token != NULL)
	{
		nWords++;
		token = strtok(NULL, separator);
	}
	delete[] temp;
	return nWords;
}
void WriteLine(char* word)
{
	if (word == NULL) return;
	for (unsigned int i = 0; i < strlen(word); i++)
		cout << word[i];
	cout << endl;
}
void Split(char**& arrTokens, char* word, const char* separator)
{
	int nTokens = WordCount(word, separator);
	// tạo mảng 2 chiều chứa n token
	arrTokens = NULL;
	arrTokens = new char* [nTokens];
	// lấy token đầu tiên
	char* token = strtok(word, separator);
	for (int i = 0; i < nTokens; i++)
	{
		// tạo 1 row có col = chiều dài token
		arrTokens[i] = new char[strlen(token)];
		// copy vô result
		strcpy(arrTokens[i], token);
		// lấy token kế tiếp
		token = strtok(NULL, separator);
	}
}
int TotalTokenSize(char** arrTokens, int nTokens)
{
	int sum = 0;
	for (int i = 0; i < nTokens; i++)
	{
		sum += strlen(arrTokens[i]);
	}
	return sum;
}
void MergeTokens(char*& word, char** arrTokens, int nTokens)
{
	word = NULL;
	word = new char[TotalTokenSize(arrTokens, nTokens)];
	strcpy(word, arrTokens[0]);
	for (int i = 1; i < nTokens; i++)
	{
		strcat(word, " ");
		strcat(word, arrTokens[i]);
	}
}
bool IsCapitalLetter(char c)
{
	if (c >= 'A' && c <= 'Z')
		return true;
	return false;
}
bool IsLowerLetter(char c)
{
	if (c >= 'a' && c <= 'z')
		return true;
	return false;
}
// format 1 từ theo chuẩn name ( "tRan" => "Tran" )
void FormatName(char*& name)
{
	int doDaiChuoi = strlen(name);
	if (IsLowerLetter(name[0]))
		name[0] -= 32;
	for (int i = 1; i < doDaiChuoi; i++)
		if (IsCapitalLetter(name[i]))
			name[i] += 32;
}
void FormatWord(char*& fullName, WordType type)
{
	int nTokens = WordCount(fullName);
	char** tokens = NULL;
	Split(tokens, fullName);

	for (int i = 0; i < nTokens; i++)
	{
		if (type == WordType::Name)
		{
			FormatName(tokens[i]);
		}
		else if (type == WordType::Word_Only)
		{
			// token đầu viết hoa
			if (i == 0) FormatName(tokens[i]);
			else _strlwr(tokens[i]);
		}
	}
	fullName = NULL;
	MergeTokens(fullName, tokens, nTokens);
	delete tokens;
}
void FormatWord(string& fullName)
{
	for (char& c : fullName)
	{
		c = tolower(c);
	}
	fullName[0] = toupper(fullName[0]);
}
int NumberLength(unsigned int num)
{
	int count = 0;
	do
	{
		count++;
		num = num / 10;
	} while (num != 0);
	return count;
}
void MergeWordWithNumber(char*& word, unsigned int number, unsigned int maxLengthWord)
{
	// số chữ số của number
	int numberSize = NumberLength(number);
	// số chữ số 0 chèn giữa word và number
	int countZero = maxLengthWord - strlen(word) - numberSize - 1;
	// chèn 0 vô giữa word và number
	for (int i = 0; i < countZero; i++)
		strcat(word, "0");

	// tạo chuỗi chứa số
	char* numberAsString = new char[numberSize];
	_itoa(number, numberAsString, 10);
	// nối số vào cuối
	strcat(word, numberAsString);
}
void MergeWordWithNumber(string& word, unsigned int number, unsigned int maxLengthWord)
{
	// số chữ số của number
	int numberSize = NumberLength(number);
	// số chữ số 0 chèn giữa word và number
	int countZero = maxLengthWord - word.size() - numberSize;
	// chèn 0 vô giữa word và number
	for (int i = 0; i < countZero; i++)
		word += "0";

	// tạo chuỗi chứa số
	char* numberAsString = new char[numberSize];
	_itoa(number, numberAsString, 10);
	// nối số vào cuối
	word += numberAsString;
}
string* Split(string text, string delimiter)
{
	string* result;
	size_t pos = 0;
	string token;
	text += delimiter;
	int count = 0;
	while ((pos = text.find(delimiter)) != string::npos)
	{
		token = text.substr(0, pos);
		PushBack(result, token, count);
		//result.push_back(token);
		text.erase(0, pos + delimiter.length());
	}
	return result;
}
void StringToCharArray(string source, char dest[])
{
	strcpy(dest, source.c_str());
}
string Trim(string text)
{
	auto at = text.find_first_of(' ');
	if (at > text.size())
		return text;
	text.erase(text.begin() + at, text.end());
	return text;
}
char* StringToCharArray(string source)
{
	char* result = new char[source.size() + 1];
	strcpy(result, source.c_str());
	return result;
}
string ToLowerString(string text)
{
	string result = text;
	for (char& c : result)
	{
		c = tolower(c);
	}
	return result;
}
string ToUpperString(string text)
{
	string result = text;
	for (char& c : result)
	{
		c = toupper(c);
	}
	return result;
}
bool IsNumber(string text)
{
	for (auto c : text)
	{
		if (!isdigit(c)) return false;
	}
	return true;
}