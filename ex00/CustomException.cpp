/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CustomException.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:51:50 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/23 18:44:30 by TheTerror        ###   ########lyon.fr   */
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
