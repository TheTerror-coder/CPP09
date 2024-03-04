/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Libftpp.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:38:13 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/04 15:42:14 by TheTerror        ###   ########lyon.fr   */
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
# include <cmath>

class Libftpp
{
	public:

		Libftpp(const Libftpp& other);
		Libftpp&	operator= (const Libftpp& other);
		~Libftpp();
		
		/*considered signs: + - * / */
		static bool				isSign(const char c);
		static std::string		itoa(const size_t& n);
		static std::string&		trimStartSpaces(std::string& str);
		static std::string&		trimEndSpaces(std::string& str);
		static std::string&		trimSpaces(std::string& str);
		static std::string&		trimStart(std::string& str, const std::string& set);
		static std::string&		trimStart(std::string& str, const std::string& set, const size_t& nb);
		static std::string&		trimEnd(std::string& str, const std::string& set);
		static std::string&		trimEnd(std::string& str, const std::string& set, const size_t& nb);
		static std::string&		trim(std::string& str, const std::string& set);
		static std::string&		trim(std::string& str, const std::string& set, const size_t& nb);
		static std::string		replaceBySpace(std::string& str);
		static std::string&		removeChars(std::string& str, const std::string& set);
		static bool				strIsWSpaces(const std::string& str);
		static bool				authFileExtension(const std::string& filename, \
									const std::string& extension, std::string& errorfield);
		static std::string		strToLower(std::string str);
		static bool				strIsInt(std::string str);
		static bool				strIsFloat(std::string str);
		static bool				strIsDouble(std::string str);

		static std::string		putFloat(float f);
		static std::string		putDouble(double d);

		/*compute the k'th Jacobsthal number with k in range [1, ++[ and return the value*/
		static size_t			jacobsthalNumber(size_t k);
		template <typename Tdata>
		static Tdata			operation(const Tdata& lhs, const Tdata& rhs, const char opsign);
		
		/*prints error message on standard error output and returns false*/
		static bool				error(const std::string& msg);
		/*prints error message on standard error output then throws Texception*/
		template <typename Texception>
		static void				errorThrow(const std::string& msg);
		/*prints error message on standard error output then throws Texception 'e'*/
		template <typename Texception>
		static void				errorThrow(const std::string& msg, const Texception& e);
		/*prints error message on standard error output specifying the file's name
		* then throws Texception*/
		template <typename Texception>
		static void				errorThrow(const std::string& filename, \
										const std::string& msg);
		/*prints error message on standard error output specifying the file's name,
		* the number of line then throws Texception*/
		template <typename Texception>
		static void				errorThrow(const std::string& filename, \
										size_t linenumber, const std::string& msg);
		/*prints error message on standard error output specifying the file's name,
		* the number of line then throws Texception 'e'*/
		template <typename Texception>
		static void				errorThrow(const std::string& filename, \
										size_t linenumber, const Texception& e);

	private:

		Libftpp();
};

/*template function errorThrow()'s implementation*/
#include "Error.tpp"
#include "MathTools.tpp"

#endif
/* ************************************************************************** */