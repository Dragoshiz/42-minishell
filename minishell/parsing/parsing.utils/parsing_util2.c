/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:56:45 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/16 11:23:53 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// checks if after the dollar char is a quote char
int	peek_dollar_quote(t_parsing *p, char *str)
{
	if (str[p->ix] == '$' && is_quote_char(str[p->ix + 1]))
		return (1);
	return (0);
}

// seeks to the right until str[i] != c, return i
void	seek_word_r(t_parsing *p, char *str)
{
	while (is_word_c(str[p->ix]) && str[p->ix] && p->q_open == NULL)
	{
		check_token_quotes(p, str, p->ix);
		p->ix++;
	}
}

// seeks to the left until str[i] != c, return i
void	seek_red_r(t_parsing *p, char *str)
{
	while (is_redc(str[p->ix]) && str[p->ix] && p->q_open == NULL)
	{
		check_token_quotes(p, str, p->ix);
		p->ix++;
	}
}

// seeks to the left until str[i] != c, return i
void	seek_whs_r(t_parsing *p, char *str)
{
	while (is_whs_c(str[p->ix]) && str[p->ix] && p->q_open == NULL)
	{
		check_token_quotes(p, str, p->ix);
		p->ix++;
	}
}
