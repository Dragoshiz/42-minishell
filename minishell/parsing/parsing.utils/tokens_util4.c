/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_util4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 03:05:01 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/20 15:43:16 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function to check for redirection errors
void	redir_error_check(t_parsing *p, char *str, int i)
{
	if ((str[i] == '<' && str[i + 1] == '>') || \
	(str[i] == '>' && str[i + 1] == '<') || \
	(is_redc(str[i + 1]) && is_redc(str[i + 2])))
	{
		p->vars->s_err_c = str[i];
		p->vars->syntax_error = 1;
	}
}

// function that returns the redirection token value
int	token_value_red(t_parsing *p, char *str, int i)
{
	redir_error_check(p, str, i);
	if (str[i] == '<' && !is_redc(str[i + 1]))
		return (1);
	else if (str[i] == '>' && !is_redc(str[i + 1]))
		return (2);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (3);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (4);
	else if (str[i] == '<' && str[i + 1] == '>')
		return (1);
	else if (str[i] == '>' && str[i + 1] == '<')
		return (2);
	return (0);
}

// function that trims whitespace
void	token_trim_white(t_parsing *parsing)
{
	t_token		*current;
	char		*p;

	current = parsing->token_list->head;
	while (current)
	{
		p = ft_strtrim(current->data, WHITESPACE);
		free (current->data);
		current->data = p;
		current = current->next;
	}
}

// function that the quote pairs
void	remove_quote_pairs(char *p, int *ref, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
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
