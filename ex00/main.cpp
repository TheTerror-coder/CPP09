/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:51:53 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/26 17:11:20 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>
#include "BitcoinExchange.hpp"

int	main(const int argc, const char **argv)
{
	if (argc != 2)
		return (std::cerr << "argument fault, " \
				<< "this program takes one input file name as argument"
				<< std::endl, 1);
	try
	{
		BitcoinExchange::computeAndDisplay(argv[1]);
	}
	catch(const std::exception& e)
	{
		// std::cerr << "Error: " << e.what() << '\n';
	}
	return (0);
}
