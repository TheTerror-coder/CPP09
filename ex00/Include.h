/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:47:43 by TheTerror         #+#    #+#             */
/*   Updated: 2024/02/25 13:01:18 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef	INCLUDE_H
# define	INCLUDE_H

# include "Date.hpp"
# include "CustomException.hpp"

typedef class	CustomException::SyntaxErrorException		t_SyntaxErrorException;
typedef class	CustomException::InfileErrorException		t_InfileErrorException;
typedef class	Date::DateErrorException					t_DateErrorException;
typedef class	CustomException::EmptyDatabaseException		t_EmptyDatabaseException;
typedef class	CustomException::DatabaseException			t_DatabaseException;

#endif