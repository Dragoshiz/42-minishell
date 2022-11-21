/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:53:08 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/21 16:28:17 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	insert(t_parsing *p, t_node *current, int opt)
{
	char	*str;

	str = NULL;
	if (opt == 0)
		str = insert_expanded_string(p, current->data);
	else if (opt == 1)
		str = insert_exit_status(p, current->data);
	free (current->data);
	current->data = str;
	p->check = 1;
	return (p->ix);
}

static int	expand_var(t_parsing *p, t_node *current)
{
	p->pipelen = ft_strlen(current->data);
	while (current->data[p->ix])
	{
		p->check = 0;
		check_expansion_quotes(&p->quote, &p->status, current->data[p->ix]);
		if (p->status == 0 && current->data[p->ix] == DOLLAR \
		&& is_variable_char(current->data[p->ix + 1]))
			return (insert(p, current, 0));
		else if (p->status == 0 && current->data[p->ix] == DOLLAR \
		&& current->data[p->ix + 1] == '?')
			return (insert(p, current, 1));
		p->ix++;
	}
	return (p->ix);
}

// expands variables in pipes
void	expand_variables(t_parsing *parsing)
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
			if ((parsing->ix == parsing->pipelen && parsing->check == 0) \
			|| parsing->pipelen == 0)
				break ;
			parsing->ix = 0;
			parsing->status = 0;
			parsing->quote = '\0';
		}
		current = current->next;
		if (current == NULL)
			break ;
	}
	parsing->pipelen = 0;
}
