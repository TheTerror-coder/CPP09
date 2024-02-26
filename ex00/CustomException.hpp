/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CustomException.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:49:52 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/26 16:33:01 by TheTerror        ###   ########lyon.fr   */
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

		class	EmptyDatabaseException : public std::exception
		{
			public:
				virtual const char*		what() const throw();
		};
		
		class	DatabaseException : public std::exception
		{
			public:
				virtual const char*		what() const throw();
		};
		
	private:
	
		CustomException();

};

#endif