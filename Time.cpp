#include "Time.h"

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
		minutes -= abs(seconds / 60) + 1;
		seconds += 60;
	}

	if (minutes < 0)
	{
		if (hours)
		{
			hours -= abs(minutes / 60) + 1;
			minutes += 60;
		}
		else
		{
			std::cout << "Âðåìÿ çàêîí÷èëîñü!!\n";
			valid = 0;
		}
	}

	if (hours < 0)
	{
		std::cout << "Âðåìÿ çàêîí÷èëîñü!!\n";
		valid = 0;
	}
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


Time::Time()
{
	hours = minutes = seconds = {};
	valid = { 1 };
}

Time::Time(int h, int m, int s) //ó÷åñòü ÷òî ñåêóíä ìîæåò áûòü áîëüøå
{
	hours = { h };
	minutes = { m };
	seconds = { s };
	valid = { 1 };
	valid_time();
}

Time::Time(const std::string& str)
{
	std::istringstream ss(str);
	char c;
	ss >> hours >> c >> minutes >> c >> seconds;
	valid = { 1 };
	valid_time();
}

Time::Time(int sec)
{
	seconds = { sec };
	hours = minutes = {};
	valid = { 1 };
	valid_time();
}

Time::Time(tm* time)
{
	hours = { time->tm_hour };
	minutes = { time->tm_min };
	seconds = { time->tm_sec };
	valid = { 1 };
}

bool Time::operator==(const Time& time) const
{
	return hours == time.hours && minutes == time.minutes && seconds == time.seconds;
}

bool Time::operator!=(const Time& time) const
{
	return !(hours == time.hours && minutes == time.minutes && seconds == time.seconds);
}

std::strong_ordering Time::operator<=>(const Time& time) const {
	std::strong_ordering res;
	if (hours != time.hours) { res = hours <=> time.hours; }
	else
		if (minutes != time.minutes) { res = minutes <=> time.minutes; }
		else
			res = seconds <=> time.seconds;
	return res;
}

Time Time::operator+(const Time& time) const
{
	return Time(hours + time.hours, minutes + time.minutes, seconds + time.seconds);
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
	int t{ hours * 60 + minutes };
	if (seconds > 0)
		t++;
	return t;
}

int Time::seconds_between(const Time& time)
{
	Time t(*this - time);
	return t.to_seconds();
}

Time Time::operator+(int sec) const
{
	return Time(hours, minutes, seconds + sec);
}

Time Time::seconds_plus(int sec)
{
	return Time((*this).to_seconds() + sec);
}

Time Time::seconds_minus(int sec)
{
	return Time((*this).to_seconds() - sec);
}

int Time::compare(const Time& time)
{
	int res{ -1 };
	std::strong_ordering id{ (*this) <=> time };
	if (id == std::strong_ordering::greater)
		res = 1;
	else
		if (id == std::strong_ordering::equal)
			res = 0;
	return res;
}

std::string Time::to_string()
{
	std::ostringstream str;
	str << hours << ":" << minutes << ":" << seconds;
	return str.str();
}

Time::~Time()
{
}

bool Time::is_valid()
{
	return valid;
}
