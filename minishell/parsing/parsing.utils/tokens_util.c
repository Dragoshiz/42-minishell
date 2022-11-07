/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:03:59 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/07 21:35:38 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	init_split_tokens(t_parsing *parsing, char *str)
{
	int		len;

	len = ft_strlen(str);
	parsing->p_start = str;
	parsing->p_end = &str[len];
	parsing->line_end = &str[len];
	parsing->q_open = NULL;
	parsing->quote = '\0';
}

static void	check_string(t_parsing *parsing, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		check_token_quotes(parsing, str, i);
		if (parsing->q_open == NULL && !is_whitespace_char(str[i]) && \
		is_whitespace_char(str[i + 1]))
		{
			parsing->p_end = &str[i + 1];
			add_token(parsing, dup_range(parsing->p_start, parsing->p_end), 0);
			parsing->p_start = &parsing->p_end[1];
		}
		if (str[i + 1] == '\0' && !is_whitespace_char(str[i]))
			add_token(parsing, dup_range(parsing->p_start, parsing->line_end), \
			0);
		i++;
	}
}

void	split_tokens(t_parsing *parsing)
{
	int		j;
	char	*str;
	t_node	*current;

	current = parsing->pipeline->head;
	j = 0;
	while (current)
	{
		str = current->data;
		init_split_tokens(parsing, str);
		check_string(parsing, str);
		if (parsing->q_open != NULL)
			parsing->vars->syntax_error = 2;
		current = current->next;
		j++;
		parsing->num_cmds = j;
	}
}
