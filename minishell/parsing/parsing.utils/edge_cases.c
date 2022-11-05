/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:55:04 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/05 22:22:09 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	edge_cases(t_parsing *parsing)
{
	last_pipe_empty(parsing);
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