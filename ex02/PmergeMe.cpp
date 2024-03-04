/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:43:22 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/03 21:56:28 by TheTerror        ###   ########lyon.fr   */
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
PmergeMe	PmergeMe::operator= (const PmergeMe& other)
{
	(void)	other;
	return (*this);
}

/*destructor*/
PmergeMe::~PmergeMe()
{
}

PmergeMe::Vector_variables::Vector_variables()
{}

PmergeMe::Vector_variables::Vector_variables(const Vector_variables& other)
{
	*this = other;
}

PmergeMe::Vector_variables	PmergeMe::Vector_variables::operator= (const Vector_variables& other)
{
	(void)	other;
	return (*this);
}

PmergeMe::Vector_variables::~Vector_variables()
{}
PmergeMe::List_variables::List_variables()
{}

PmergeMe::List_variables::List_variables(const List_variables& other)
{
	*this = other;
}

PmergeMe::List_variables	PmergeMe::List_variables::operator= (const List_variables& other)
{
	(void)	other;
	return (*this);
}

PmergeMe::List_variables::~List_variables()
{}

bool		PmergeMe::mergeInsert(const char** argv)
{
	t_vvars		vars;

	if (!parseArgv(vars, argv))
		return (false);
	if (!sort(vars))
		return (false);
	return (true);
}

bool		PmergeMe::parseArgv(t_vvars& vars, const char** argv)
{
	double					val;
	std::vector<unsigned>	arr;

	val = -1;
	vars.arr2dim.clear();
	for (size_t i = 1; argv[i]; i++)
	{
		arr.clear();
		if (!checkGetValue(val, argv[i]))
			return (false);
		arr.push_back(val);
		if (argv[++i])
		{
			if (!checkGetValue(val, argv[i]))
				return (false);
			arr.push_back(val);
			vars.arr2dim.push_back(arr);
		}
		else
		{
			vars.arr2dim.push_back(arr);
			break ;
		}
	}
	return (true);
}

bool		PmergeMe::checkGetValue(double& val, const char* arg)
{
	if (!Libftpp::strIsInt(arg))
		return (Libftpp::error(std::string("\"") + arg \
					+ "\", expecting a positive integer sequence"));
	val = std::strtod(arg, NULL);
	if (val < 0)
		return (Libftpp::error(std::string("\"") + arg \
					+ "\", expecting a positive integer sequence"));
	if (val > std::numeric_limits<unsigned>::max())
		return (Libftpp::error(std::string("\"") + arg \
					+ "\" overflowing"));
	return (true);
}

bool		PmergeMe::sort(t_vvars& vars)
{
	try
	{
		if (!merge(vars))
			return (false);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (false);
	}
	return (true);
}

bool		PmergeMe::merge(t_vvars& vars)
{
	sortEachPair(vars);
for (std::vector<std::vector<unsigned> >::iterator it = vars.arr2dim.begin(); it != vars.arr2dim.end(); it++)
{
	std::cout << it->at(0);
	if (it->size() == 2)
		std::cout << " | " << it->at(1) << std::endl;
	else
		std::cout << std::endl;
}
	if (!sortPairs(vars))
		return (false);
std::cout << "----------" << std::endl;
for (std::vector<unsigned>::iterator it = vars.sorted.begin(); it != vars.sorted.end(); it++)
	std::cout << *it << " ";
std::cout << std::endl;
for (std::vector<unsigned>::iterator it = vars.pendElms.begin(); it != vars.pendElms.end(); it++)
	std::cout << *it << " ";
std::cout << std::endl;
std::cout << "----------" << std::endl;
	if (!insertPendElm(vars))
		return (false);
std::cout << "----------" << std::endl;
for (std::vector<unsigned>::iterator it = vars.sorted.begin(); it != vars.sorted.end(); it++)
	std::cout << *it << " ";
std::cout << std::endl;
for (std::vector<unsigned>::iterator it = vars.pendElms.begin(); it != vars.pendElms.end(); it++)
	std::cout << *it << " ";
std::cout << std::endl;
std::cout << "----------" << std::endl;
	return (true);
}

bool		PmergeMe::sortEachPair(t_vvars& vars)
{
	unsigned	tmp;
	
	for (std::vector<std::vector<unsigned> >::iterator it = vars.arr2dim.begin(); \
			it != vars.arr2dim.end(); it++)
	{
		if (it->size() > 1)
		{
			tmp = it->at(0);
			if (it->at(0) < it->at(1))
			{
				it->at(0) = it->at(1);
				it->at(1) = tmp;
			}
		}
	}
	return (true);
}

bool		PmergeMe::sortPairs(t_vvars& vars)
{
	if (vars.arr2dim.size() && vars.arr2dim.begin()->size())
	{
		vars.sorted.push_back(vars.arr2dim.begin()->at(0));
		vars.pendElms.push_back(vars.arr2dim.begin()->at(1));
	}
	for (std::vector<std::vector<unsigned> >::iterator it = vars.arr2dim.begin() + 1; \
			it != vars.arr2dim.end(); it++)
	{
		if (it->size() > 1)
		{
			if (!insertFirstElm(vars, it->at(0), it->at(1)))
				return (false);
		}
		else if (it->size() == 1)
			vars.pendElms.push_back(it->at(0));
	}
	return (true);
}

bool		PmergeMe::insertFirstElm(t_vvars& vars, unsigned& elm1, unsigned& elm2)
{
	std::vector<unsigned>::iterator 	start;
	std::vector<unsigned>::iterator 	end;
	
	start = vars.sorted.begin();
	end = vars.sorted.end() - 1;
	if (elm1 <= *start)
		return (vars.sorted.insert(start, elm1), \
				vars.pendElms.insert(vars.pendElms.begin(), elm2), true);
	if (elm1 >= *end)
		return (vars.sorted.push_back(elm1), \
				vars.pendElms.push_back(elm2), true);
	for (std::vector<unsigned>::iterator it1 = start, it2 = vars.pendElms.begin(); \
			it1 != vars.sorted.end(); it1++, it2++)
	{
		if (elm1 <= *it1)
			return (vars.sorted.insert(it1, elm1), \
					vars.pendElms.insert(it2, elm2), true);
	}
	return (false);
}

bool		PmergeMe::insertPendElm(t_vvars& vars)
{
	std::vector<unsigned>::iterator 	start;
	std::vector<unsigned>::iterator 	end;
	
	vars.erased = 0;
	start = vars.sorted.begin();
	end = vars.sorted.end() - 1;
	vars.sorted.insert(vars.sorted.begin(), vars.pendElms.at(0));
	vars.pendElms.erase(vars.pendElms.begin());
	vars.erased++;
	insertFollowingJacobsthal(vars);
/*
	for (std::vector<unsigned>::iterator it2 = vars.secondElms.begin(); \
			it2 != vars.secondElms.end(); it2++)
	{
		for (std::vector<unsigned>::iterator it1 = start; \
				it1 != vars.sorted.end(); it1++, it2++)
		{
			if (elm1 < *it1)
				return (vars.sorted.insert(it1, elm1), \
						vars.secondElms.insert(it2, elm2), true);
			if (*it1 == elm1)
				return (Libftpp::error("found duplicated values of \"" \
								+ Libftpp::itoa(static_cast<size_t>(elm1)) + "\""));
		}
	}
*/
	return (true);
}

bool		PmergeMe::insertFollowingJacobsthal(t_vvars& vars)
{
	vars.k = 3;
	for (size_t	i = jacobsthalNumber(vars.k) - vars.erased - 1; \
			i < vars.pendElms.size(); i = jacobsthalNumber(vars.k) - vars.erased - 1)
	{
		insert_op(vars, vars.pendElms.at(i));
		vars.pendElms.erase(vars.pendElms.begin() + i);
		
		for (size_t x = jacobsthalNumber(vars.k) - vars.erased - 2;	\
				x + vars.erased + 1 > jacobsthalNumber(vars.k - 1) \
				&& x < vars.pendElms.size(); x--)
		{
			insert_op(vars, vars.pendElms.at(x));
			vars.pendElms.erase(vars.pendElms.begin() + (x));
			vars.erased++;
		}
		vars.erased++;
		vars.k++;
// std::cout << "x ************* " << x << std::endl;
// std::cout << "jacob k - 1 ::: "  << jacobsthalNumber(vars.k - 1) << std::endl;
// std::cout << "erased ++++++++ "  << vars.erased << std::endl;
	}
	return (true);
}

size_t	PmergeMe::jacobsthalNumber(size_t k)
{
	return ((std::pow(2, k) - std::pow(-1, k)) / 3);
}

bool		PmergeMe::insert_op(t_vvars& vars, unsigned elm)
{
	std::vector<unsigned>::iterator 	start;
	std::vector<unsigned>::iterator 	end;
	
	start = vars.sorted.begin();
	end = vars.sorted.end() - 1;
	if (elm <= *start)
		return (vars.sorted.insert(start, elm), true);
	if (elm >= *end)
		return (vars.sorted.push_back(elm), true);
	for (std::vector<unsigned>::iterator it = start; \
			it != vars.sorted.end(); it++)
	{
		if (elm <= *it)
			return (vars.sorted.insert(it, elm), true);
	}
	return (false);
}