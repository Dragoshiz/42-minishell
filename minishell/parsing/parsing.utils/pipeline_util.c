/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:56:56 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/07 20:27:08 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	split_pipeline(t_parsing *parsing)
{
	int	i;

	i = 0;
	if (*parsing->vars->line == PIPE)
		parsing->vars->syntax_error = 1;
	while (i < parsing->line_len)
	{
		check_quotes(parsing, i);
		if (parsing->q_open == NULL && parsing->vars->line[i] == PIPE)
		{
			if (parsing->vars->line[i + 1] == PIPE)
				parsing->vars->syntax_error = 1;
			parsing->p_end = &parsing->vars->line[i];
			add_tail(parsing->pipeline, dup_range(parsing->p_start, \
			parsing->p_end));
			parsing->p_start = &parsing->p_end[1];
		}
		if (i + 1 == parsing->line_len)
			add_tail(parsing->pipeline, dup_range(parsing->p_start, \
			parsing->line_end));
		i++;
	}
	if (parsing->q_open != NULL)
		parsing->vars->syntax_error = 2;
}

void	initialize_pipeline(t_parsing *parsing)
{
	parsing->pipeline = NULL;
	parsing->pipeline = ft_calloc(1, sizeof(t_linked_list));
	initialize_list(parsing->pipeline);
}

// transfers strings from linked list to arg array
void	fill_args(t_parsing *parsing)
{
	int		i;
	t_node	*current;

	current = parsing->pipeline->head;
	parsing->vars->num_args = count_linked_list(parsing->pipeline);
	parsing->vars->args = ft_calloc((parsing->vars->num_args + 1), \
	sizeof(char *));
	i = 0;
	while (i < parsing->vars->num_args)
	{
		parsing->vars->args[i] = ft_strdup(current->data);
		if (current->next)
			current = current->next;
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
