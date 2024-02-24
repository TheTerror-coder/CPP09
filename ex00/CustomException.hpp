/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CustomException.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:49:52 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/24 16:18:42 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CUSTOMEXCEPTION_HPP
# define	CUSTOMEXCEPTION_HPP

# include <iostream>
# include <string>
# include <exception>
# include "libftpp/Libftpp.hpp"

class CustomException
{
	public:
	
		CustomException(const CustomException& other);
		CustomException&	operator= (const CustomException& other);
		~CustomException();

		class	InfileErrorException : public std::exception
		{
			public:
				const char*		what() const throw();
		};
		
		class	SyntaxErrorException : public std::exception
		{
			public:
				virtual const char*		what() const throw();
		};

		template <typename Texception>
		static void			errorThrow(const std::string& msg);
		template <typename Texception>
		static void			errorThrow(const std::string& msg, const Texception& e);
		template <typename Texception>
		static void			errorThrow(const std::string& filename, \
										const std::string& msg);
		template <typename Texception>
		static void			errorThrow(const std::string& filename, \
										size_t linenumber, const std::string& msg);
		template <typename Texception>
		static void			errorThrow(const std::string& filename, \
										size_t linenumber, const Texception& e);
		
	private:
	
		CustomException();

};

template<typename Texception>
void			CustomException::errorThrow(const std::string& msg)
{
	try
	{
		throw(Texception());
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << msg << ", " << e.what() << '\n';
		throw;
	}
}

template<typename Texception>
void			CustomException::errorThrow(const std::string& msg, const Texception& e)
{
	std::cerr << "Error: " << msg << ", " << e.what() << '\n';
	throw;
}

template<typename Texception>
void			CustomException::errorThrow(const std::string& filename, \
		const std::string& msg)
{
	try
	{
		throw(Texception());
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: \"" << filename << "\": " << msg << ", " \
				<< e.what() << '\n';
		throw;
	}
}

template<typename Texception>
void			CustomException::errorThrow(const std::string& filename, \
		size_t linenumber, const std::string& msg)
{
	try
	{
		throw(Texception());
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: \"" << filename << "\": at line " \
				<< Libftpp::itoa(linenumber) << ": " << msg << ", " \
				<< e.what() << '\n';
		throw;
	}
}

template<typename Texception>
void			CustomException::errorThrow(const std::string& filename, \
		size_t linenumber, const Texception& e)
{
	std::cerr << "Error: \"" << filename << "\": at line " \
			<< Libftpp::itoa(linenumber) << ": " << e.what() << '\n';
	throw;
}

#endif