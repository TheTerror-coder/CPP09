/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Date.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:51:15 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/23 18:31:58 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef	DATE_HPP
# define	DATE_HPP

# include <iostream>
# include <exception>
# include <map>
# include <cstdlib>

typedef	class Date	t_date;

class Date
{
	public :
	
		Date(int y, int m, int d);
		Date(int y, int m, int d, std::string dayofweek);
		Date(std::string y, std::string m, std::string d);
		Date(std::string y, std::string m, std::string d, std::string dayofweek);
		Date(const Date& other);
		Date&	operator=(const Date& other);
		~Date();

		int				getYear() const;
		int				getMonth() const;
		int				getDay() const;
		std::string		getDayOfWeek() const;
		void			setYear(int y);
		void			setMonth(int m);
		void			setDay(int d);
		void			setDayOfWeek(std::string d);

		bool			operator== (const t_date& rhs) const;
		bool			operator!= (const t_date& rhs) const;
		bool			operator< (const t_date& rhs) const;
		bool			operator> (const t_date& rhs) const;
		bool			operator<= (const t_date& rhs) const;
		bool			operator>= (const t_date& rhs) const;
		
		class	DateErrorException : public std::exception
		{
			public:
				const char* what() const throw();
		};
		
		class	InvalidDayOfWeekException : public DateErrorException
		{
			public:
				const char* what() const throw();
		};
		
		class	InvalidYearException : public DateErrorException
		{
			public:
				const char* what() const throw();
		};
		
		class	InvalidMonthException : public DateErrorException
		{
			public:
				const char* what() const throw();
		};
		
		class	InvalidDayException : public DateErrorException
		{
			public:
				const char* what() const throw();
		};


	private :
	
		Date();
	
		int											year;
		int											month;
		int											day;
		std::string									dayofweek;
		std::map<std::string, std::string>			weekdays_base;

		
		void					initWeekDaysBase(void);
		void					constructorRoutine(std::string& y, std::string& m, std::string& d);
		std::string				strToLower(std::string str);
		bool					strIsInt(std::string str);
};

std::ostream&	operator<< (std::ostream& os, const Date& rhs);

#endif