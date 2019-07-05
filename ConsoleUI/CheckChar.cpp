#include "CheckChar.h"

// Only number
bool IsNumber(char c)
{
	return isdigit(c);
}
// Only upper
bool IsUpper(char c)
{
	return isupper(c);
}
// Only lower
bool IsLower(char c)
{
	return islower(c);
}
// text and whitespace
bool IsLetterOnly(char c)
{
	return isupper(c) || islower(c) || isblank(c);
}
// text, number and whitespace
bool IsMixLetter(char c)
{
	return IsLetterOnly(c) || isdigit(c);
}
