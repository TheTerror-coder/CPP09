/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:51:53 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/13 20:14:29 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"

int	main(const int argc, const char** argv)
{
	if (argc < 2)
	{
		std::cerr	<< "argument fault, expecting " \
					<< "an inverted Polish mathematical expression"\
					<< std::endl;
		return (1);
	}
	if (!RPN::calculate(&argv[1]))
		return (1);
	return (0);
}
