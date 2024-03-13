/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:11:35 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/13 18:25:08 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/*default constructor*/
BitcoinExchange::BitcoinExchange()
{
}

/*copy constructor*/
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	*this = other;
}

/*assignment operator*/
BitcoinExchange&	BitcoinExchange::operator= (const BitcoinExchange& other)
{
	if (this == &other)
		return (*this);
	return (*this);
}

/*destructor*/
BitcoinExchange::~BitcoinExchange()
{
}

/*Variables: default constructor*/
BitcoinExchange::Variables::Variables()
	: year(0), month(0), day(0), value(0), linenum(0)
{
}

/*Variables: copy constructor*/
BitcoinExchange::Variables::Variables(const Variables& other)
	: year(other.year), month(other.month), day(other.day), value(other.value), \
	linenum(other.linenum)
{
	*this = other;
}

/*Variables: assignment operator*/
BitcoinExchange::Variables&		BitcoinExchange::Variables::operator= (const Variables& other)
{
	if (this == &other)
		return (*this);
	this->istream.clear();
	this->line = other.line;
	this->year = other.year;
	this->month = other.month;
	this->day = other.day;
	this->value = other.value;
	this->linenum = other.linenum;
	this->linestream.clear();
	this->rateDatabase = other.rateDatabase;
	return (*this);
}

/*Variables: destructor*/
BitcoinExchange::Variables::~Variables()
{}

bool				BitcoinExchange::computeAndDisplay(const std::string& infile)
{
	t_vars		vars;

	try
	{
		vars.rateDatabase = ExchangeRateBase(__DATABASENAME, __DATABASEFILENAME);
	}
	catch(const std::exception& e)
	{
		return (false);
	}
	if (infile.empty())
		return (Libftpp::error("empty filename"));
	if (!BitcoinExchange::openFile(vars, infile))
		return (false);
	if (!BitcoinExchange::authFileHead(vars, infile))
		return (false);
	if (!BitcoinExchange::exchange(vars, infile))
		return (false);
	return (true);
}

bool				BitcoinExchange::openFile(t_vars& vars, const std::string& infile)
{
	try
	{
		vars.istream.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		vars.istream.open(infile.c_str(), std::ios_base::in);
		vars.istream.exceptions(std::ios_base::goodbit);
	}
	catch(const std::ifstream::failure& e)
	{
		Libftpp::error("failed to open \"" + infile + "\"");
		return (false);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		throw ;
	}
	return (true);
}

bool				BitcoinExchange::authFileHead(t_vars& vars, const std::string& infile)
{
	vars.line.clear();
	std::getline(vars.istream, vars.line);
	vars.linenum++;
	if (vars.istream.eof() && vars.line.empty())
		return (Libftpp::error("empty file \"" + infile + "\""), true);
	else if (!vars.istream && !vars.istream.eof())
		return (Libftpp::error(\
				"something went wrong on the read of the infile \"" \
				+ infile + "\"\nbadbit or failbit setted"));
	else if (vars.line != "date | value")
		return (Libftpp::error("invalid file header \"" \
						+ vars.line + "\""), true);
	return (true);
}

bool				BitcoinExchange::exchange(t_vars& vars, const std::string& infile)
{
	bool	fdbk;

	while (vars.istream)
	{
		fdbk = true;
		vars.line.clear();
		std::getline(vars.istream, vars.line);
		vars.linenum++;
		if (fdbk)
			fdbk = BitcoinExchange::checkContent(vars, infile);
		vars.linestream.clear();
		vars.linestream.str(vars.line);
		if (fdbk)
			fdbk = parseDataLine(vars, infile);
		if (fdbk)
			fdbk = exchange_op(vars);
	}
	return (true);
}

bool				BitcoinExchange::exchange_op(t_vars& vars)
{
	try
	{
		double		val;
		t_date		date(vars.year, vars.month, vars.day);
		
		val = vars.value * vars.rateDatabase.request(date);
		std::cout	<< vars.year << "-" << vars.month << "-" << vars.day \
					<< " => " << vars.value << " = " \
					<< val << std::endl;
	}
	catch(const std::exception& e)
	{
		// std::cerr << e.what() << '\n';
		return (false);
	}
	return (true);
}

bool				BitcoinExchange::checkContent(t_vars& vars, const std::string& infile)
{
	if (vars.istream && vars.line.empty())
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) + "\": empty line"));
	else if (vars.istream.eof())
		return (false);
	else if (!vars.istream)
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) \
						+ ": something went wrong while reading"));
	return (true);
}

bool				BitcoinExchange::parseDataLine(t_vars& vars, const std::string& infile)
{
	std::string			year;
	std::string			month;
	std::string			day;
	std::string			value;

	vars.linestream.clear();
	vars.linestream.str(vars.line);
	std::getline(vars.linestream, year, '-');
	std::getline(vars.linestream, month, '-');
	std::getline(vars.linestream, day, '|');
	std::getline(vars.linestream, value);
	if (!BitcoinExchange::parseYear(vars, year, infile))
		return (false);
	if (!BitcoinExchange::parseMonth(vars, month, infile))
		return (false);
	if (!BitcoinExchange::parseDay(vars, day, infile))
		return (false);
	if (!BitcoinExchange::parseValue(vars, value, infile))
		return (false);
	return (true);
}

bool				BitcoinExchange::parseYear(t_vars& vars, std::string& year, const std::string& infile)
{
	double	n;

	if (year.empty())
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) \
						+ ": empty year field"));
	if (!Libftpp::strIsInt(year))
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) \
						+ ": invalid year value format \"" \
						+ year + "\""));
	n = std::strtod(year.c_str(), NULL);
	if (n < -2147483648 || n > 2147483647)
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) \
						+ ": too large year value \"" \
						+ year + "\""));
	vars.year = n;
	return (true);
}

bool				BitcoinExchange::parseMonth(t_vars& vars, std::string& month, const std::string& infile)
{
	double	n;

	if (month.empty())
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) \
						+ ": empty month field"));
	if (!Libftpp::strIsInt(month))
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) \
						+ ": invalid month value format \"" \
						+ month + "\""));
	n = std::strtod(month.c_str(), NULL);
	if (n < -2147483648 || n > 2147483647)
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) \
						+ ": too large month value \"" \
						+ month + "\""));
	if (n < 1 || n > 12)
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) \
						+ ": invalid month value \"" \
						+ month + "\""));
	vars.month = n;
	return (true);
}

bool				BitcoinExchange::parseDay(t_vars& vars, std::string& day, const std::string& infile)
{
	double	n;

	Libftpp::trimEnd(day, " 	", 1);
	if (day.empty())
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) \
						+ ": empty day field"));
	if (!Libftpp::strIsInt(day))
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) \
						+ ": invalid day value format \"" \
						+ day + "\""));
	n = std::strtod(day.c_str(), NULL);
	if (n < -2147483648 || n > 2147483647)
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) \
						+ ": too large day value \"" \
						+ day + "\""));
	if (n < 1 || n > 31)
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) \
						+ ": invalid day value \"" \
						+ day + "\""));
	vars.day = n;
	return (true);
}

bool				BitcoinExchange::parseValue(t_vars& vars, std::string& value, const std::string& infile)
{
	double	n;

	Libftpp::trimStart(value, " 	", 1);
	if (value.empty())
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) \
						+ ": empty bitcoin value field"));
	if (!Libftpp::strIsInt(value) && !Libftpp::strIsFloat(value) \
			&& !Libftpp::strIsDouble(value))
	{
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) \
						+ ": invalid bitcoin value format \"" \
						+ value + "\""));
	}
	n = std::strtod(value.c_str(), NULL);
	if (n > 1000)
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) \
						+ ": too large bitcoin value \"" \
						+ value + "\""));
	if (n < 0)
		return (Libftpp::error("\"" + infile + "\":" + " at line " \
						+ Libftpp::itoa(vars.linenum) \
						+ ": bitcoin value not a positive number \"" \
						+ value + "\""));
	vars.value = n;
	return (true);
}
