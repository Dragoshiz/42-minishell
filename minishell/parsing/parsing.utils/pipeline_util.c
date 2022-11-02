/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:56:56 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/02 21:51:33 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	initialize_pipeline(t_parsing *parsing)
{
	parsing->pipeline = NULL;
	parsing->pipeline = ft_calloc(1, sizeof(t_linked_list));
	initialize_list(parsing->pipeline);
}

// transfers strings from linked list to arg array
void	fill_args(t_parsing *parsing)
{
	int	i;

	parsing->pipeline->current = parsing->pipeline->head;
	parsing->vars->num_args = count_linked_list(parsing->pipeline);
	parsing->vars->args = ft_calloc((parsing->vars->num_args + 1), sizeof(char *));
	i = 0;
	while (i < parsing->vars->num_args)
	{
		parsing->vars->args[i] = ft_strdup(parsing->pipeline->current->data);
		if (parsing->pipeline->current->next)
			parsing->pipeline->current = parsing->pipeline->current->next;
		i++;
	}
	parsing->vars->args[i] = NULL;
}

void	check_quotes(t_parsing *parsing, int i)
{
	if ((parsing->vars->line[i] == SQUOTE || \
	parsing->vars->line[i] == DQUOTE) && (parsing->q_open == NULL))
	{
		parsing->q_open = &parsing->vars->line[i];
		parsing->quote = parsing->vars->line[i];
	}
	else if (parsing->quote == parsing->vars->line[i])
		parsing->q_open = NULL;
}
