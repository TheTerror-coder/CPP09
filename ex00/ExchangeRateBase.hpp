/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExchangeRateBase.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:43:38 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/24 20:43:36 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef	EXCHANGERATEBASE_HPP
# define	EXCHANGERATEBASE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <iomanip>
# include <exception>
# include <map>
# include "libftpp/Libftpp.hpp"
# include "Include.h"
# include "Date.hpp"
# include "CustomException.hpp"

class ExchangeRateBase
{
	public:

		ExchangeRateBase(const std::string& filename);
		ExchangeRateBase(const ExchangeRateBase& other);
		ExchangeRateBase&	operator= (const ExchangeRateBase& other);
		~ExchangeRateBase();

		void	head(void);

	private:
	
		ExchangeRateBase();
		
		std::map<t_date,double>		database;
		std::ifstream				istream;
		std::string					filename;
		std::string					line;
		std::string					year;
		std::string					month;
		std::string					day;
		std::string					exchange_rate;
		size_t						linenum;
		std::istringstream			linestream;

		void						parseFilename(void);
		void						openFile(void);
		void						authFileHead(void);
		void						checkDatabase(void);
		void						parseDataLine(void);
		
};

#endif