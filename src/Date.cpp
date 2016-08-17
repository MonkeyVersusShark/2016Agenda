#include "Date.hpp"
#include <cstring>
#include <cstdlib>
#include <sstream>

/**
* @brief default constructor
*/
Date::Date() : m_year(0), m_month(0), m_day(0), m_hour(0), m_minute(0) { }

/**
* @brief constructor with arguments
*/
Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute)
	: m_year(t_year), m_month(t_month), m_day(t_day),
	m_hour(t_hour), m_minute(t_minute) { }

/**
* @brief constructor with a string
*/
Date::Date(std::string dateString) {
	Date t_date = stringToDate(dateString);
	(*this) = t_date;
}

/**
* @brief return the year of a Date
* @return   a integer indicate the year of a date
*/
int Date::getYear(void) const { return m_year; }

/**
* @brief set the year of a date
* @param a integer indicate the new year of a date
*/
void Date::setYear(const int t_year) { m_year = t_year; }

/**
* @brief return the month of a Date
* @return   a integer indicate the month of a date
*/
int Date::getMonth(void) const { return m_month; }

/**
* @brief set the month of a date
* @param a integer indicate the new month of a date
*/
void Date::setMonth(const int t_month) { m_month = t_month; }

/**
* @brief return the day of a Date
* @return   a integer indicate the day of a date
*/
int Date::getDay(void) const { return m_day; }

/**
* @brief set the day of a date
* @param a integer indicate the new day of a date
*/
void Date::setDay(const int t_day) { m_day = t_day; }

/**
* @brief return the hour of a Date
* @return   a integer indicate the hour of a date
*/
int Date::getHour(void) const { return m_hour; }

/**
* @brief set the hour of a date
* @param a integer indicate the new hour of a date
*/
void Date::setHour(const int t_hour) { m_hour = t_hour; }

/**
* @brief return the minute of a Date
* @return   a integer indicate the minute of a date
*/
int Date::getMinute(void) const { return m_minute; }

/**
* @brief set the minute of a date
* @param a integer indicate the new minute of a date
*/
void Date::setMinute(const int t_minute) { m_minute = t_minute; }

/**
*   @brief check whether the date is valid or not
*   @return the bool indicate valid or not
*/
bool Date::isValid(const Date t_date) {
	if (t_date.m_year < 1000 || t_date.m_year > 9999) return false;
	if (t_date.m_month < 1 || t_date.m_month > 12) return false;
	switch (t_date.m_month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		if (t_date.m_day < 1 || t_date.m_day > 31) return false;
		else break;
	case 4: case 6: case 9: case 11:
		if (t_date.m_day < 1 || t_date.m_day > 30) return false;
		else break;
	case 2:
		auto isLeap = [](const int t_year) {
			if (t_year % 400 == 0) return true;
			if (t_year % 4 == 0 && t_year % 100 != 0) return true;
			return false;
		};
		if (isLeap(t_date.m_year)) {
			if (t_date.m_day < 1 || t_date.m_day > 29) return false;
		}
		else {
			if (t_date.m_day < 1 || t_date.m_day > 28) return false;
		}
		break;
	}
	if (t_date.m_hour < 0 || t_date.m_hour > 23) return false;
	if (t_date.m_minute < 0 || t_date.m_minute > 59) return false;
	return true;
}

/**
* @brief convert a string to date, if the format is not correct return
* 0000-00-00/00:00
* @return a date
*/
Date Date::stringToDate(const std::string t_dateString) {
	if (t_dateString.size() != 16) return Date();

	int index[4];
	index[0] = t_dateString.find('-');
	if (index[0] != 4) return Date();
	index[1] = t_dateString.find('-', index[0] + 1);
	if (index[1] != 7) return Date();
	index[2] = t_dateString.find('/', index[1] + 1);
	if (index[2] != 10) return Date();
	index[3] = t_dateString.find(':', index[2] + 1);
	if (index[3] != 13) return Date();

	std::string t_monthString = "";
	for (int i = index[0] + 1; i < index[1]; i++)
		t_monthString += t_dateString[i];
	if (t_monthString.size() != 2) return Date();

	std::string t_str[5];
	int t_data[5];
	for (int i = 0; i < index[0]; i++)
		t_str[0] += t_dateString[i];
	t_data[0] = std::atoi(t_str[0].c_str());
	for (int i = 1; i <= 3; i++) {
		for (int j = index[i - 1] + 1; j < index[i]; j++)
			t_str[i] += t_dateString[j];
		t_data[i] = std::atoi(t_str[i].c_str());
	}
	for (int i = index[3] + 1; i < t_dateString.size(); i++)
		t_str[4] += t_dateString[i];
	t_data[4] = std::atoi(t_str[4].c_str());

	Date retDate(t_data[0], t_data[1], t_data[2], t_data[3], t_data[4]);
	if (!isValid(retDate)) return Date();

	return retDate;
}

/**
* @brief convert a date to string, if the format is not correct return
* 0000-00-00/00:00
*/
std::string Date::dateToString(Date t_date) {
	if (!isValid(t_date)) return "0000-00-00/00:00";

	auto int_to_string = [=](int integer) -> std::string {
		std::stringstream stream;
		stream << integer;
		return stream.str();
	};

	std::string result;
	result += int_to_string(t_date.m_year) + "-";
	if (t_date.m_month < 10)
		result += "0";
	result += int_to_string(t_date.m_month) + "-";
	if (t_date.m_day < 10)
		result += "0";
	result += int_to_string(t_date.m_day) + "/";
	if (t_date.m_hour < 10)
		result += "0";
	result += int_to_string(t_date.m_hour) + ":";
	if (t_date.m_minute < 10)
		result += "0";
	result += int_to_string(t_date.m_minute);

	return result;
}

/**
*  @brief overload the assign operator
*/
Date &Date::operator=(const Date &t_date) {
	if (this == &t_date)
		return *this;

	m_year = t_date.m_year;
	m_month = t_date.m_month;
	m_day = t_date.m_day;
	m_hour = t_date.m_hour;
	m_minute = t_date.m_minute;
	return *this;
}

/**
* @brief check whether the CurrentDate is equal to the t_date
*/
bool Date::operator==(const Date &t_date) const {
	if (m_year == t_date.m_year
		&& m_month == t_date.m_month
		&& m_day == t_date.m_day
		&& m_hour == t_date.m_hour
		&& m_minute == t_date.m_minute)
		return true;
	return false;
}

/**
* @brief check whether the CurrentDate is  greater than the t_date
*/
bool Date::operator>(const Date &t_date) const {
	if (m_year > t_date.m_year) return true;
	if (m_year < t_date.m_year) return false;
	if (m_month > t_date.m_month) return true;
	if (m_month < t_date.m_month) return false;
	if (m_day > t_date.m_day) return true;
	if (m_day < t_date.m_day) return false;
	if (m_hour > t_date.m_hour) return true;
	if (m_hour < t_date.m_hour) return false;
	if (m_minute > t_date.m_minute) return true;
	if (m_minute < t_date.m_minute) return false;
	return false;
}

/**
* @brief check whether the CurrentDate is  less than the t_date
*/
bool Date::operator<(const Date &t_date) const {
	if (!((*this) >= t_date)) return true;
	return false;
}

/**
* @brief check whether the CurrentDate is  greater or equal than the t_date
*/
bool Date::operator>=(const Date &t_date) const {
	if ((*this) > t_date || (*this) == t_date) return true;
	return false;
}

/**
* @brief check whether the CurrentDate is  less than or equal to the t_date
*/
bool Date::operator<=(const Date &t_date) const {
	if (!((*this) > t_date)) return true;
	return false;
}
