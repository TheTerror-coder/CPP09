/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExchangeRateBase.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:48:43 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/23 19:53:15 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ExchangeRateBase.hpp"

/*default constructor*/
ExchangeRateBase::ExchangeRateBase() : linenum(0)
{}
/*parametric constructor*/
ExchangeRateBase::ExchangeRateBase(std::ifstream& is, const std::string& filename) \
	: filename(filename), linenum(0)
{
	if (!is.good())
		CustomException::errorThrow<t_InfileErrorException>(\
				"empty file \"" + this->filename + "\"");
	try
	{

		std::getline(is, this->line, '\n');
		this->linenum++;
		authFileHead(is);
// int i = 0;
		this->line.clear();
		if (is)
			std::getline(is, this->line, '\n');
		this->linenum++;
		checkDatabase(is);
		while (is && !this->line.empty())
		{
// i++;
			parseDataLine();
// std::cout << t_date(this->year, this->month, this->day) << std::endl;
			this->database.insert(\
				std::pair<t_date, double>(\
					t_date(this->year, this->month, this->day), \
					std::strtod(this->exchange_rate.c_str(), NULL)));
			this->line.clear();
			std::getline(is, this->line, '\n');
			this->linenum++;
		}
		if (is)
			CustomException::errorThrow<t_SyntaxErrorException>(this->filename, this->linenum, \
					"empty line");
// std::cout << "***looped : " << i << " times" << std::endl;
	}
	catch(const t_DateErrorException& e)
	{
		CustomException::errorThrow<t_DateErrorException>(this->filename, this->linenum, e);
	}
	catch(const std::exception& e)
	{
		throw;
	}
}

/*copy constructor*/
ExchangeRateBase::ExchangeRateBase(const ExchangeRateBase& other)
	: database(other.database), filename(other.filename), line(other.line), \
	year(other.year), month(other.month), day(other.day), \
	exchange_rate(other.exchange_rate), linenum(other.linenum)
{
	*this = other;
}

/*assignment operator*/
ExchangeRateBase&	ExchangeRateBase::operator= (const ExchangeRateBase& other)
{
	this->database = other.database;
	this->filename = other.filename;
	this->line = other.line;
	this->year = other.year;
	this->month = other.month;
	this->day = other.day;
	this->exchange_rate = other.exchange_rate;
	this->linenum = other.linenum;
	return (*this);
}
/*destructor*/
ExchangeRateBase::~ExchangeRateBase()
{}

void			ExchangeRateBase::head(void)
{
	int	i;

	i = 0;
	for (std::map<t_date, double>::iterator it = this->database.begin(); \
			it != this->database.end() && i < 10; ++it)
	{
		std::cout << it->first << "," << it->second << std::endl;
		i++;
	}
std::cout << "***looped : " << i << " times" << std::endl;
}

void			ExchangeRateBase::authFileHead(std::ifstream& is)
{
	if (is.eof() && this->line.empty())
		CustomException::errorThrow<t_InfileErrorException>(\
				"empty file \"" + this->filename + "\"");
	else if (!is)
		CustomException::errorThrow<t_InfileErrorException>(\
				"something went wrong on the read of the infile \"" \
				+ this->filename + "\"\nbadbit or failbit setted");
	else if (this->line != "date,exchange_rate")
		CustomException::errorThrow<t_SyntaxErrorException>(\
				"invalid file header \"" + this->line + "\"");
}

void			ExchangeRateBase::checkDatabase(std::ifstream& is)
{
	if (is.eof() && this->line.empty()) // check not empty this->line
		CustomException::errorThrow<t_InfileErrorException>(\
				"exchange rate database \"" + this->filename \
				+ "\" is empty");
	else if (!is) // check not stream error
		CustomException::errorThrow<t_InfileErrorException>(\
				"something went wrong on the read of the infile \"" \
				+ this->filename + "\"\nbadbit or failbit setted");
}

void			ExchangeRateBase::parseDataLine(void)
{
	this->linestream.clear();
	this->linestream.str(this->line);
	std::getline(this->linestream, this->year, '-');
	std::getline(this->linestream, this->month, '-');
	std::getline(this->linestream, this->day, ',');
	std::getline(this->linestream, this->exchange_rate);
	if (this->year.empty())
		CustomException::errorThrow<t_SyntaxErrorException>(this->filename, this->linenum,\
				"empty year field");
	if (this->month.empty())
		CustomException::errorThrow<t_SyntaxErrorException>(this->filename, this->linenum,\
				"empty month field");
	if (this->day.empty())
		CustomException::errorThrow<t_SyntaxErrorException>(this->filename, this->linenum,\
				"empty day field");
	if (this->exchange_rate.empty())
		CustomException::errorThrow<t_SyntaxErrorException>(this->filename, this->linenum,\
				"empty exchange rate field");
	if (!strIsInt(this->exchange_rate) && !strIsFloat(this->exchange_rate) \
			&& !strIsDouble(this->exchange_rate))
	{
		CustomException::errorThrow<t_SyntaxErrorException>(this->filename, this->linenum,\
				"invalid exchange rate format \"" +this->exchange_rate + "\"");
	}
}

bool			ExchangeRateBase::strIsDouble(std::string str)
{
	size_t	i;

	i = 0;
	str = strToLower(str);
	if (str.empty())
		return (false);
	if (str == "-inf" || str == "nan" || str == "+inf" || str == "inf")
		return (true);
	if (str == ".")
		return (false);
	if (str.at(i) == '-' || str.at(i) == '+')								// (optional) plus or minus sign 
		i++;
	if (i < str.size() && str.at(i) == '.' && i + 1 < str.size() && !std::isdigit(str.at(i + 1)))
		return (false);
	for (i = i; i < str.size() && std::isdigit(str.at(i)); i++)				// nonempty sequence of decimal digits
	{}
	if (i >= str.size() || str.at(i) != '.' )								// decimal-point character 
		return (false);
	for (i += 1; i < str.size() && std::isdigit(str.at(i)); i++)			// nonempty sequence of decimal digits
	{}
	if (i < str.size() && str.at(i) == 'e')									// (optional) 'e' or 'E' defining exponent to base 10)
	{
		i++;
		if (i < str.size() && (str.at(i) == '+' || str.at(i) == '-'))		// (optional) plus or minus exponent sign
			i++;
		if (i < str.size() && std::isdigit(str.at(i)))
		{
			for (i += 1; i < str.size() && std::isdigit(str.at(i)); i++)	// nonempty sequence of decimal digits
			{}
		}
		else
			return (false);
	}
	if (i >= str.size())
		return (true);
	return (false);
}


std::string		ExchangeRateBase::strToLower(std::string str)
{
	std::string		lowstr;

	lowstr = str;
	if (str.empty())
		return (str);
	for (size_t i = 0; i < str.size(); i++)
		lowstr[i] = std::tolower(str.at(i));
	return (lowstr);
}

bool			ExchangeRateBase::strIsInt(std::string str)
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

bool			ExchangeRateBase::strIsFloat(std::string str)
{
	size_t	i;

	i = 0;
	str = strToLower(str);
	if (str.empty())
		return (false);
	if (str == "-inff" || str == "nanf" || str == "+inff" || str == "inff")
		return (true);
	if (str == "f" || str == "+f" || str == "-f")
		return (true);
	if (str == ".f" || !str.compare(0, 2, ".e"))
		return (false);
	if (str.at(i) == '-' || str.at(i) == '+')						// (optional) plus or minus sign 
		i++;
	if (i >= str.size() || (!std::isdigit(str.at(i)) && str.at(i) != '.'))
		return (false);
	for (i = i; i < str.size() && std::isdigit(str.at(i)); i++)		// nonempty sequence of decimal digits
	{}
	if (i >= str.size() || str.at(i) != '.')						// decimal-point character 
		return (false);
	for (i += 1; i < str.size() && std::isdigit(str.at(i)); i++)	// nonempty sequence of decimal digits
	{}
	if (i < str.size() && str.at(i) == 'e')									// (optional) 'e' or 'E' defining exponent to base 10)
	{
		i++;
		if (i < str.size() && (str.at(i) == '+' || str.at(i) == '-'))		// (optional) plus or minus exponent sign
			i++;
		if (i < str.size() && std::isdigit(str.at(i)))
		{
			for (i += 1; i < str.size() && std::isdigit(str.at(i)); i++)	// nonempty sequence of decimal digits
			{}
		}
		else
			return (false);
	}
	if (i < str.size() && str.at(i) == 'f' && i + 1 >= str.size())			// character 'f' or 'F' specifying float-type
		return (true);
	return (false);
}
