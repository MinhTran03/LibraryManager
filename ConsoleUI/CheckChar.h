#pragma once
#include <ctype.h>

// Only number
bool IsNumber(char c);
// Only upper
bool IsUpper(char c);
// Only lower
bool IsLower(char c);
// text and whitespace
bool IsLetterOnly(char c);
// text, number and whitespace
bool IsMixLetter(char c);
bool IsAllLetter(char c);
