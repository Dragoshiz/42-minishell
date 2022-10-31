/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:38:33 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/31 17:15:15 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	split_pipe(t_parsing *parsing)
{
	int	i;

	i = 0;
	initialize_line(parsing);
	
}

static void	split_pipeline(t_parsing *parsing)
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
			add_tail(parsing->pipeline, \
			dup_range(parsing->p_start, parsing->p_end));
			parsing->p_start = &parsing->p_end[1];
		}
		if (i + 1 == parsing->line_len)
			add_tail(parsing->pipeline, \
			dup_range(parsing->p_start, parsing->line_end));
		i++;
	}
	if (parsing->q_open != NULL)
		parsing->vars->syntax_error = 2;
}

// Initialize parsing struct
static void	initialize_parsing(t_parsing *parsing, t_vars *vars)
{
	parsing->vars = vars;
	parsing->line_len = ft_strlen(vars->line);
	parsing->line_end = &vars->line[parsing->line_len];
	parsing->p_start = vars->line;
	parsing->p_end = parsing->line_end;
	parsing->q_open = NULL;
	parsing->quote = '\0';
}

// displays error message. 1:near unexpected token 2:unclosed quote
static void	syntax_errors(t_parsing *parsing)
{
	if (parsing->vars->syntax_error == 1)
		printf("minish: syntax error near unexpected token '|' \n");
	if (parsing->vars->syntax_error == 2)
		printf("minish: syntax error unclosed quote \n");
}

// DEBUG print args
static void	debug_print_args(char *args[], int num_args)
{
	int	i;

	i = 0;
	while (i < num_args)
	{
		printf("arg[%d]: $%s$\n", i, args[i]);
		i++;
	}
}

// Main function for Parsing & initial checks
void	parsing(t_vars *vars)
{
	t_parsing	parsing;

	initialize_parsing(&parsing, vars);
	initialize_pipeline(&parsing);
	split_pipeline(&parsing);
	split_pipe(&parsing);
	fill_args(&parsing); // TODO update function to cpy from sublist
	debug_print_args(parsing.vars->args, parsing.vars->num_args); // DEBUG
	//display_linked_list(parsing.pipeline); // DEBUG
	delete_list(parsing.pipeline);
	syntax_errors(&parsing);
	// if (!parsing.vars->syntax_error)
	// 	delete_sub_list(parsing.pipeline); // TODO implement
}
