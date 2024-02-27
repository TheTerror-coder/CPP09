/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MathTools.tpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:05:05 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/27 19:32:40 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

template <typename Tdata>
Tdata			Libftpp::operation(const Tdata& lhs, const Tdata& rhs, const char opsign)
{
	Tdata	result;

	result = Tdata();
	if (!isSign(opsign))
		return (result);
	if (opsign == '+')
		result = lhs + rhs;
	if (opsign == '-')
		result = lhs - rhs;
	if (opsign == '*')
		result = lhs * rhs;
	if (opsign == '/')
		result = lhs / rhs;
	return (result);
}
