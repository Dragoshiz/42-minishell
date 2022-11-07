/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_util3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:27:33 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/07 17:27:38 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
int	is_variable_start_char(char c)
{
	if (c != 95 && !(c >= 65 \
	&& c <= 90) && !(c >= 97 && c <= 122))
		return (0);
	return (1);
}

//function that checks if char is a valid variable name character
int	is_variable_char(char c)
{
	if (c != 95 && !(c >= 65 \
	&& c <= 90) && !(c >= 97 && c <= 122) && !(c >= 48 && c <= 57))
		return (0);
	return (1);
}

int	is_redirection_char(char c)
{
	if (c != 60 && c != 62)
		return (0);
	return (1);
}
