/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_util3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:28:20 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/09 18:00:22 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	init_analyse_quotes(t_parsing *parsing)
{
	parsing->m1 = -1;
	parsing->m2 = -1;
	parsing->quote = '\0';
	parsing->p_len = parsing->p_len - 2;
}

static void	analyse_quotes(t_parsing *parsing, t_token *current, int *ref)
{
	int	i;

	i = 0;
	while (current->data[i])
	{
		if ((current->data[i] == parsing->d_quote || current->data[i] == \
		parsing->s_quote) && parsing->m1 >= 0 && current->data[i] \
		!= parsing->quote)
			ref[i] = -1;
		if ((current->data[i] == parsing->d_quote || current->data[i] == \
		parsing->s_quote) && parsing->m1 < 0)
		{
			parsing->quote = current->data[i];
			parsing->m1 = i;
		}
		else if (current->data[i] == parsing->quote && parsing->m2 < 0)
		{
			parsing->m2 = i;
			ref[parsing->m1] = 1;
			ref[parsing->m2] = 1;
			current->type = 0;
			init_analyse_quotes(parsing);
		}
		i++;
	}
}

void	token_trim_quotes(t_parsing *parsing)
{
	t_token		*current;
	char		*p;
	int			*ref;

	parsing->p_len = 0;
	current = parsing->token_list->head;
	parsing->len = 0;
	ref = NULL;
	while (current)
	{
		parsing->quote = '\0';
		parsing->len = ft_strlen(current->data);
		ref = ft_calloc(parsing->len + 1, sizeof(int));
		parsing->p_len = parsing->len;
		analyse_quotes(parsing, current, ref);
		p = ft_calloc((parsing->p_len + 1), sizeof(char));
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