/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:53:08 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/07 20:13:49 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	expand_var(t_parsing *parsing, t_token *current)
{
	char	*p;

	parsing->len = ft_strlen(current->data);
	while (current->data[parsing->index])
	{
		parsing->check = 0;
		check_expansion_quotes(&parsing->quote, \
		&parsing->status, current->data[parsing->index]);
		if (parsing->status == 0 && current->data[parsing->index] == DOLLAR \
		&& is_variable_char(current->data[parsing->index + 1]))
		{
			p = insert_expanded_string(parsing, \
			current->data);
			free (current->data);
			current->data = p;
			parsing->check = 1;
			return (parsing->index);
		}
		parsing->index++;
	}
	return (parsing->index);
}

// expands variables in tokens
void	expand_tokens(t_parsing *parsing)
{
	t_token	*current;

	current = parsing->token_list->head;
	while (current != NULL)
	{
		parsing->check = 0;
		parsing->index = 0;
		parsing->status = 0;
		parsing->quote = '\0';
		while (1)
		{
			parsing->index = expand_var(parsing, current);
			if ((parsing->index == parsing->len && parsing->check == 0) \
			|| parsing->len == 0)
				break ;
			parsing->index = 0;
			parsing->status = 0;
			parsing->quote = '\0';
		}
		current = current->next;
		if (current == NULL)
			break ;
	}
	parsing->len = 0;
}
