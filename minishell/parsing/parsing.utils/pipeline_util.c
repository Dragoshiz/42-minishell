/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:56:56 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/18 19:34:47 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// splits line into pipes -> linked list (pipeline)
void	split_pipeline(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (i < parsing->line_len)
	{
		check_quotes(parsing, i);
		if (parsing->q_open == NULL && parsing->vars->line[i] == PIPE)
		{
			if (parsing->vars->line[i + 1] == PIPE)
				parsing->vars->syntax_error = 1;
			parsing->p_end = &parsing->vars->line[i];
			add_tail_pipe(parsing, dup_range(parsing->p_start, \
			parsing->p_end));
			parsing->p_start = &parsing->p_end[1];
		}
		if (i + 1 == parsing->line_len)
			add_tail_pipe(parsing, dup_range(parsing->p_start, \
			parsing->line_end));
		i++;
	}
	if (parsing->q_open != NULL)
		parsing->vars->syntax_error = 2;
}

// allocates for linked list pipeline
void	initialize_pipeline(t_parsing *parsing)
{
	parsing->pipeline = NULL;
	parsing->pipeline = ft_calloc(1, sizeof(t_linked_list));
	initialize_list(parsing->pipeline);
}

// if i is in quoted area, quote will store which quote is
// active and q_open will not be NULL
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

// function to trim whitespace from pipe at the beg and end
void	pipe_trim_white(t_parsing *parsing)
{
	t_node		*current;
	char		*p;

	current = parsing->pipeline->head;
	while (current)
	{
		p = ft_strtrim(current->data, " ");
		free (current->data);
		current->data = p;
		current = current->next;
	}
}
