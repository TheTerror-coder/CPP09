/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Libftpp.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:38:13 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/23 17:57:51 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIBFTPP_HPP
# define	LIBFTPP_HPP

#include <iostream>
#include <cstdlib>
#include <string>

class Libftpp
{
	public:

		Libftpp(const Libftpp& other);
		Libftpp&	operator= (const Libftpp& other);
		~Libftpp();

		static std::string	itoa(const size_t& n);

	private:

		Libftpp();
};

#endif
/* ************************************************************************** */