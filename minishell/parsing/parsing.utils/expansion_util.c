/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:53:08 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/08 20:47:57 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	expand_var(t_parsing *parsing, t_node *current)
{
	char	*p;

	parsing->len = ft_strlen(current->data);
	while (current->data[parsing->ix])
	{
		parsing->check = 0;
		check_expansion_quotes(&parsing->quote, \
		&parsing->status, current->data[parsing->ix]);
		if (parsing->status == 0 && current->data[parsing->ix] == DOLLAR \
		&& is_variable_char(current->data[parsing->ix + 1]))
		{
			p = insert_expanded_string(parsing, \
			current->data);
			free (current->data);
			current->data = p;
			parsing->check = 1;
			return (parsing->ix);
		}
		parsing->ix++;
	}
	return (parsing->ix);
}

// expands variables in tokens
void	expand_tokens(t_parsing *parsing)
{
	t_node	*current;

	current = parsing->pipeline->head;
	while (current != NULL)
	{
		parsing->check = 0;
		parsing->ix = 0;
		parsing->status = 0;
		parsing->quote = '\0';
		while (1)
		{
			parsing->ix = expand_var(parsing, current);
			if ((parsing->ix == parsing->len && parsing->check == 0) \
			|| parsing->len == 0)
				break ;
			parsing->ix = 0;
			parsing->status = 0;
			parsing->quote = '\0';
		}
		current = current->next;
		if (current == NULL)
			break ;
	}
	parsing->len = 0;
}
