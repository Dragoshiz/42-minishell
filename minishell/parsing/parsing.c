/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:38:33 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/29 22:10:06 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	split_pipeline(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (i < parsing->line_len)
	{
		check_quotes(parsing, i);
		if (parsing->q_open == NULL && parsing->s_vars->line[i] == PIPE)
		{
			if (parsing->s_vars->line[i + 1] == PIPE)
				exit(printf("minish: syntax error near unexpected token `|'")); // TODO create perror instance
			parsing->p_end = &parsing->s_vars->line[i];
			add_tail(parsing->pipeline, \
			dup_range(parsing->p_start, parsing->p_end));
			parsing->p_start = &parsing->p_end[1];
		}
		if (i + 1 == parsing->line_len)
			add_tail(parsing->pipeline, \
			dup_range(parsing->p_start, parsing->line_end));
		i++;
	}
}

// Initialize parsing struct
static void	initialize(t_parsing *parsing, t_vars *vars)
{
	if (*vars->line == PIPE)
		exit(printf("minish: syntax error near unexpected token `|'")); // TODO create perror instance
	parsing->s_vars = vars;
	parsing->line_len = ft_strlen(vars->line);
	parsing->line_end = &vars->line[parsing->line_len];
	parsing->p_start = vars->line;
	parsing->p_end = parsing->line_end;
	parsing->q_open = NULL;
	parsing->quote = '\0';
	parsing->pipeline = NULL;
	parsing->pipeline = (t_linkedList *) malloc(sizeof(t_linkedList)); // TODO why does the struct not malloc it already?
	initialize_list(parsing->pipeline);
}

// DEBUG print args
static void	debug_print_args(char *args[], int num_args)
{
	int	i;

	i = 0;
	while (i < num_args) // DEBUG
	{
		printf("arg[%d]: $%s$\n", i, args[i]);
		i++;
	}
}

// frees all allocated memory
static void	cleanup(t_parsing *parsing)
{
	delete_list(parsing->pipeline);
}

// Main function for Parsing & initial checks
void	parsing(t_vars *vars)
{
	t_parsing	parsing;

	initialize(&parsing, vars);
	split_pipeline(&parsing);
	fill_args(&parsing);
	debug_print_args(parsing.s_vars->args, parsing.s_vars->num_args); // DEBUG
	//display_linked_list(parsing.pipeline); // DEBUG
	cleanup(&parsing);
}
