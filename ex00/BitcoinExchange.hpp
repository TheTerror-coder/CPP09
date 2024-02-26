/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:07:10 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/26 16:17:24 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef	BITCOINEXCHANGE_HPP
# define	BITCOINEXCHANGE_HPP

# define	__DATABASENAME "database_1.0"
# define	__DATABASEFILENAME "data.csv"

# include <iostream>
# include <fstream>
# include <sstream>
# include "Include.h"
# include "libftpp/Libftpp.hpp"
# include "CustomException.hpp"
# include "ExchangeRateBase.hpp"

class BitcoinExchange
{
	public:
	
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange&	operator= (const BitcoinExchange& other);
		~BitcoinExchange();

		static bool		computeAndDisplay(const std::string& infile);
	
	private:

		BitcoinExchange();

		struct Variables
		{
			public :
				
				Variables();
				Variables(const Variables& other);
				Variables&	operator=(const Variables& other);
				~Variables();

				std::ifstream		istream;
				std::string			line;
				int					year;
				int					month;
				int					day;
				double				value;
				size_t				linenum;
				std::istringstream	linestream;
				t_ExchangeRateBase	rateDatabase;
		};
		
		typedef struct Variables	t_vars;
		
		static bool				openFile(t_vars& vars, const std::string& infile);
		static bool				authFileHead(t_vars& vars, const std::string& infile);
		static bool				exchange(t_vars& vars, const std::string& infile);
		static bool				exchange_op(t_vars& vars);
		static bool				checkContent(t_vars& vars, const std::string& infile);
		static bool				parseDataLine(t_vars& vars, const std::string& infile);
		static bool				parseYear(t_vars& vars, std::string& year, const std::string& infile);
		static bool				parseMonth(t_vars& vars, std::string& month, const std::string& infile);
		static bool				parseDay(t_vars& vars, std::string& day, const std::string& infile);
		static bool				parseValue(t_vars& vars, std::string& value, const std::string& infile);

};

#endif
