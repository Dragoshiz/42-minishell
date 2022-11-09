/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:55:04 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/09 20:27:52 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// sets syntax_error to i and s_err_ to c
void	add_syntax_error(t_parsing *p, char *c, int i)
{
	p->vars->s_err_c = *c;
	p->vars->syntax_error = i;
}

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
