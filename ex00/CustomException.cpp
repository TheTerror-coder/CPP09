/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CustomException.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:51:50 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/12 19:39:57 by TheTerror        ###   ########lyon.fr   */
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
	if (this == &other)
		return (*this);
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
