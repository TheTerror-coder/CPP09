/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:59:07 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/13 18:47:26 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Date.hpp"

Date::Date() : year(0), month(0), day(0)
{
	Date::initWeekDaysBase();
}

Date::Date(int y, int m, int d) : year(y), month(m), day(d)
{
	Date::initWeekDaysBase();
	if (this->month < 1 || this->month > 12)
		throw(InvalidMonthException());
	if (this->day < 1 || this->day > 31)
		throw(InvalidDayException());
}

Date::Date(int y, int m, int d, std::string dayofweek) : year(y), month(m), \
														day(d)
{
	Date::initWeekDaysBase();
	if (this->month < 1 || this->month > 12)
		throw(InvalidMonthException());
	if (this->day < 1 || this->day > 31)
		throw(InvalidDayException());
	try
	{
		dayofweek = strToLower(dayofweek);
		this->dayofweek = Date::weekdays_base.at(dayofweek);
	}
	catch(const std::exception& e)
	{
		throw(Date::InvalidDayOfWeekException());
	}
}

Date::Date(std::string y, std::string m, std::string d) : year(0), month(0), \
														day(0)
{
	Date::initWeekDaysBase();
	constructorRoutine(y, m, d);
}

Date::Date(std::string y, std::string m, std::string d, std::string dayofweek) : year(0), month(0), \
														day(0)
{
	Date::initWeekDaysBase();
	constructorRoutine(y, m, d);
	try
	{
		dayofweek = strToLower(dayofweek);
		this->dayofweek = Date::weekdays_base.at(dayofweek);
	}
	catch(const std::exception& e)
	{
		throw(InvalidDayOfWeekException());
	}
}

/*copy constructor*/
Date::Date(const Date& other) : year(other.year), month(other.month), \
								day(other.day), dayofweek(other.dayofweek)
{
	Date::initWeekDaysBase();
	*this = other;
}

/*assignment operator*/
Date&	Date::operator=(const Date& other)
{
	if (this == &other)
		return (*this);
	this->year = other.year;
	this->month = other.month;
	this->day = other.day;
	this->dayofweek = other.dayofweek;
	return (*this);
}

/*Destructor*/
Date::~Date()
{}

void			Date::constructorRoutine(std::string& y, std::string& m, std::string& d)
{
	if (y.empty() || !strIsInt(y))
		throw(InvalidYearException());
	if (m.empty() || !strIsInt(m))
		throw(InvalidMonthException());
	if (d.empty() || !strIsInt(d))
		throw(InvalidDayException());
	this->year = std::atoi(y.c_str());
	this->month = std::atoi(m.c_str());
	this->day = std::atoi(d.c_str());
	if (this->month < 1 || this->month > 12)
		throw(InvalidMonthException());
	if (this->day < 1 || this->day > 31)
		throw(InvalidDayException());
}

int				Date::getYear() const
{
	return (this->year);
}
int				Date::getMonth() const
{
	return (this->month);
}
int				Date::getDay() const
{
	return (this->day);
}
std::string		Date::getDayOfWeek() const
{
	return (this->dayofweek);
}
void			Date::setYear(int y)
{
	this->year = y;
}
void			Date::setMonth(int m)
{
	this->month = m;
	if (this->month < 1 || this->month > 12)
		throw(InvalidMonthException());
}
void			Date::setDay(int d)
{
	this->day = d;
	if (this->day < 1 || this->day > 31)
		throw(InvalidDayException());
}
void			Date::setDayOfWeek(std::string d)
{
	try
	{
		d = strToLower(d);
		this->dayofweek = Date::weekdays_base.at(d);
	}
	catch(const std::exception& e)
	{
		throw(InvalidDayOfWeekException());
	}
}

bool			Date::operator== (const t_date& rhs) const
{
	if (this->year == rhs.year && \
		this->month == rhs.month && \
		this->day == rhs.day)
		return (true);
	return (false);
}

bool			Date::operator!= (const t_date& rhs) const
{
	return (!(*this == rhs));
}

bool			Date::operator< (const t_date& rhs) const
{
	if (this->year < rhs.year)
		return (true);
	if (this->year == rhs.year && \
		this->month < rhs.month)
		return (true);
	if (this->year == rhs.year && \
		this->month == rhs.month && \
		this->day < rhs.day)
		return (true);
	return (false);
}

bool			Date::operator> (const t_date& rhs) const
{
	if (this->year > rhs.year)
		return (true);
	if (this->year == rhs.year && \
		this->month > rhs.month)
		return (true);
	if (this->year == rhs.year && \
		this->month == rhs.month && \
		this->day > rhs.day)
		return (true);
	return (false);
}

bool			Date::operator<= (const t_date& rhs) const
{
	if (*this < rhs || *this == rhs)
		return (true);
	return (false);
}

bool			Date::operator>= (const t_date& rhs) const
{
	if (*this > rhs || *this == rhs)
		return (true);
	return (false);
}

const char*		Date::DateErrorException::what() const throw()
{
	return ("DateErrorException thrown");
}
const char*		Date::InvalidDayOfWeekException::what() const throw()
{
	return ("unknown day of week, InvalidDayOfWeekException thrown");
}
const char*		Date::InvalidYearException::what() const throw()
{
	return ("unknown year, InvalidYearException thrown");
}
const char*		Date::InvalidMonthException::what() const throw()
{
	return ("unknown month, valid range [1, 12], InvalidMonthException thrown");
}
const char*		Date::InvalidDayException::what() const throw()
{
	return ("unknown day of month, valid range [1, 30], InvalidDayException thrown");
}

void	Date::initWeekDaysBase(void)
{
	Date::weekdays_base.insert(std::pair<std::string, std::string>("monday", "monday"));
	Date::weekdays_base.insert(std::pair<std::string, std::string>("tuesday", "tuesday"));
	Date::weekdays_base.insert(std::pair<std::string, std::string>("wednesday", "wednesday"));
	Date::weekdays_base.insert(std::pair<std::string, std::string>("thursday", "thursday"));
	Date::weekdays_base.insert(std::pair<std::string, std::string>("friday", "friday"));
	Date::weekdays_base.insert(std::pair<std::string, std::string>("saturday", "saturday"));
	Date::weekdays_base.insert(std::pair<std::string, std::string>("sunday", "sunday"));
	
	Date::weekdays_base.insert(std::pair<std::string, std::string>("lundi", "monday"));
	Date::weekdays_base.insert(std::pair<std::string, std::string>("mardi", "tuesday"));
	Date::weekdays_base.insert(std::pair<std::string, std::string>("mercredi", "wednesday"));
	Date::weekdays_base.insert(std::pair<std::string, std::string>("jeudi", "thursday"));
	Date::weekdays_base.insert(std::pair<std::string, std::string>("vendredi", "friday"));
	Date::weekdays_base.insert(std::pair<std::string, std::string>("samedi", "saturday"));
	Date::weekdays_base.insert(std::pair<std::string, std::string>("dimanche", "sunday"));
}

std::string		Date::strToLower(std::string str)
{
	std::string		lowstr;

	lowstr = str;
	if (str.empty())
		return (str);
	for (size_t i = 0; i < str.size(); i++)
		lowstr[i] = std::tolower(str.at(i));
	return (lowstr);
}

bool			Date::strIsInt(std::string str)
{
	size_t	i;

	i = 0;
	if (str.empty())
		return (false);
	if (str.at(i) == '-' || str.at(i) == '+')					// (optional) plus or minus sign 
		i++;
	for (i = i; i < str.size(); i++)							// nonempty sequence of decimal digits
	{
		if (!std::isdigit(str.at(i)))
			return (false);
	}
	return (true);
}

std::ostream&	operator<< (std::ostream& os, const Date& lhs)
{
	if (lhs.getDayOfWeek().empty())
		os << lhs.getMonth() << "/" << lhs.getDay() << "/" << lhs.getYear();
	else
		os << lhs.getDayOfWeek() << " " << lhs.getMonth() << "/" << \
			lhs.getDay() << "/" << lhs.getYear();
	return (os);
}
