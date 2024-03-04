/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MathTools.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:34:05 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/04 15:36:19 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Libftpp.hpp"


size_t	Libftpp::jacobsthalNumber(size_t k)
{
	return ((std::pow(2, k) - std::pow(-1, k)) / 3);
}
