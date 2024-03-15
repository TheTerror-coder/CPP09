/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:43:22 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/15 15:30:51 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*default constructor*/
PmergeMe::PmergeMe()
{
}

/*copy constructor*/
PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
}

/*assignment operator*/
PmergeMe&	PmergeMe::operator= (const PmergeMe& other)
{
	if (this == &other)
		return (*this);
	return (*this);
}

/*destructor*/
PmergeMe::~PmergeMe()
{
}

bool		PmergeMe::mergeInsert(const char** argv)
{
	std::string		args;

	for (size_t i = 1; argv[i]; i++)
		args = args + " " + argv[i];
	if (!PmergeMe::mergeInsert(args))
		return (false);
	return (true);
}

/*parses obviously the integers sequence passed to the main program
* then sorts the obtained sequence*/
bool		PmergeMe::mergeInsert(const std::string& argv)
{
	t_vvars			vvars;
	t_lvars			lvars;
	std::clock_t	_start = -1;
	std::clock_t	_end = -1;

	try
	{
		_start = std::clock();
		if (_start < 0)
			return (Libftpp::error("failure in std::clock()"));
		PmergeMe::withAVector(vvars, argv);
		_end = std::clock();
		if (_end < 0)
			return (Libftpp::error("failure in std::clock()"));
		vvars.vectorTime = (1000000.0 * (_end - _start)) / CLOCKS_PER_SEC;

		_start = -1;
		_end = -1;
		_start = std::clock();
		if (_start < 0)
			return (Libftpp::error("failure in std::clock()"));
		PmergeMe::withAList(lvars, argv);
		_end = std::clock();
		if (_end < 0)
			return (Libftpp::error("failure in std::clock()"));
		lvars.listTime = (1000000.0 * (_end - _start)) / CLOCKS_PER_SEC;
		PmergeMe::display(vvars, lvars);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (false);
	}
	return (true);
}

bool		PmergeMe::display(t_vvars& vvars, t_lvars& lvars)
{
	std::string			elm;
	std::istringstream	sstream;

	sstream.str(vvars.argv);
	std::cout << "Before :";
	while (sstream)
	{
		elm.clear();
		std::getline(sstream, elm, ' ');
		if (elm.size())
			std::cout << " " << elm;
	}
	std::cout << std::endl;
	
	std::cout << "After :";
	for (std::vector<unsigned>::iterator it = vvars.sorted.begin(); it != vvars.sorted.end(); it++)
		std::cout << " " << *it;
	std::cout << std::endl;
	
	std::cout << "Time to process a range of " << vvars.sorted.size() \
				<<  " elements with std::vector : " << vvars.vectorTime \
				<< " us" << std::endl;
	std::cout << "Time to process a range of " << lvars.sorted.size() \
				<<  " elements with std::list : " << lvars.listTime \
				<< " us" << std::endl;
	return (true);
}

/*checks formatting and convert from */
bool		PmergeMe::checkGetValue(double& val, const std::string& element)
{
	if (!Libftpp::strIsInt(element))
		return (Libftpp::error("\"" + element \
					+ "\", expecting a positive integer sequence"));
	val = std::strtod(element.c_str(), NULL);
	if (val < 0)
		return (Libftpp::error("\"" + element \
					+ "\", expecting a positive integer sequence"));
	if (val > std::numeric_limits<unsigned>::max())
		return (Libftpp::error("\"" + element \
					+ "\" overflowing"));
	return (true);
}
