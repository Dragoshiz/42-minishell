/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:56:56 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/30 15:34:44 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// transfers strings from linked list to arg array
void	fill_args(t_parsing *parsing)
{
	int	i;

	parsing->pipeline->current = parsing->pipeline->head;
	parsing->s_vars->num_args = count_linked_list(parsing->pipeline);
	parsing->s_vars->args = malloc(sizeof(char *) * parsing->s_vars->num_args);
	i = 0;
	while (i < parsing->s_vars->num_args)
	{
		parsing->s_vars->args[i] = ft_strdup(parsing->pipeline->current->data);
		if (parsing->pipeline->current->next)
			parsing->pipeline->current = parsing->pipeline->current->next;
		i++;
	}
}

void	check_quotes(t_parsing *parsing, int i)
{
	if ((parsing->s_vars->line[i] == SQUOTE || \
	parsing->s_vars->line[i] == DQUOTE) && (parsing->q_open == NULL))
	{
		parsing->q_open = &parsing->s_vars->line[i];
		parsing->quote = parsing->s_vars->line[i];
	}
	else if (parsing->quote == parsing->s_vars->line[i])
		parsing->q_open = NULL;
}
