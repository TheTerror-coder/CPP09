/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:38:08 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/03 20:15:52 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PMERGEME_HPP
# define	PMERGEME_HPP

# include <iostream>
# include <vector>
# include <list>
# include <cstdlib>
# include <cmath>
# include <limits>
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
		
				std::vector<std::vector<unsigned> >		arr2dim;
				std::vector<unsigned>					sorted;
				std::vector<unsigned>					pendElms;
				size_t									k;
				size_t									erased;
			
			private:
			
		};
		
		class List_variables
		{
			public:

				List_variables();
				List_variables(const List_variables& other);
				List_variables	operator= (const List_variables& other);
				~List_variables();
		
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
		static bool		insertFirstElm(t_vvars& vars, unsigned& elm1, unsigned& elm2);
		static bool		insertPendElm(t_vvars& vars);
		static bool		insertFollowingJacobsthal(t_vvars& vars);
		static bool		insert_op(t_vvars& vars, unsigned elm);
		static size_t		jacobsthalNumber(size_t k);

};

#endif
/* ************************************************************************** */