/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Libftpp.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:38:13 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/24 20:31:16 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIBFTPP_HPP
# define	LIBFTPP_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <fstream>
#include <cstdlib>
#include <string>

class Libftpp
{
	public:

		Libftpp(const Libftpp& other);
		Libftpp&	operator= (const Libftpp& other);
		~Libftpp();

		static std::string		itoa(const size_t& n);
		static std::string&		trimStart(std::string& str, const std::string& set);
		static std::string&		trimEnd(std::string& str, const std::string& set);
		static std::string&		trim(std::string& str, const std::string& set);
		static std::string&		removeChars(std::string& str, const std::string& set);
		static bool				strIsWSpaces(const std::string& str);
		static bool				authFileExtension(const std::string& filename, \
								const std::string& extension, std::string& errorfield);
		static bool				strIsDouble(std::string str);
		static std::string		strToLower(std::string str);
		static bool				strIsInt(std::string str);
		static bool				strIsFloat(std::string str);

	private:

		Libftpp();
};

#endif
/* ************************************************************************** */