/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:51:53 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/23 19:02:56 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// #include <iomanip>
// #include <iostream>
// #include <fstream>
// #include <exception>
 
// int main()
// {
// 	try
// 	{
	
// 		std::ifstream stream;
// 		std::istringstream linestream;
	
// 		stream.open("test.csv", std::ios::in);
		
// 		std::string exchange_rate;
// 		std::string line;
// 		std::string year;
// 		std::string month;
// 		std::string day;
	
// 		stream >> line;
// 		std::cout << line << std::endl;
// 		stream >> line;
// line.clear();
// 		linestream = std::istringstream(line);
// 		std::getline(linestream, year, '-');
// 		std::cout << year << std::endl;
// 		std::getline(linestream, month, '-');
// 		std::cout << month << std::endl;
// 		std::getline(linestream, day, '-');
// 		std::cout << day << std::endl;
// 	}
// 	catch(const std::exception& e)
// 	{
// 		std::cerr << "Exception: " << e.what() << '\n';
// 	}
// }

#include <fstream>
#include <vector>
#include <list>
#include <stack>
#include <ctime>
#include "Date.hpp"
#include "libftpp/Libftpp.hpp"
#include "ExchangeRateBase.hpp"
#include <iostream>
#include <exception>



int	main(void)
{
	try
	{
		std::ifstream	is("test.csv", std::ios::in);
		ExchangeRateBase	rate_base(is, "test.csv");
		
		rate_base.head();
	}
	catch(const std::exception& e)
	{
		// std::cerr << "Error: " << e.what() << '\n';
	}
	// const size_t	n = 184467440000000UL;

	// std::cout << Libftpp::itoa(n) << std::endl;
	return (0);
}