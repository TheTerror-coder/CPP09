/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:51:53 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/25 19:14:18 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>
#include "BitcoinExchange.hpp"

int	main(void)
{
	try
	{
		BitcoinExchange::computeAndDisplay("input.txt");
	}
	catch(const std::exception& e)
	{
		// std::cerr << "Error: " << e.what() << '\n';
	}
	return (0);
}