/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:43:22 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/12 19:43:10 by TheTerror        ###   ########lyon.fr   */
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
	if (this == &other)
		return (*this);
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
	if (this == &other)
		return (*this);
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
	if (this == &other)
		return (*this);
	return (*this);
}

PmergeMe::List_variables::~List_variables()
{}

/*parses obviously the integers sequence passed to the main program
* then sorts the obtained sequence*/
bool		PmergeMe::mergeInsert(const char** argv)
{
	t_vvars		vvars;
	t_lvars		lvars;

	if (!parseArgv(vvars, argv))
		return (false);
	if (vvars.arr2dim.empty() || vvars.arr2dim.begin()->empty())
		return (true);
	copyVector2List(vvars, lvars);
	if (!sort(vvars))
		return (false);
	if (!sort(lvars))
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

/*checks formatting and convert from */
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


/** *******************************std::VECTOR***************************************** **/


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


/** *******************************std::LIST***************************************** **/


bool		PmergeMe::copyVector2List(t_vvars& vvars, t_lvars& lvars)
{
	std::list<unsigned>		arr;

	for (std::vector<std::vector<unsigned> >::iterator	it = vvars.arr2dim.begin();
			it != vvars.arr2dim.end(); it++)
	{
		arr.clear();
		for (std::vector<unsigned>::iterator i = it->begin(); i != it->end(); i++)
			arr.push_back(*i);
		lvars.arr2dim.push_back(arr);
	}
	return (false);
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
