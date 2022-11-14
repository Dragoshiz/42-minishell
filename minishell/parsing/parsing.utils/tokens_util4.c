/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_util4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 03:05:01 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/14 10:14:15 by vfuhlenb         ###   ########.fr       */
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

void	add_echo_values(t_parsing *p)
{
	(void)p;
	// t_token	*curr;
	// int		pipe_nr;

	// curr = p->token_list->head;
	// pipe_nr = curr->pipe_nbr;
	// p->check = 0;
	// while (curr)
	// {
	// 	if (pipe_nr != curr->pipe_nbr)
	// 	{
	// 		if (curr->type == 0 && ft_strncmp(curr->data, "echo", 4) == 0)
	// 		{
	// 			curr->type = 5;
	// 			p->check = 1;
	// 		}
	// 	}
	// 	if (curr && curr->next && curr->pipe_nbr == pipe_nr && p->check != 1 && \
	// 	curr->type != 0)
	// 	{
	// 		if (curr->next->next && curr->next->next->type == 0 && \
	// 		ft_strncmp(curr->data, "echo", 4) == 0)
	// 		{
	// 			curr->type = 5;
	// 			p->check = 1;
	// 		}
	// 	}
	// 	curr = curr->next;
	// 	if (curr && pipe_nr != curr->pipe_nbr)
	// 	{
	// 		pipe_nr = curr->pipe_nbr;
	// 		p->check = 0;
	// 	}
	// }
}
