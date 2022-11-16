/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_util3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:27:33 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/16 11:24:03 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// checks if in quoted area
void	check_expansion_quotes(char *quote, int *status, char c)
{
	if (c == DQUOTE && (*status == 0))
		*quote = c;
	if (c == SQUOTE && (*status == 0) && *quote != DQUOTE)
	{
		*status = 1;
		*quote = c;
	}
	else if (*quote == c)
		*status = 0;
}

//function that checks if char is a valid first variable name character
//(underscore, lower-case letter, upper-case letter)
int	is_variable_start_char(char c)
{
	if (c != 95 && !(c >= 65 \
	&& c <= 90) && !(c >= 97 && c <= 122))
		return (0);
	return (1);
}

//function that checks if char is a valid variable name character
//(digit, underscore, lower-case letter, upper-case letter)
int	is_variable_char(char c)
{
	if (c == 95 || (c >= 65 \
	&& c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	return (0);
}

// function to check if character is a redirection char
int	is_redc(char c)
{
	if (c == 60 || c == 62)
		return (1);
	return (0);
}

// function to check if character is a quote char
int	is_quote_char(char c)
{
	if (c == 36 || c == 39)
		return (1);
	return (0);
}
