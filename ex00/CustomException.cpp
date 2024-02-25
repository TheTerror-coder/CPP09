/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CustomException.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:51:50 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/25 15:38:39 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "CustomException.hpp"

CustomException::CustomException()
{
}

CustomException::CustomException(const CustomException& other)
{
	*this = other;
}

CustomException&	CustomException::operator= (const CustomException& other)
{
	(void)	other;
	return (*this);
}

CustomException::~CustomException()
{
}

const char*		CustomException::InfileErrorException::what() const throw()
{
	return ("InfileErrorException thrown");
}

const char*		CustomException::SyntaxErrorException::what() const throw()
{
	return ("SyntaxErrorException thrown");
}

const char*		CustomException::EmptyDatabaseException::what() const throw()
{
	return ("EmptyDatabaseException thrown");
}

const char*		CustomException::DatabaseException::what() const throw()
{
	return ("ErrorDatabaseException thrown");
}

bool			CustomException::error(const std::string& msg)
{
	std::cerr << "Error: " << msg << std::endl;
	return (false);
}
