/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:51:53 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/03 20:14:59 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PmergeMe.hpp"

int	main(const int argc, const char** argv)
{
	if (argc < 2)
	{
		Libftpp::error("argument fault, expecting a positive integer sequence");
		return (1);
	}
	PmergeMe::mergeInsert(argv);
// (void) argc;
// (void) argv;
// std::cout << jacobsthalNumber(60) << std::endl;
	return (0);
}
