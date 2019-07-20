#pragma once
#include <ctime>
#include "TextHandler.h"

#define defaultDay 1
#define defaultMonth 1
#define defaultYear 1970

struct DATETIME
{
	time_t t = time(0);
	tm* now = localtime(&t);

	unsigned int day;
	unsigned int month;
	unsigned int year;

	unsigned int hour;
	unsigned int minute;
	unsigned int second;

	DATETIME() : day(defaultDay), month(defaultMonth), year(defaultYear), hour(0), minute(0), second(0)
	{

	}
	DATETIME(unsigned int day, unsigned int month, unsigned int year)
		: hour(0), minute(0), second(0)
	{
		if (IsValid(day, month, year, 0, 0, 0))
		{
			this->day = day;
			this->month = month;
			this->year = year;
		}
		else
		{
			DATETIME();
		}
	}
	DATETIME(unsigned int day, unsigned int month, unsigned int year,
		unsigned int hour, unsigned int minute, unsigned int second)
	{
		if (IsValid(day, month, year, hour, minute, second))
		{
			this->day = day;
			this->month = month;
			this->year = year;
			this->hour = hour;
			this->minute = minute;
			this->second = second;
		}
		else
		{
			DATETIME();
		}
	}

	void SetDateTimeNow()
	{
		this->year = now->tm_year + 1900;
		this->month = now->tm_mon + 1;
		this->day = now->tm_mday;
		this->hour = now->tm_hour;
		this->minute = now->tm_min;
		this->second = now->tm_sec;
	}
	string ToStringDate()
	{
		string result = "";

		if (this->day < 10) result = "0";
		result += to_string(this->day);
		result += "/";

		if (this->month < 10) result += "0";
		result += to_string(this->month);
		result += "/";
		result += to_string(this->year);
		return result;
	}
	string ToStringTime()
	{
		string result = "";

		if (this->hour < 10) result = "0";
		result += to_string(this->hour);
		result += ":";

		if (this->minute < 10) result += "0";
		result += to_string(this->minute);
		result += ":";

		if (this->second < 10) result += "0";
		result += to_string(this->second);
		return result;
	}

	bool IsValid(unsigned int day, unsigned int month, unsigned int year,
		unsigned int hour, unsigned int minute, unsigned int second)
	{
		return (hour > 23 ||
			minute > 59 ||
			second > 59 ||
			day > 31 ||
			month > 12 ||
			year > 9999) ? false : true;
	}

	DATETIME ParseStringDate(string dateAsString)
	{
		auto date = Split(dateAsString, "/");
		day = stoi(date[0]);
		month = stoi(date[1]);
		year = stoi(date[2]);
		return *this;
	}
	DATETIME ParseStringTime(string timeAsString)
	{
		auto time = Split(timeAsString, ":");
		hour = stoi(time[0]);
		minute = stoi(time[1]);
		year = stoi(time[2]);
		return *this;
	}

	bool IsNamNhuan(unsigned int year)
	{
		return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}
	int GetDaysOfYear(unsigned int year)
	{
		if (IsNamNhuan(year))
			return 366;
		return 365;
	}
	int GetDaysOfMonth(unsigned int month, unsigned int year)
	{
		switch (month)
		{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			return 31;
		case 4: case 6: case 9: case 11:
			return 30;
		case 2:
			if (IsNamNhuan(year)) return 29;
			return 28;
		default:
			return 0;
			break;
		}
	}

	int SubDate(DATETIME anotherDate)
	{
		return this->SubToDefaultDate() - anotherDate.SubToDefaultDate();
	}
	int SubToDefaultDate()
	{
		int days = 0;
		for (size_t i = defaultYear; i < this->year; i++)
		{
			days += GetDaysOfYear(i);
		}
		for (size_t i = defaultMonth; i < this->month; i++)
		{
			days += GetDaysOfMonth(i, this->year);
		}
		days += this->day - defaultDay;
		return days;
	}
};