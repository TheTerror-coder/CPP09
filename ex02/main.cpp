/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:51:53 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/15 15:37:16 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PmergeMe.hpp"

int	main(const int argc, const char** argv)
{
	if (argc < 2)
	{
		// Libftpp::error("argument fault, expecting a positive integer sequence");
		// return (1);
	}
	// if (!PmergeMe::mergeInsert(argv))
	// 	return (1);
PmergeMe::Vector_variables	var;

var.arr2dim.push_back(std::vector<unsigned>({85, 195}));
var.arr2dim.push_back(std::vector<unsigned>({845156, 9566232}));
var.arr2dim.push_back(std::vector<unsigned>({495225625}));

var.sorted.push_back(85);
var.sorted.push_back(195);
var.sorted.push_back(845156);
var.sorted.push_back(9566232);
var.sorted.push_back(495225625);

var.pendElms.push_back(5);
var.pendElms.push_back(5);
var.pendElms.push_back(5);
var.pendElms.push_back(5);
var.pendElms.push_back(5);

var.k = 8;
var.erased = 99;
var.argv = "";
var.argv = var.argv + "Hello wolrd" + argv[0];
var.vectorTime = 0.44;

{
	PmergeMe::Vector_variables	test;
	test = var;
}
// return (0);

std::cout << "VECTOR PART" << std::endl;
for (std::vector<std::vector<unsigned> >::iterator it = var.arr2dim.begin(); it != var.arr2dim.end(); it++)
{
	std::cout << it->at(0);
	if (it->size() == 2)
		std::cout << " | " << it->at(1) << std::endl;
	else
		std::cout << std::endl;
}
std::cout << "----------" << std::endl;
for (std::vector<unsigned>::iterator it = var.sorted.begin(); it != var.sorted.end(); it++)
	std::cout << *it << " ";
std::cout << std::endl;
for (std::vector<unsigned>::iterator it = var.pendElms.begin(); it != var.pendElms.end(); it++)
	std::cout << *it << " ";
std::cout << std::endl;
std::cout << "----------" << std::endl;
std::cout << "----------" << std::endl;
for (std::vector<unsigned>::iterator it = var.sorted.begin(); it != var.sorted.end(); it++)
	std::cout << *it << " ";
std::cout << std::endl;
for (std::vector<unsigned>::iterator it = var.pendElms.begin(); it != var.pendElms.end(); it++)
	std::cout << *it << " ";
std::cout << std::endl;
std::cout << "----------" << std::endl;
	return (0);
}
