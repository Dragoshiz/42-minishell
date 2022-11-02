/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:38:33 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/02 22:49:39 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Cleans Tokens from Whitespace and expands Variables
void	expand_tokens(t_parsing *parsing)
{
	int		i;
	int		len;
	t_token	*current;
	char	*var;
	int		var_len;
	int		quote_nbr;

	current = parsing->token_list->head;
	while (current != NULL)
	{
		i = 0;
		quote_nbr = 0;
		len = ft_strlen(current->data);
		while (current->data[i])
		{
			if (current->data[i] == DQUOTE && quote_nbr == 0)
				quote_nbr++;
			if (current->data[i] == '$' && quote_nbr < 2)
				// TODO Here 
		}
		printf("token[pipe#%d]: $%s$\n", current->pipe_nbr, current->data); // DEBUG remove $ for production
		current = current->next;
	}
}

static void	split_tokens(t_parsing *parsing)
{
	int		i;
	int		j;
	char	*str;
	int		len;
	t_node	*current;

	current = parsing->pipeline->head;
	j = 0;
	while (current)
	{
		str = current->data;
		len = ft_strlen(str);
		parsing->p_start = str;
		parsing->p_end = &str[len];
		parsing->line_end = &str[len];
		parsing->q_open = NULL;
		parsing->quote = '\0';
		i = 0;
		while(str[i])
		{
			check_token_quotes(parsing, str, i);
			if (parsing->q_open == NULL && !is_whitespace_char(str[i]) && is_whitespace_char(str[i + 1]))
			{
				parsing->p_end = &str[i + 1];
				add_token(parsing, dup_range(parsing->p_start, parsing->p_end));
				parsing->p_start = &parsing->p_end[1];
			}
			if (str[i + 1] == '\0' && !is_whitespace_char(str[i]))
				add_token(parsing, dup_range(parsing->p_start, parsing->line_end));
			i++;
		}
		if (parsing->q_open != NULL)
			parsing->vars->syntax_error = 2;
		// printf("TOKEN-STR %d: %s\n", i, str);
		current = current->next;
		i = 0;
		j++;
		parsing->num_pipes = j;
	}
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
			add_tail(parsing->pipeline, dup_range(parsing->p_start, parsing->p_end));
			parsing->p_start = &parsing->p_end[1];
		}
		if (i + 1 == parsing->line_len)
			add_tail(parsing->pipeline, dup_range(parsing->p_start, parsing->line_end));
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
	parsing->num_pipes = 0;
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
	initialize_token_list(&parsing);
	split_tokens(&parsing);
	fill_args(&parsing); // TODO update function to cpy from sublist
	debug_print_args(parsing.vars->args, parsing.vars->num_args); // DEBUG
	expand_tokens(&parsing);
	display_token_list(parsing.token_list); // DEBUG
	delete_list(parsing.pipeline);
	//delete_token_list(parsing.token_list); // TODO Segfaults
	syntax_errors(&parsing);
	// if (!parsing.vars->syntax_error)
	// 	delete_sub_list(parsing.pipeline); // TODO implement
}
