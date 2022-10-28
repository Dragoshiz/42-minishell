/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:38:33 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/28 17:37:29 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// process readline input and prepares args for the executor
static void	split_pipeline(t_parsing *parsing)
{
	/*
	if pipe found outside quotes, then split
	
	while p_start < line_end
	{
		- iterate string until finds quote character [[peek]]
			- if pipe symbol, then split [[add node]]
				- only if pipe stands alone [[check]], otherwise syntax error
			- if single or double quote
				- search for matching closing quote until reaches end of string.
					- if no closing quote found -> return (syntax error)
				- set p_end
				- use *dup_range to copy range to pipe node
				- set marker as new start after the closing quote [[set marker]]
			- if \0 then return
		i++;
	}

	- create sub-list for each pipe
		- while p_start < line_end
			- if single quote
				iterate till closing quote and copy whole to one argument
			- if double quote
				- iterate till closing quote
					- only recognize $
						- if found then copy expanded string in one argument
							- use str-len to measure how long i need the argument to be
			- after encouter a white space, put it to another argument, but without any preceding and trailing empty spaces

	*/

	
	
	// int		i;
	// int		token;

	// i = 0;
	// token = 0;
	// while (parsing->s_vars->line[i])
	// {
	// 	if (parsing->s_vars->line[i] == SPACE)
	// 		while (parsing->s_vars->line[i] == SPACE)
	// 			i++;
	// 	if (parsing->s_vars->line[i] && parsing->s_vars->line[i] == PIPE)
	// 	{
	// 		parsing->s_vars->line[i] = '\0';
	// 		addTail(parsing->pipeline, ft_strdup(&parsing->s_vars->line[token]));
	// 		token = i + 1;
	// 		if (parsing->s_vars->line[i] == SPACE)
	// 		{
	// 			while (parsing->s_vars->line[i] == SPACE)
	// 				i++;
	// 		}
	// 	}
	// 	i++;
	// }
	// addTail(parsing->pipeline, ft_strdup(&parsing->s_vars->line[token]));
	//displayLinkedList(pipeline); // DEBUG
	//clearLinkedList(pipeline); // TODO finish the function
}

// Initialize parsing struct
static void	initialize(t_parsing *parsing, t_vars *vars)
{
	// TODO if || in line, then exit with error message "OR not implemented"
	if (*vars->line == PIPE)
		exit(printf("minish: syntax error near unexpected token `|'")); // TODO create perror instance
	parsing->line_len = 0;
	parsing->pipeline = NULL;
	parsing->s_vars = vars;
	parsing->p_start = vars->line;
	parsing->p_end = NULL;
	//parsing->line = ft_strdup(parsing->s_vars->line); // TODO not needed
	parsing->line_len = ft_strlen(vars->line);
	parsing->line_end = vars->line[parsing->line_len + 1]; // pointer to \0 from line
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

// frees all allocated memory
static void	cleanup(t_parsing *parsing)
{
	deleteList(parsing->pipeline);
}

// Main function for Parsing & initial checks
void	parsing(t_vars *vars)
{
	t_parsing	parsing;

	initialize(&parsing, vars);
	split_pipeline(&parsing);
	fill_args(&parsing);
	debug_print_args(parsing.s_vars->args, parsing.s_vars->num_args); // DEBUG
	cleanup(&parsing);
}
