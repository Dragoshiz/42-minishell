/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:38:33 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/05 01:19:39 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	remove_quote_pair(char *p, char *str, int m1, int m2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(str[i])
	{
		if (i != m1 && i != m2)
		{
			p[j] = str[i];
			j++;
		}
		i++;
	}
	return (j);
	// p[i] = '\0';
}

void	token_trim_quotes(t_parsing *parsing) // TODO possible leaks
{
	t_token		*current;
	char		*p;
	char		d_quote;
	char		s_quote;
	int			len;
	int			m1;
	int			m2;
	char		quote;
	int			i;
	int			len_p;

	d_quote = DQUOTE;
	s_quote = SQUOTE;
	current = parsing->token_list->head;
	len = 0;
	while (current)
	{
		m1 = -1;
		m2 = -1;
		i = 0;
		quote = '\0';
		len_p = 0;
		while (current->data[i])
		{
			if ((current->data[i] == d_quote || current->data[i] == s_quote) && m1 < 0)
			{
				quote = current->data[i];
				m1 = i;
			}
			else if (current->data[i] == quote && m2 < 0)
			{
				len = ft_strlen(current->data);
				p = calloc(len, sizeof(char));
				m2 = i;
				len_p = remove_quote_pair(p, current->data, m1, m2);
				current->type = 1;
				m1 = -1;
				m2 = -1;
				quote = '\0';
				current->data = p;
			}
			i++;
		}
		current->data[len_p + 1] = '\0';
		current = current->next;
	}
}

// void	token_trim_quotes(t_parsing *parsing)
// {
// 	t_token		*current;
// 	char		*p;
// 	char		d_quote;
// 	char		s_quote;
// 	int			len;

// 	d_quote = DQUOTE;
// 	s_quote = SQUOTE;
// 	current = parsing->token_list->head;
// 	len = 0;
// 	while (current)
// 	{
// 		len = ft_strlen(current->data);
// 		if ((current->data[0] == d_quote || current->data[0] == s_quote) \
// 		&& (current->data[len - 1] == d_quote || current->data[len - 1] == s_quote))
// 		{
// 			current->type = 1;
// 			p = ft_substr(current->data, 1, len - 2);
// 			free (current->data);
// 			current->data = p;
// 		}
// 		current = current->next;
// 	}
// }

void	token_trim_white(t_parsing *parsing)
{
	t_token		*current;
	char		*p;

	current = parsing->token_list->head;
	while (current)
	{
		p = ft_strtrim(current->data, " ");
		free (current->data);
		current->data = p;
		current = current->next;
	}
}

// expands variables in tokens
void	expand_tokens(t_parsing *parsing) // TODO not working
{
	int		i;
	t_token	*current;
	int		status;
	char	quote;
	char	*p;
	int		check;
	int		len;

	current = parsing->token_list->head;
	while (current != NULL)
	{
		check = 0;
		i = 0;
		status = 0;
		quote = '\0';
		while (1)
		{
			len = ft_strlen(current->data);
			while (current->data[i])
			{
				check = 0;
				check_expansion_quotes(&quote, &status, current->data[i]);
				if (status == 0 && current->data[i] == DOLLAR && is_variable_char(current->data[i + 1]))
				{
					p = insert_expanded_string(parsing->vars->env_list, current->data, i);
					// printf("\nexpanded token: %s\n", current->data); // DEBUG remove $ for production
					free (current->data);
					current->data = p;
					check = 1;
					break;
				}
				i++;
			}
			if (i == len && check == 0)
				break;
			i = 0;
		}
		current = current->next;
	}
}

void	split_tokens(t_parsing *parsing)
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
		parsing->num_cmds = j;
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
	parsing->num_cmds = 0;
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

void	parsing_cleanup(t_parsing *parsing)
{
	delete_list(parsing->pipeline);
	delete_list(parsing->vars->env_list);
	delete_token_list(parsing->token_list); // TODO Segfaults
	if (parsing->token_list)
		free(parsing->token_list);
	ft_free_doublepoint(parsing->vars->args);
	if (parsing->vars->args)
		free(parsing->vars->args);
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
	fill_args(&parsing); // DEBUG
	debug_print_args(parsing.vars->args, parsing.vars->num_args); // DEBUG
	expand_tokens(&parsing);
	token_trim_white(&parsing);
	token_trim_quotes(&parsing);
	// token_trim_quotes(&parsing);
	// token_trim_quotes(&parsing);
	display_token_list(parsing.token_list); // DEBUG
	printf("total cmds: %d\n", parsing.num_cmds);
	syntax_errors(&parsing);
}
