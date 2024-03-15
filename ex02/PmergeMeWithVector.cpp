/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeWithVector.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:43:22 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/15 15:33:57 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/** *******************************std::VECTOR PART***************************************** **/

PmergeMe::Vector_variables::Vector_variables()
	: k(0), erased(0), vectorTime(0)
{
}

PmergeMe::Vector_variables::Vector_variables(const Vector_variables& other)
	: arr2dim(other.arr2dim), sorted(other.sorted), pendElms(other.pendElms), \
	k(other.k), erased(other.erased), argv(other.argv), vectorTime(other.vectorTime)
{
	*this = other;
}

PmergeMe::Vector_variables&		PmergeMe::Vector_variables::operator= (const Vector_variables& other)
{
	if (this == &other)
		return (*this);
	this->arr2dim = other.arr2dim;
	this->sorted = other.sorted;
	this->pendElms = other.pendElms;
	this->k = other.k;
	this->erased = other.erased;
	this->argv = other.argv;
	this->sstream.clear();
	this->vectorTime = other.vectorTime;
	return (*this);
}

PmergeMe::Vector_variables::~Vector_variables()
{
}

bool		PmergeMe::withAVector(t_vvars& vars, const std::string& argv)
{
	vars.argv = argv;
	Libftpp::replaceBySpace(vars.argv);
	Libftpp::trimSpaces(vars.argv);
	if (vars.argv.empty())
		return (Libftpp::error("empty sequence"));
	if (!parseArgv(vars))
		return (false);
	if (vars.arr2dim.empty() || vars.arr2dim.begin()->empty())
		return (true);
	if (!sort(vars))
		return (false);
	return (true);
}

bool		PmergeMe::parseArgv(t_vvars& vars)
{
	double					val;
	std::vector<unsigned>	arr;
	std::string				element;

	val = -1;
	vars.arr2dim.clear();
	vars.sstream.str(vars.argv);
	while (vars.sstream)
	{
		arr.clear();
		element.clear();
		std::getline(vars.sstream, element, ' ');
		if (element.size())
		{
			if (!checkGetValue(val, element))
				return (false);
			arr.push_back(val);
		element.clear();
		while (vars.sstream && !element.size())
		{
			element.clear();
			std::getline(vars.sstream, element, ' ');
			if (element.size())
			{
				if (!checkGetValue(val, element))
					return (false);
				arr.push_back(val);
			}
		}
		vars.arr2dim.push_back(arr);
		}
	}
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

/*implements the Ford-Johnson sorting algorithm*/
bool		PmergeMe::merge(t_vvars& vars)
{
	// return (PmergeMe::debugModeDisplayer(vars));
	sortEachPair(vars);
	if (!sortPairs(vars))
		return (false);
	if (!insertPendElm(vars))
		return (false);
	return (true);
}

/*first step of F-J algorithm: sort the two elements
* of each single pair in decreasing order*/
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

/*second step of F-J algorithm: sort increasingly the pairs by 
* their first element (the highest). That is perfomed here by
* building the main chain (ordered sequence) with essentially 
* the first elements of pairs using insertion algorithm and 
* at the same time the pend elements chain containing the respective pend element*/
bool		PmergeMe::sortPairs(t_vvars& vars)
{
	if (vars.arr2dim.begin()->size() == 1)
		return (vars.sorted.push_back(vars.arr2dim.begin()->at(0)), true);
	vars.sorted.push_back(vars.arr2dim.begin()->at(0));
	vars.pendElms.push_back(vars.arr2dim.begin()->at(1));
	for (std::vector<std::vector<unsigned> >::iterator it = vars.arr2dim.begin() + 1; \
			it != vars.arr2dim.end(); it++)
	{
		if (it->size() > 1)
		{
			if (!buildMainPendChains(vars, it->at(0), it->at(1)))
				return (false);
		}
		else if (it->size() == 1)
			vars.pendElms.push_back(it->at(0));
	}
	return (true);
}

bool		PmergeMe::buildMainPendChains(t_vvars& vars, unsigned& elm1, unsigned& elm2)
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

/*third and last step of F-J algorithm: pend elements are inserted 
* in main chain by following Jacobsthal numbers to get the next pend element to insert*/
bool		PmergeMe::insertPendElm(t_vvars& vars)
{
	std::vector<unsigned>::iterator 	start;
	std::vector<unsigned>::iterator 	end;
	
	vars.erased = 0;
	if (vars.pendElms.empty())
		return (true);
	start = vars.sorted.begin();
	end = vars.sorted.end() - 1;
	vars.sorted.insert(vars.sorted.begin(), vars.pendElms.at(0));
	vars.pendElms.erase(vars.pendElms.begin());
	vars.erased++;
	insertFollowingJacobsthal(vars);
	for (std::vector<unsigned>::iterator it = vars.pendElms.begin(); \
			it != vars.pendElms.end(); it++)
		insert_op(vars, *it);
	vars.pendElms.clear();
	return (true);
}

bool		PmergeMe::insertFollowingJacobsthal(t_vvars& vars)
{
	vars.k = 3;
	for (size_t	i = Libftpp::jacobsthalNumber(vars.k) - vars.erased - 1; \
			i < vars.pendElms.size(); \
			i = Libftpp::jacobsthalNumber(vars.k) - vars.erased - 1)
	{
		insert_op(vars, vars.pendElms.at(i));
		vars.pendElms.erase(vars.pendElms.begin() + i);
		
		for (size_t x = Libftpp::jacobsthalNumber(vars.k) - vars.erased - 2; \
				x + vars.erased + 1 > Libftpp::jacobsthalNumber(vars.k - 1) \
				&& x < vars.pendElms.size(); x--)
		{
			insert_op(vars, vars.pendElms.at(x));
			vars.pendElms.erase(vars.pendElms.begin() + (x));
			vars.erased++;
		}
		vars.erased++;
		vars.k++;
	}
	return (true);
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


/** *******************************DEBUG MODE METHODS***************************************** **/


/*call this function instead of PmergeMe::merge(vars) to display steps of the sorting*/
bool		PmergeMe::debugModeDisplayer(t_vvars& vars)
{
			std::cout << "VECTOR PART" << std::endl;
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
