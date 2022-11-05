/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:55:04 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/05 23:23:45 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	edge_cases(t_parsing *parsing)
{
	last_pipe_empty(parsing);
	empty_redirection(parsing);
}

void	last_pipe_empty(t_parsing *parsing)
{
	t_node	*current;

	current = parsing->pipeline->tail;
	if (current->data)
	{
		if(is_whitespace(current->data))
			parsing->vars->syntax_error = 3;
	}
}

void	empty_redirection(t_parsing *parsing) // TODO
{
	t_token	*current;

	current = parsing->token_list->head;
	while (current)
	{
		if ((ft_strncmp(current->data, "<<", 2) == 0) && current->next == NULL && current->type != 1)
			parsing->vars->syntax_error = 4;
		if (current->next != NULL)
		{
			if ((ft_strncmp(current->data, "<<", 2) == 0) && (is_whitespace(current->next->data)) && current->type != 1)
				parsing->vars->syntax_error = 4;
			else if ((ft_strncmp(current->data, "<<", 2) == 0) && (ft_strncmp(current->next->data, "<<", 2) == 0) && current->next->type != 1 && current->type != 1)
				parsing->vars->syntax_error = 4;
		}
		current = current->next;
	}
}