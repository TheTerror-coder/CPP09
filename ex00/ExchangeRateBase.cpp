/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExchangeRateBase.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:48:43 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/26 16:49:22 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ExchangeRateBase.hpp"

/*default constructor*/
ExchangeRateBase::ExchangeRateBase() : linenum(0)
{
}

/*parametric constructor*/
ExchangeRateBase::ExchangeRateBase(const std::string& name, const std::string& filename) \
	: name(name), filename(filename), linenum(0)
{
	parseFilename();
	openFile();
	try
	{
		std::getline(this->istream, this->line, '\n');
		this->linenum++;
		authFileHead();
		this->line.clear();
		if (this->istream)
			std::getline(this->istream, this->line, '\n');
		this->linenum++;
		checkContent();
		buildDatabase();
	}
	catch(const t_DateErrorException& e)
	{
		Libftpp::errorThrow<t_DateErrorException>(this->filename, this->linenum, e);
	}
	catch(const std::ifstream::failure& e)
	{
		std::cerr << "Error: \"" << filename << "\", " << e.what() << '\n';
		throw;
	}
	catch(const std::exception& e)
	{
		throw;
	}
}

/*copy constructor*/
ExchangeRateBase::ExchangeRateBase(const ExchangeRateBase& other)
	: name(other.name), database(other.database), filename(other.filename), line(other.line), \
	year(other.year), month(other.month), day(other.day), \
	exchange_rate(other.exchange_rate), linenum(other.linenum)
{
	*this = other;
}

/*assignment operator*/
ExchangeRateBase&	ExchangeRateBase::operator= (const ExchangeRateBase& other)
{
	this->name = other.name;
	this->database = other.database;
	this->istream.clear();
	this->filename = other.filename;
	this->line = other.line;
	this->year = other.year;
	this->month = other.month;
	this->day = other.day;
	this->exchange_rate = other.exchange_rate;
	this->linenum = other.linenum;
	this->linestream.clear();
	return (*this);
}

/*destructor*/
ExchangeRateBase::~ExchangeRateBase()
{}

void				ExchangeRateBase::setName(const std::string& name)
{
	this->name = name;
}

void				ExchangeRateBase::setFilename(const std::string& filename)
{
	this->filename = filename;
}

const std::string&	ExchangeRateBase::getName(void) const
{
	return (this->name);
}

const std::string&	ExchangeRateBase::getFilename(void) const
{
	return (this->filename);
}

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

double			ExchangeRateBase::request(const t_date& date)
{
	std::map<t_date,double, std::greater<t_date> >::iterator	it;
	double													exc_rate;

	if (this->database.empty() && this->name.empty())
		Libftpp::errorThrow<t_EmptyDatabaseException>(\
				"an unnamed database is empty");
	else if (this->database.empty())
		Libftpp::errorThrow<t_EmptyDatabaseException>(\
				"the database \"" + this->name +  "\" is empty");
	it = this->database.lower_bound(date);
	if (it == this->database.end())
		Libftpp::errorThrow<t_DatabaseException>(\
				"unfound exchange rate in the database \"" \
				+ this->name +  "\"");
	exc_rate = it->second;
	return (exc_rate);
}

void			ExchangeRateBase::parseFilename(void)
{
	std::string		errorfield;
	
	if (!Libftpp::authFileExtension(this->filename, "csv", errorfield))
		Libftpp::errorThrow<t_InfileErrorException>(this->filename, errorfield);
}

void			ExchangeRateBase::openFile(void)
{
	try
	{
		this->istream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		this->istream.open(this->filename.c_str(), std::ios_base::in);
		this->istream.exceptions(std::ifstream::goodbit);
	}
	catch(const std::ifstream::failure& e)
	{
		Libftpp::errorThrow<std::ifstream::failure>(\
				"failed to open \"" + this->filename + "\"", e);
	}
	if (!this->istream.good())
		Libftpp::errorThrow<t_InfileErrorException>(\
				"something went wrong when opening \"" + this->filename + "\"");
}

void			ExchangeRateBase::authFileHead(void)
{
	if (this->istream.eof() && this->line.empty())
		Libftpp::errorThrow<t_InfileErrorException>(\
				"empty file \"" + this->filename + "\"");
	else if (!this->istream)
		Libftpp::errorThrow<t_InfileErrorException>(\
				"something went wrong on the read of the infile \"" \
				+ this->filename + "\"\nbadbit or failbit setted");
	else if (this->line != "date,exchange_rate")
		Libftpp::errorThrow<t_SyntaxErrorException>(\
				"invalid file header \"" + this->line + "\"");
}

void			ExchangeRateBase::checkContent(void)
{
	if (this->istream.eof() && this->line.empty())
		Libftpp::errorThrow<t_InfileErrorException>(\
				"\"" + this->filename \
				+ "\": empty database");
	else if (!this->istream)
		Libftpp::errorThrow<t_InfileErrorException>(\
				"something went wrong on the read of the infile \"" \
				+ this->filename + "\"\nbadbit or failbit setted");
}

void			ExchangeRateBase::buildDatabase(void)
{
	t_date	date;
	double	exc_rate;
	
	exc_rate = 0;
	while (this->istream && !this->line.empty())
	{
		parseDataLine();
		date = t_date(this->year, this->month, this->day);
		exc_rate = std::strtod(this->exchange_rate.c_str(), NULL);
		if (exc_rate < 0)
			Libftpp::errorThrow<t_SyntaxErrorException>(\
			this->filename, this->linenum, "exchange rate cannot be negative");
		this->database.insert(std::pair<t_date, double>(date, exc_rate));
		this->line.clear();
		std::getline(this->istream, this->line, '\n');
		this->linenum++;
	}
	if (this->istream)
		Libftpp::errorThrow<t_SyntaxErrorException>(this->filename, \
				this->linenum, "empty line");
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
		Libftpp::errorThrow<t_SyntaxErrorException>(this->filename, this->linenum,\
				"empty year field");
	if (this->month.empty())
		Libftpp::errorThrow<t_SyntaxErrorException>(this->filename, this->linenum,\
				"empty month field");
	if (this->day.empty())
		Libftpp::errorThrow<t_SyntaxErrorException>(this->filename, this->linenum,\
				"empty day field");
	if (this->exchange_rate.empty())
		Libftpp::errorThrow<t_SyntaxErrorException>(this->filename, this->linenum,\
				"empty exchange rate field");
	if (!Libftpp::strIsInt(this->exchange_rate) && !Libftpp::strIsFloat(this->exchange_rate) \
			&& !Libftpp::strIsDouble(this->exchange_rate))
	{
		Libftpp::errorThrow<t_SyntaxErrorException>(this->filename, this->linenum,\
				"invalid exchange rate format \"" + this->exchange_rate + "\"");
	}
}
