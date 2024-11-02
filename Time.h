#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <compare>
#include <Windows.h>

class Time
{
private:
	int hours;
	int minutes;
	int seconds;
	void valid_time();
public:
	int get_hours();
	int get_minutes();
	int get_seconds();

	Time();
	Time(int h, int m, int s);
	Time(const std::string& str);
	Time(int sec);
	Time(tm* time);

	friend std::ostream& operator<<(std::ostream& out, const Time& time) {
		out << time.hours << ":" << time.minutes << ":" << time.seconds << '\n';
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Time& time) {
		char c;
		in >> time.hours >> c >> time.minutes >> c >> time.seconds;
		time.valid_time();
		return in;
	}

	//перегрузки 
	bool operator== (const Time& time);
	bool operator!= (const Time& time);
	std::strong_ordering operator<=>(const Time& time) const;
	Time operator+ (const Time& time) const;

	int operator-(const Time& time) const;
	int to_seconds();
	int to_minutes();
	int seconds_between(const Time& time);
	Time operator+(int sec);
	Time seconds_plus(int sec);
	Time seconds_minus(int sec);
	int compare(const Time& time);
	std::string to_string();
	~Time();
};
