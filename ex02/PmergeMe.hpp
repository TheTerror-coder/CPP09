/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:38:08 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/15 15:39:16 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PMERGEME_HPP
# define	PMERGEME_HPP

# include <iostream>
# include <vector>
# include <list>
# include <cstdlib>
# include <limits>
# include <ctime>
# include "libftpp/Libftpp.hpp"

/*static class*/
class PmergeMe
{
	public:

		PmergeMe(const PmergeMe& other);
		PmergeMe&	operator= (const PmergeMe& other);
		~PmergeMe();

		static bool		mergeInsert(const char** argv);
		static bool		mergeInsert(const std::string& argv);

	private:

		PmergeMe();
		
		class Vector_variables
		{
			public:

				Vector_variables();
				Vector_variables(const Vector_variables& other);
				Vector_variables&	operator= (const Vector_variables& other);
				~Vector_variables();
		
				std::vector<std::vector<unsigned> >		arr2dim;	//pairs chain
				std::vector<unsigned>					sorted;		//main chain
				std::vector<unsigned>					pendElms;	//pend elments chain
				size_t									k;			//specify the k'th Jacobsthal number
				size_t									erased;		//erased elements from 'pendelms' array counter
				std::string								argv;
				std::istringstream						sstream;
				double									vectorTime;	//in microseconds
			
			private:
			
		};
		
		class List_variables
		{
			public:

				List_variables();
				List_variables(const List_variables& other);
				List_variables&	operator= (const List_variables& other);
				~List_variables();
		
				std::list<std::list<unsigned> >			arr2dim;	//pairs chain
				std::list<unsigned>						sorted;		//main chain
				std::list<unsigned>						pendElms;	//pend elments chain
				size_t									k;			//specify the k'th Jacobsthal number
				size_t									erased;		//erased elements from 'pendelms' array counter
				std::string								argv;
				std::istringstream						sstream;
				double									listTime;	//in microseconds
			
			private:
			
		};

		typedef class Vector_variables	t_vvars;
		typedef class List_variables	t_lvars;
	
		static bool		checkGetValue(double& val, const std::string& element);
		static bool		display(t_vvars& vvars, t_lvars& lvars);

		/*vector part methods*/
		static bool		withAVector(t_vvars& vars, const std::string& argv);
		static bool		parseArgv(t_vvars& vars);
		static bool		sort(t_vvars& vars);
		static bool		sortEachPair(t_vvars& vars);
		static bool		sortPairs(t_vvars& vars);
		static bool		merge(t_vvars& vars);
		static bool		buildMainPendChains(t_vvars& vars, unsigned& elm1, unsigned& elm2);
		static bool		insertPendElm(t_vvars& vars);
		static bool		insertFollowingJacobsthal(t_vvars& vars);
		static bool		insert_op(t_vvars& vars, unsigned elm);

		
		/*list part methods*/
		static bool		withAList(t_lvars& vars, const std::string& argv);
		static bool		parseArgv(t_lvars& vars);
		static bool		sort(t_lvars& vars);
		static bool		sortEachPair(t_lvars& vars);
		static bool		sortPairs(t_lvars& vars);
		static bool		merge(t_lvars& vars);
		static bool		buildMainPendChains(t_lvars& vars, unsigned& elm1, unsigned& elm2);
		static bool		insertPendElm(t_lvars& vars);
		static bool		insertFollowingJacobsthal(t_lvars& vars);
		static bool		insert_op(t_lvars& vars, unsigned elm);
		
		/*call these functions instead of PmergeMe::merge(vars) to display steps of the sorting*/
		static bool		debugModeDisplayer(t_vvars& vars);
		static bool		debugModeDisplayer(t_lvars& vars);

};

#endif
/* ************************************************************************** */