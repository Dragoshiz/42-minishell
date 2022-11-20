/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:55:04 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/20 01:41:56 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// sets syntax_error to i and s_err_ to c
void	add_syntax_error(t_parsing *p, char *c, int i)
{
	p->vars->s_err_c = *c;
	p->vars->syntax_error = i;
}

// edge cases related to pipes
void	s_err_pipe(t_parsing *p)
{
	t_node	*current;

	current = p->pipeline->head;
	while (current)
	{
		if (is_whitespace(current->data))
			add_syntax_error(p, "|", 1);
		current = current->next;
	}
}

// edge cases related to redirections
void	s_err_redir(t_parsing *p)
{
	t_token	*curr;
	int		pipe_nr;

	curr = p->token_list->head;
	if (p->token_list->tail->type != 0)
	{
		add_syntax_error(p, &p->token_list->tail->data[0], 1);
		return ;
	}
	while (curr)
	{
		pipe_nr = curr->pipe_nbr;
		if (pipe_nr == curr->pipe_nbr)
		{
			if (curr->next != NULL)
			{
				if (curr->type != 0 && (curr->next->type != 0 || \
				curr->next->pipe_nbr != curr->pipe_nbr))
				{
					add_syntax_error(p, &curr->data[0], 1);
				}
			}
		}
		curr = curr->next;
	}
}

// edge cases related to tokens
int	s_err_token(t_parsing *p)
{
	t_token	*current;

	current = p->token_list->head;
	if (!current && p->num_cmds < 1)
	{
		p->vars->syntax_error = 3;
		ft_putstr_fd("\n", 2);
		g_exit = 259;
		return (1);
	}
	return (0);
}
