/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:55:04 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/07 20:38:19 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	edge_cases(t_parsing *parsing)
{
	last_pipe_empty(parsing);
	syntax_heredoc(parsing);
	syntax_redirect_output_append(parsing);
	syntax_redirect_output_overwrite(parsing);
	syntax_redirect_input(parsing);
}

void	last_pipe_empty(t_parsing *parsing)
{
	t_node	*current;

	current = parsing->pipeline->tail;
	if (current->data)
	{
		if (is_whitespace(current->data))
			parsing->vars->syntax_error = 3;
	}
}

//function that checks for whitespace characters
static int	is_only_c(char *line, char c)
{
	while (*line)
	{
		if (*line != c)
			return (0);
		line++;
	}
	return (1);
}

void	syntax_heredoc(t_parsing *parsing)
{
	t_token	*current;

	current = parsing->token_list->head;
	while (current)
	{
		if (ft_strlen(current->data) > 2)
		{
			if ((ft_strncmp(current->data, "<<", 2) == 0) && (current->data[2] == '<' || current->data[2] == '>'))
				parsing->vars->syntax_error = 3;
		}
		if (ft_strlen(current->data) < 3 || (is_only_c(current->data, '<')))
		{
			if ((ft_strncmp(current->data, "<<", 2) == 0) && current->next == NULL && current->type != 2)
				parsing->vars->syntax_error = 3;
		}
		if (current->next != NULL && ((ft_strlen(current->data) < 3) || (is_only_c(current->data, '<'))))
		{
			if (ft_strlen(current->data) == 2)
			{
				if ((ft_strncmp(current->data, "<<", 2) == 0) && (is_redirection_char(current->next->data[0])) && current->type != 1 && current->next->type != 1)
						parsing->vars->syntax_error = 3;
			}
			if ((ft_strncmp(current->data, "<<", 2) == 0) && (is_whitespace(current->next->data)) && current->type != 2)
				parsing->vars->syntax_error = 3;
			else if ((ft_strncmp(current->data, "<<", 2) == 0) && (ft_strncmp(current->next->data, "<<", 2) == 0) && current->next->type != 1 && current->type != 1)
				parsing->vars->syntax_error = 3;
		}
		if ((is_only_c(current->data, '<')) && ft_strlen(current->data) > 2 && current->type != 1)
			parsing->vars->syntax_error = 3;
		current = current->next;
	}
}

void	syntax_redirect_output_append(t_parsing *parsing)
{
	t_token	*current;

	current = parsing->token_list->head;
	while (current)
	{
		if (ft_strlen(current->data) > 2)
		{
			if ((ft_strncmp(current->data, ">>", 2) == 0) && (current->data[2] == '<' || current->data[2] == '>'))
				parsing->vars->syntax_error = 4;
		}
		if ((ft_strncmp(current->data, ">>", 2) == 0) && current->next == NULL && current->type != 1)
			parsing->vars->syntax_error = 4;
		if (current->next != NULL)
		{
			if (ft_strlen(current->data) == 2)
			{
				if ((ft_strncmp(current->data, ">>", 2) == 0) && (is_redirection_char(current->next->data[0])) && current->type != 1 && current->next->type != 1)
						parsing->vars->syntax_error = 4;
			}
			if ((ft_strncmp(current->data, ">>", 2) == 0) && (is_whitespace(current->next->data)) && current->type != 1)
				parsing->vars->syntax_error = 4;
			else if ((ft_strncmp(current->data, ">>", 2) == 0) && (ft_strncmp(current->next->data, ">>", 2) == 0) && current->next->type != 1 && current->type != 1)
				parsing->vars->syntax_error = 4;
		}
		if ((is_only_c(current->data, '>')) && ft_strlen(current->data) > 2 && current->type != 1)
			parsing->vars->syntax_error = 4;
		current = current->next;
	}
}

void	syntax_redirect_output_overwrite(t_parsing *parsing)
{
	t_token	*current;

	current = parsing->token_list->head;
	while (current)
	{
		if (ft_strlen(current->data) > 1)
		{
			if ((ft_strncmp(current->data, ">", 1) == 0) && (current->data[1] == '<'))
				parsing->vars->syntax_error = 5;
		}
		if ((ft_strncmp(current->data, ">", 2) == 0) && current->next == NULL && current->type != 1)
			parsing->vars->syntax_error = 5;
		if (current->next != NULL)
		{
			if (ft_strlen(current->data) == 1)
			{
				if ((ft_strncmp(current->data, ">", 1) == 0) && (is_redirection_char(current->next->data[0])) && current->type != 1 && current->next->type != 1)
						parsing->vars->syntax_error = 5;
			}
			if ((ft_strncmp(current->data, ">", 2) == 0) && (is_whitespace(current->next->data)) && current->type != 1)
				parsing->vars->syntax_error = 5;
			else if ((ft_strncmp(current->data, ">", 2) == 0) && (ft_strncmp(current->next->data, ">", 2) == 0) && current->next->type != 1 && current->type != 1)
				parsing->vars->syntax_error = 5;
		}
		current = current->next;
	}
}

void	syntax_redirect_input(t_parsing *parsing)
{
	t_token	*current;

	current = parsing->token_list->head;
	while (current)
	{
		if (ft_strlen(current->data) > 1)
		{
			if ((ft_strncmp(current->data, "<", 1) == 0) && (current->data[1] == '>'))
				parsing->vars->syntax_error = 6;
		}
		if ((ft_strncmp(current->data, "<", 2) == 0) && current->next == NULL && current->type != 1)
			parsing->vars->syntax_error = 6;
		if (current->next != NULL)
		{
			if (ft_strlen(current->data) == 1)
			{
				if ((ft_strncmp(current->data, "<", 1) == 0) && (is_redirection_char(current->next->data[0])) && current->type != 1 && current->next->type != 1)
						parsing->vars->syntax_error = 6;
			}
			if ((ft_strncmp(current->data, "<", 2) == 0) && (is_whitespace(current->next->data)) && current->type != 1)
				parsing->vars->syntax_error = 6;
			else if ((ft_strncmp(current->data, "<", 2) == 0) && (ft_strncmp(current->next->data, "<", 2) == 0) && current->next->type != 1 && current->type != 1)
				parsing->vars->syntax_error = 6;
		}
		current = current->next;
	}
}
