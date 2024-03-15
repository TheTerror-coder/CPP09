/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeWithList.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:43:22 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/15 15:31:15 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/** *******************************std::LIST PART***************************************** **/

PmergeMe::List_variables::List_variables()
	: k(0), erased(0), listTime(0)
{
}

PmergeMe::List_variables::List_variables(const List_variables& other)
	: arr2dim(other.arr2dim), sorted(other.sorted), pendElms(other.pendElms), \
	k(other.k), erased(other.erased), argv(other.argv), listTime(other.listTime)
{
	*this = other;
}

PmergeMe::List_variables&	PmergeMe::List_variables::operator= (const List_variables& other)
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
	this->listTime = other.listTime;
	return (*this);
}

PmergeMe::List_variables::~List_variables()
{
}


bool		PmergeMe::withAList(t_lvars& vars, const std::string& argv)
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

bool		PmergeMe::parseArgv(t_lvars& vars)
{
	double					val;
	std::list<unsigned>		arr;
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

bool		PmergeMe::sort(t_lvars& vars)
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
bool		PmergeMe::merge(t_lvars& vars)
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
bool		PmergeMe::sortEachPair(t_lvars& vars)
{
	unsigned	tmp;
	
	for (std::list<std::list<unsigned> >::iterator it = vars.arr2dim.begin(); \
			it != vars.arr2dim.end(); it++)
	{
		if (it->size() > 1)
		{
			tmp = it->front();
			if (it->front() < it->back())
			{
				it->front() = it->back();
				it->back() = tmp;
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
bool		PmergeMe::sortPairs(t_lvars& vars)
{
	if (vars.arr2dim.begin()->size() == 1)
		return (vars.sorted.push_back(vars.arr2dim.begin()->front()), true);
	vars.sorted.push_back(vars.arr2dim.begin()->front());
	vars.pendElms.push_back(vars.arr2dim.begin()->back());
	for (std::list<std::list<unsigned> >::iterator it = ++vars.arr2dim.begin(); \
			it != vars.arr2dim.end(); it++)
	{
		if (it->size() > 1)
		{
			if (!buildMainPendChains(vars, it->front(), it->back()))
				return (false);
		}
		else if (it->size() == 1)
			vars.pendElms.push_back(it->front());
	}
	return (true);
}

bool		PmergeMe::buildMainPendChains(t_lvars& vars, unsigned& elm1, unsigned& elm2)
{
	std::list<unsigned>::iterator 	start;
	std::list<unsigned>::iterator 	end;
	
	start = vars.sorted.begin();
	end = --vars.sorted.end();
	if (elm1 <= *start)
		return (vars.sorted.insert(start, elm1), \
				vars.pendElms.insert(vars.pendElms.begin(), elm2), true);
	if (elm1 >= *end)
		return (vars.sorted.push_back(elm1), \
				vars.pendElms.push_back(elm2), true);
	for (std::list<unsigned>::iterator it1 = start, it2 = vars.pendElms.begin(); \
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
bool		PmergeMe::insertPendElm(t_lvars& vars)
{
	std::list<unsigned>::iterator 	start;
	std::list<unsigned>::iterator 	end;
	
	vars.erased = 0;
	if (vars.pendElms.empty())
		return (true);
	start = vars.sorted.begin();
	end = --vars.sorted.end();
	vars.sorted.insert(vars.sorted.begin(), vars.pendElms.front());
	vars.pendElms.erase(vars.pendElms.begin());
	vars.erased++;
	insertFollowingJacobsthal(vars);
	for (std::list<unsigned>::iterator it = vars.pendElms.begin(); \
			it != vars.pendElms.end(); it++)
		insert_op(vars, *it);
	vars.pendElms.clear();
	return (true);
}

bool		PmergeMe::insertFollowingJacobsthal(t_lvars& vars)
{
	std::list<unsigned>::iterator	it;

	vars.k = 3;
	for (size_t	i = Libftpp::jacobsthalNumber(vars.k) - vars.erased - 1; \
			i < vars.pendElms.size(); \
			i = Libftpp::jacobsthalNumber(vars.k) - vars.erased - 1)
	{
		it = vars.pendElms.begin();
		std::advance(it, i);
		insert_op(vars, *it);
		vars.pendElms.erase(it);
		for (size_t x = Libftpp::jacobsthalNumber(vars.k) - vars.erased - 2; \
				x + vars.erased + 1 > Libftpp::jacobsthalNumber(vars.k - 1) \
				&& x < vars.pendElms.size(); x--)
		{
			it = vars.pendElms.begin();
			std::advance(it, x);
			insert_op(vars, *it);
			vars.pendElms.erase(it);
			vars.erased++;
		}
		vars.erased++;
		vars.k++;
	}
	return (true);
}

bool		PmergeMe::insert_op(t_lvars& vars, unsigned elm)
{
	std::list<unsigned>::iterator 	start;
	std::list<unsigned>::iterator 	end;
	
	start = vars.sorted.begin();
	end = --vars.sorted.end();
	if (elm <= *start)
		return (vars.sorted.insert(start, elm), true);
	if (elm >= *end)
		return (vars.sorted.push_back(elm), true);
	for (std::list<unsigned>::iterator it = start; \
			it != vars.sorted.end(); it++)
	{
		if (elm <= *it)
			return (vars.sorted.insert(it, elm), true);
	}
	return (false);
}


/** *******************************DEBUG MODE METHODS***************************************** **/


/*call this function instead of PmergeMe::merge(vars) to display steps of the sorting*/
bool		PmergeMe::debugModeDisplayer(t_lvars& vars)
{
			std::cout << "LIST PART" << std::endl;
	sortEachPair(vars);
			for (std::list<std::list<unsigned> >::iterator it = vars.arr2dim.begin(); it != vars.arr2dim.end(); it++)
			{
				std::cout << it->front();
				if (it->size() == 2)
					std::cout << " | " << it->back() << std::endl;
				else
					std::cout << std::endl;
			}
	if (!sortPairs(vars))
		return (false);
			std::cout << "----------" << std::endl;
			for (std::list<unsigned>::iterator it = vars.sorted.begin(); it != vars.sorted.end(); it++)
				std::cout << *it << " ";
			std::cout << std::endl;
			for (std::list<unsigned>::iterator it = vars.pendElms.begin(); it != vars.pendElms.end(); it++)
				std::cout << *it << " ";
			std::cout << std::endl;
			std::cout << "----------" << std::endl;
	if (!insertPendElm(vars))
		return (false);
			std::cout << "----------" << std::endl;
			for (std::list<unsigned>::iterator it = vars.sorted.begin(); it != vars.sorted.end(); it++)
				std::cout << *it << " ";
			std::cout << std::endl;
			for (std::list<unsigned>::iterator it = vars.pendElms.begin(); it != vars.pendElms.end(); it++)
				std::cout << *it << " ";
			std::cout << std::endl;
			std::cout << "----------" << std::endl;
	return (true);
}
