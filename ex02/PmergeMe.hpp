/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:38:08 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/04 18:53:39 by TheTerror        ###   ########lyon.fr   */
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

class PmergeMe
{
	public:

		PmergeMe(const PmergeMe& other);
		PmergeMe	operator= (const PmergeMe& other);
		~PmergeMe();

		static bool		mergeInsert(const char** argv);

	private:

		PmergeMe();
		
		class Vector_variables
		{
			public:

				Vector_variables();
				Vector_variables(const Vector_variables& other);
				Vector_variables	operator= (const Vector_variables& other);
				~Vector_variables();
		
				std::vector<std::vector<unsigned> >		arr2dim;	//pairs chain
				std::vector<unsigned>					sorted;		//main chain
				std::vector<unsigned>					pendElms;	//pend elments chain
				size_t									k;			//specify the k'th Jacobsthal number
				size_t									erased;		//erased elements from 'pendelms' array counter
			
			private:
			
		};
		
		class List_variables
		{
			public:

				List_variables();
				List_variables(const List_variables& other);
				List_variables	operator= (const List_variables& other);
				~List_variables();
		
				std::list<std::list<unsigned> >		arr2dim;		//pairs chain
				std::list<unsigned>					sorted;			//main chain
				std::list<unsigned>					pendElms;		//pend elments chain
				size_t									k;			//specify the k'th Jacobsthal number
				size_t									erased;		//erased elements from 'pendelms' array counter
			
			private:
			
		};

		typedef class Vector_variables	t_vvars;
		typedef class List_variables	t_lvars;
	
		static bool		parseArgv(t_vvars& vars, const char** argv);
		static bool		checkGetValue(double& val, const char* arg);
		static bool		sort(t_vvars& vars);
		static bool		sortEachPair(t_vvars& vars);
		static bool		sortPairs(t_vvars& vars);
		static bool		merge(t_vvars& vars);
		static bool		buildMainPendChains(t_vvars& vars, unsigned& elm1, unsigned& elm2);
		static bool		insertPendElm(t_vvars& vars);
		static bool		insertFollowingJacobsthal(t_vvars& vars);
		static bool		insert_op(t_vvars& vars, unsigned elm);

		
		static bool		copyVector2List(t_vvars& vvars, t_lvars& lvars);

		static bool		sort(t_lvars& vars);
		static bool		sortEachPair(t_lvars& vars);
		static bool		sortPairs(t_lvars& vars);
		static bool		merge(t_lvars& vars);
		static bool		buildMainPendChains(t_lvars& vars, unsigned& elm1, unsigned& elm2);
		static bool		insertPendElm(t_lvars& vars);
		static bool		insertFollowingJacobsthal(t_lvars& vars);
		static bool		insert_op(t_lvars& vars, unsigned elm);
};

#endif
/* ************************************************************************** */