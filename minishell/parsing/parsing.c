/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:38:33 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/05 23:44:19 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_quote_pairs(char *p, int *ref, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(str[i])
	{
		if (ref[i] != 1)
		{
			p[j] = str[i];
			j++;
		}
		i++;
	}
	p[j] = '\0';
}

void	token_trim_quotes(t_parsing *parsing) // TODO possible leaks
{
	t_token		*current;
	char		*p;
	int			*ref;
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
	ref = NULL;
	while (current)
	{
		m1 = -1;
		m2 = -1;
		i = 0;
		quote = '\0';
		len = ft_strlen(current->data);
		ref = ft_calloc(len + 1, sizeof(int));
		len_p = len;
		while (current->data[i])
		{
			if ((current->data[i] == d_quote || current->data[i] == s_quote) && m1 >= 0 && current->data[i] != quote)
			{
				ref[i] = -1;
			}
			if ((current->data[i] == d_quote || current->data[i] == s_quote) && m1 < 0)
			{
				quote = current->data[i];
				m1 = i;
			}
			else if (current->data[i] == quote && m2 < 0)
			{
				m2 = i;
				ref[m1] = 1;
				ref[m2] = 1;
				current->type = 1;
				m1 = -1;
				m2 = -1;
				quote = '\0';
				len_p = len_p - 2;
			}
			i++;
		}
		p = ft_calloc((len_p + 1), sizeof(char));
		remove_quote_pairs(p, ref, current->data);
		free(current->data);
		current->data = p;
		current = current->next;
		free(ref);
	}
}

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
		ft_putstr_fd("minish: syntax error near unexpected token '|' \n", 1);
	if (parsing->vars->syntax_error == 2)
		ft_putstr_fd("minish: syntax error unclosed quote \n", 1);
	if (parsing->vars->syntax_error == 3)
		ft_putstr_fd("minish: syntax error empty cmd \n", 1);
	if (parsing->vars->syntax_error == 4)
		ft_putstr_fd("minish: syntax error empty redirection \n", 1);
	if (parsing->vars->syntax_error == 5)
		ft_putstr_fd("minish: syntax error (redirection) \n", 1);
}

static void	debug_print_args(char *args[], int num_args) // DEBUG print args
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (i < num_args)
	{
		ft_putstr_fd("arg[", 1);
		temp = ft_itoa(i);
		ft_putstr_fd(temp, 1);
		free(temp);
		ft_putstr_fd("]:\t\t\t\t$", 1);
		ft_putstr_fd(args[i], 1);
		ft_putstr_fd("$\n", 1);
		i++;
	}
}

void	parsing_cleanup(t_parsing *parsing)
{
	delete_list(parsing->pipeline);
	free(parsing->pipeline);
	delete_token_list(parsing->token_list); // TODO Segfaults
	free(parsing->token_list);
	ft_free_doublepoint(parsing->vars->args);
	free(parsing->vars->args);
	delete_list(parsing->vars->env_list); // TODO
	free(parsing->vars->env_list); // TODO
	free(parsing->vars->env_sh); // TODO
}

// Main function for Parsing & initial checks
void	parsing(t_vars *vars, t_parsing *parsing)
{
	initialize_parsing(parsing, vars);
	initialize_pipeline(parsing);
	split_pipeline(parsing);
	initialize_token_list(parsing);
	split_tokens(parsing);
	expand_tokens(parsing);
	token_trim_white(parsing);
	token_trim_quotes(parsing);
	fill_args(parsing); // DEBUG
	debug_print_args(parsing->vars->args, parsing->vars->num_args); // DEBUG
	display_token_list(parsing->token_list); // DEBUG
	edge_cases(parsing);
	syntax_errors(parsing);
}
