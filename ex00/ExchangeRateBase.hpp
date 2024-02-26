/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExchangeRateBase.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:43:38 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/26 16:17:17 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef	EXCHANGERATEBASE_HPP
# define	EXCHANGERATEBASE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <exception>
# include <map>
# include "libftpp/Libftpp.hpp"
# include "Include.h"
# include "Date.hpp"
# include "CustomException.hpp"

typedef class ExchangeRateBase	t_ExchangeRateBase;

/*throws exceptions on  error*/
class ExchangeRateBase
{
	public:

		ExchangeRateBase();
		ExchangeRateBase(const std::string& name, const std::string& filename);
		ExchangeRateBase(const ExchangeRateBase& other);
		ExchangeRateBase&	operator= (const ExchangeRateBase& other);
		~ExchangeRateBase();

		void				setName(const std::string& name);
		const std::string&	getName(void) const;
		const std::string&	getFilename(void) const;
		/*prints the first 10 elements of the database on the standard output*/
		void				head(void);
		/*searchs the exchange rate at "date" on the database and return it, 
		**it may throw exception*/
		double				request(const t_date& date);

	private:
	
		
		std::string										name;
		std::map<t_date,double, std::greater<t_date> >	database;
		std::ifstream									istream;
		std::string										filename;
		std::string										line;
		std::string										year;
		std::string										month;
		std::string										day;
		std::string										exchange_rate;
		size_t											linenum;
		std::istringstream								linestream;

		void											setFilename(const std::string& filename);
		/*authenticates the name of the file*/
		void											parseFilename(void);
		/*opens the file 'filename' on a private input stream 'istream'*/
		void											openFile(void);
		/*authenticate the database file head*/
		void											authFileHead(void);
		void											checkContent(void);
		void											parseDataLine(void);
		/*loops on the file and extract datas to build the database,
		**throws exception on error*/
		void											buildDatabase(void);
		
};

#endif