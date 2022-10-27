/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:38:33 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/27 18:53:46 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	separate_pipes(t_parsing *parsing)
{
	int		i;
	int		token;

	i = 0;
	token = 0;
	while (parsing->line[i])
	{
		if (parsing->line[i] == SPACE)
			while (parsing->line[i] == SPACE)
				i++;
		if (parsing->line[i] && parsing->line[i] == PIPE)
		{
			parsing->line[i] = '\0';
			addTail(parsing->pipeline, ft_strdup(&parsing->line[token]));
			token = i + 1;
			if (parsing->line[i] == SPACE)
			{
				while (parsing->line[i] == SPACE)
					i++;
			}
		}
		i++;
	}
	addTail(parsing->pipeline, ft_strdup(&parsing->line[token]));
}

// frees all allocated memory
static void	cleanup(t_parsing *parsing)
{
	deleteList(parsing->pipeline);
}

// process readline input and prepares args for the executor
static void	split_pipeline(t_parsing *parsing)
{
	separate_pipes(parsing);
	//displayLinkedList(pipeline); // DEBUG
	//clearLinkedList(pipeline); // TODO finish the function
	fill_args(parsing);
	free(parsing->line);
}

// Initialize parsing struct
static void	initialize(t_parsing *parsing, t_vars *vars)
{
	if (*vars->line == PIPE)
		exit(printf("minish: syntax error near unexpected token `|'")); // TODO create perror instance
	parsing->line_len = 0;
	parsing->pipeline = NULL;
	parsing->s_vars = vars;
	parsing->line = ft_strdup(parsing->s_vars->line); // TODO protect
	parsing->line_len = ft_strlen(parsing->line);
	parsing->pipeline = (t_linkedList *) malloc(sizeof(t_linkedList));
	initializeList(parsing->pipeline);
}

// DEBUG print args
static void	debug_print_args(char *args[], int num_args)
{
	int			i;

	i = 0;
	while (i < num_args) // DEBUG
	{
		printf("arg[%d]: %s $\n", i, args[i]);
		i++;
	}
}

// Main function for Parsing & initial checks
void	parsing(t_vars *vars) // TODO if || in line, then exit with error message "OR not implemented"
{
	t_parsing	parsing;

	initialize(&parsing, vars);
	split_pipeline(&parsing);
	cleanup(&parsing);
	debug_print_args(parsing.s_vars->args, parsing.s_vars->num_args); // DEBUG
}
