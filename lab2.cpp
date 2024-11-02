﻿//ивановская олеся 9 группа
// 8. Создать класс Time для работы со временем в формате «час:минута:секунда». Класс
//должен включать в себя не менее четырех способов инициализации : 
// числами,
// строкой(например, «23:59 : 59»), 
// секундами, 
// встроенным типом времени.
//Обязательными операциями являются : 
// вычисление разности между двумя моментами времени в секундах, 
// сложение времени и заданного количества секунд (также в виде перегрузки операторов + и - )
// вычитание из времени заданного количества секунд, 
// сравнение моментов времени, 
// перевод в секунды, 
// перевод в минуты(с округлением до целой минуты).
// 
// 
//Во всех упражнениях, помимо указанных методов, обязательно должны быть
//реализованы функции ввода данных с клавиатуры и из файла, функции вывода данных
//на экран и в файл, метод преобразования в строку to_string.Для класса необходимо
//выполнить перегрузку операторов(+, -, *, / , битовые операторы, операторы
//сравнения — <=> и == ), если это возможно. Реализовывая операции нельзя использовать приведение к другим, более
// вместительным типам.Например, нельзя просто засунуть два long - а в longlong,сложить, а 
// затем разделить обратно на лонги в задаче №17 на класс LongLong.
// Аналогично, нельзя загонять массивы в большие числа или в тип string.
// Задача должна демонстрировать работу всех методов, для этого пользователь
//  должен мочь ввести Объект_A и Объект_B.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
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

	Time(int h, int m, int s);
	Time(const std::string& str);
	Time(int sec);
	Time(tm *time);

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
	bool operator< (const Time& time);
	bool operator<= (const Time& time);
	bool operator> (const Time& time);
	bool operator>= (const Time& time);
	bool operator== (const Time& time);
	bool operator!= (const Time& time);
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
	void print_time(std::ostream& ostr);
	void time_in(std::istream& istr);
	~Time();
};

int main()
{
    SetConsoleOutputCP(1251);
	//иниц циферками
	std::cout << "-> ";
	Time t1(0);

	/*std::cout << "Введите имя файла:\n>";
	std::string file_name;
	std::cin >> file_name;
	std::ifstream file(file_name);*/


	//иниц строкой
	//std::cout << "-> ";
	//std::string input;
	//std::getline(std::cin, input);
	//Time t(input);
	//std::cout << t ;

	//иниц секундами
	/*std::cout << "-> ";
	int sec{};
	std::cin >> sec;
	Time t(sec);
	t.print_time(std::cout);*/

	//встроенный?
	/*time_t now = time(0);
	tm time{};
	localtime_s(&time, &now);
	Time t(&time);
	t.print_time(std::cout);*/

	std::cin.ignore(std::cin.rdbuf()->in_avail()).get();
}

void Time::valid_time()
{
	int tmp{};
	if (seconds > 59)
	{
		tmp = seconds / 60;
		seconds = seconds % 60;
		minutes += tmp;
		tmp = 0;
	}
	if (minutes > 59)
	{
		tmp = minutes / 60;
		minutes = minutes % 60;
		hours += tmp;
		tmp = 0;
	}

	if (seconds < 0)
	{
		minutes -= abs(seconds / 60) +1;
		seconds += 60;
	}

	if (minutes < 0)
	{
		if (hours)
		{
			hours-= abs(minutes/60)+1;
			minutes += 60;
		}
		else
			std::cout << "Время закончилось!!\n";
	}

	if (hours <0)
		std::cout << "Время закончилось!!\n";
}

int Time::get_hours()
{
	return hours;
}

int Time::get_minutes()
{
	return minutes;
}

int Time::get_seconds()
{
	return seconds;
}

Time::Time(int h, int m, int s) //учесть что секунд может быть больше
{
	hours = { h };
	minutes = { m };
	seconds = { s };
	valid_time();
}

Time::Time(const std::string& str)
{
	std::istringstream ss(str);
	char c;
	ss >> hours >> c >> minutes >> c >> seconds;
	valid_time();
}

Time::Time(int sec)
{
	seconds = { sec };
	hours = minutes = {};
	valid_time();
}

Time::Time(tm* time)
{
	hours = { time->tm_hour };
	minutes = { time->tm_min };
	seconds = { time->tm_sec };
}

bool Time::operator<(const Time& time)
{
	bool res{};
	if (hours < time.hours ||
		hours == time.hours && minutes < time.minutes ||
		hours == time.hours && minutes == time.minutes && seconds < time.seconds)
		res = 1;
	return res;
}

bool Time::operator<=(const Time& time)
{
	bool res{};
	if (hours < time.hours ||
		hours == time.hours && minutes < time.minutes ||
		hours == time.hours && minutes == time.minutes && seconds <= time.seconds)
		res = 1;
	return res;
}

bool Time::operator>(const Time& time)
{
	bool res{};
	if (hours > time.hours ||
		hours == time.hours && minutes > time.minutes ||
		hours == time.hours && minutes == time.minutes && seconds > time.seconds)
		res = 1;
	return res;
}

bool Time::operator>=(const Time& time)
{
	bool res{};
	if (hours > time.hours ||
		hours == time.hours && minutes > time.minutes ||
		hours == time.hours && minutes == time.minutes && seconds >= time.seconds)
		res = 1;
	return res;
}

bool Time::operator==(const Time& time)
{
	return hours == time.hours && minutes == time.minutes && seconds == time.seconds;
}

bool Time::operator!=(const Time& time)
{
	return !(hours == time.hours && minutes == time.minutes && seconds == time.seconds);
}

Time Time::operator+(const Time& time) const
{
	return Time(hours+time.hours, minutes+time.minutes, seconds + time.seconds);
}

int Time::operator-(const Time& time) const
{
	int final_sec{ hours * 3600 - time.hours * 3600
		+ minutes * 60 - time.minutes * 60
		+ seconds - time.seconds };
	return abs(final_sec);
}

int Time::to_seconds()
{
	return hours * 3600 + minutes * 60 + seconds;
}

int Time::to_minutes()
{
	int t{ hours * 60 + minutes};
	if (seconds > 0)
		t++;
	return t;
}

int Time::seconds_between(const Time& time)
{
	Time t(*this - time);
	return t.to_seconds();
}

Time Time::operator+(int sec)
{
	return Time(hours, minutes, seconds + sec);
}

Time Time::seconds_plus(int sec)
{
	return Time((*this).to_seconds() +sec);
}

Time Time::seconds_minus(int sec)
{
	return Time((*this).to_seconds() - sec);
}

int Time::compare(const Time& time)
{
	int res{ -1 };
	if (*this > time)
		res = 1;
	else
		if (*this == time)
			res = 0;
	return res;
}

std::string Time::to_string()
{
	std::ostringstream str;
	str << hours << ":" << minutes << ":" << seconds;
	return str.str();
}

void Time::print_time(std::ostream& ostr)
{
	ostr << *this;
}

void Time::time_in(std::istream& istr)
{
	istr >> *this;
}

Time::~Time()
{
}
