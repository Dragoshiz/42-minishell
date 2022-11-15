/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_util4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 03:05:01 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/14 14:41:49 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redir_error_check(t_parsing *p, char *str, int i)
{
	if ((str[i] == '<' && str[i + 1] == '>') || \
	(str[i] == '>' && str[i + 1] == '<') || \
	(is_redc(str[i + 1]) && is_redc(str[i + 2])))
	{
		p->vars->s_err_c = str[i];
		p->vars->syntax_error = 1;
	}
}

int	token_value_red(t_parsing *p, char *str, int i)
{
	redir_error_check(p, str, i);
	if (str[i] == '<' && !is_redc(str[i + 1]))
		return (1);
	else if (str[i] == '>' && !is_redc(str[i + 1]))
		return (2);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (3);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (4);
	else if (str[i] == '<' && str[i + 1] == '>')
		return (1);
	else if (str[i] == '>' && str[i + 1] == '<')
		return (2);
	return (0);
}
