/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Libftpp.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:40:24 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/12 19:43:22 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Libftpp.hpp"

/*private default constructor*/
Libftpp::Libftpp()
{
}

/*copy constructor*/
Libftpp::Libftpp(const Libftpp& other)
{
	*this = other;
}

/*assignment operator*/
Libftpp&	Libftpp::operator= (const Libftpp& other)
{
	if (this == &other)
		return (*this);
	return (*this);
}

/*destructor*/
Libftpp::~Libftpp()
{
}
