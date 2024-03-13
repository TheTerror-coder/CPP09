/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:38:02 by TheTerror         #+#    #+#             */
/*   Updated: 2024/03/13 19:47:37 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/*default constructor*/
RPN::RPN()
{
}

/*copy constructor*/
RPN::RPN(const RPN& other)
{
	*this = other;
}

/*assignment operator*/
RPN&	RPN::operator=(const RPN& other)
{
	if (this == &other)
		return (*this);
	return (*this);
}

/*destructor*/
RPN::~RPN()
{
}

/*Variables: default constructor*/
RPN::Variables::Variables()
	: value(0), lhs(0), rhs(0), result(0)
{
}

/*Variables: copy constructor*/
RPN::Variables::Variables(const Variables& other)
	: expr(other.expr), __stack(other.__stack), \
	element(other.element), value(other.value), \
	lhs(other.lhs), rhs(other.rhs), result(other.result)
{
	this->sstream.clear();
	*this = other;
}

/*Variables: assignment operator*/
RPN::Variables&		RPN::Variables::operator=(const Variables& other)
{
	if (this == &other)
		return (*this);
	this->expr = other.expr;
	this->__stack = other.__stack;
	this->sstream.clear();
	this->element = other.element;
	this->value = other.value;
	this->rhs = other.rhs;
	this->lhs = other.lhs;
	this->result = other.result;
	return (*this);
}

/*Variables: destructor*/
RPN::Variables::~Variables()
{
}

bool	RPN::calculate(const char** argv)
{
	std::string		expr;

	for (size_t i = 0; argv[i]; i++)
		expr = expr + " " + argv[i];
	if (!RPN::calculate(expr))
		return (false);
	return (true);
}

bool	RPN::calculate(const std::string& expr)
{
	try
	{
		t_vars	vars;

		if (expr.empty())
			return (Libftpp::error("empty expression"));
		vars.expr = expr;
		Libftpp::replaceBySpace(vars.expr);
		Libftpp::trimSpaces(vars.expr);
		vars.sstream.str(expr);
		if (!calculate_op(vars))
			return (false);
		if (vars.__stack.size() != 1)
			return (Libftpp::error("invalid expression \'" + expr + "\'"));
		std::cout << vars.__stack.top() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (false);
	}
	return (true);
}

bool	RPN::calculate_op(t_vars& vars)
{
	while (vars.sstream)
	{
		vars.element.clear();
		std::getline(vars.sstream, vars.element, ' ');
		if (!vars.element.empty())
		{
			if (Libftpp::strIsInt(vars.element))
			{
				if (!RPN::pushOnStack(vars))
					return (false);	
			}
			else if (vars.element.size() == 1 && Libftpp::isSign(vars.element.at(0)))
			{
				if (!RPN::evaluate(vars))
					return (false);
			}
			else
				return (Libftpp::error("invalid expression \'" \
						+ vars.element \
						+ "\', expecting an inverted Polish mathematical " \
						+ "expression"));
		}
	}
	return (true);
}

bool	RPN::pushOnStack(t_vars& vars)
{
	vars.value = std::atol(vars.element.c_str());
	vars.__stack.push(vars.value);
	return (true);
}

bool	RPN::evaluate(t_vars& vars)
{
	if (vars.__stack.empty())
		return (Libftpp::error("invalid expression \'" \
				+ vars.element + "\', expecting digit first"));
	vars.rhs = vars.__stack.top();
	vars.__stack.pop();
	if (vars.__stack.empty())
		return (Libftpp::error("operation aborted at element \'" \
				+ vars.element \
				+ "\', expecting an inverted Polish mathematical " \
				+ "expression"));
	vars.lhs = vars.__stack.top();
	vars.__stack.pop();
	vars.result = Libftpp::operation<double>(\
						vars.lhs, vars.rhs, vars.element.at(0));
	vars.__stack.push(vars.result);
	return (true);
}
