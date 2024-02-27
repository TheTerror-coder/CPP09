/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:32:32 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/27 20:52:01 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef	RPN_HPP
# define	RPN_HPP

# include <iostream>
# include <sstream>
# include <stack>
# include "libftpp/Libftpp.hpp"

class RPN
{
	public:
	
		RPN(const RPN& other);
		RPN&	operator= (const RPN& other);
		~RPN();
	
		static bool			calculate(const char** argv);
		static bool			calculate(const std::string& expr);

	private:

		RPN();

		class Variables
		{
			public:

				Variables();
				Variables(const Variables& other);
				Variables& operator= (const Variables& other);
				~Variables();

				std::string				expr;
				std::stack<double>		__stack;
				std::istringstream		sstream;
				std::string				element;
				double					value;
				double					lhs;
				double					rhs;
				double					result;

			private:

			
		};
		
		typedef class Variables		t_vars;

		static bool					calculate_op(t_vars& vars);
		static bool					pushOnStack(t_vars& vars);
		static bool					evaluate(t_vars& vars);
};

#endif
