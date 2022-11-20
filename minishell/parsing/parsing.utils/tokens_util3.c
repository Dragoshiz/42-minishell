/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_util3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:28:20 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/20 15:46:19 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	init_analyse_quotes(t_parsing *parsing, t_token *current);
static void	mark_dollars(t_parsing *parsing, t_token *current, int *ref);
static void	analyse_quotes(t_parsing *parsing, t_token *current, int *ref);

// function that trims the quotes, including preceeding $ characters
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

static void	analyse_quotes(t_parsing *parsing, t_token *c, int *ref)
{
	int	i;

	i = -1;
	while (c->data[++i])
	{
		if ((c->data[i] == parsing->d_quote || c->data[i] == \
		parsing->s_quote) && parsing->m1 >= 0 && c->data[i] \
		!= parsing->quote)
			ref[i] = -1;
		if ((c->data[i] == parsing->d_quote || c->data[i] == \
		parsing->s_quote) && parsing->m1 < 0)
		{
			parsing->quote = c->data[i];
			parsing->m1 = i;
		}
		else if (c->data[i] == parsing->quote && parsing->m2 < 0)
		{
			parsing->m2 = i;
			ref[parsing->m1] = 1;
			ref[parsing->m2] = 1;
			if (i > 0 && parsing->m1 > 0 && c->data[parsing->m1 - 1] == '$')
				mark_dollars(parsing, c, ref);
			init_analyse_quotes(parsing, c);
		}
	}
}

static void	init_analyse_quotes(t_parsing *parsing, t_token *current)
{
	current->type = 0;
	parsing->m1 = -1;
	parsing->m2 = -1;
	parsing->quote = '\0';
	parsing->p_len = parsing->p_len - 2;
}

static void	mark_dollars(t_parsing *parsing, t_token *current, int *ref)
{
	int	x;

	x = 1;
	while (current->data[parsing->m1 - x] == '$')
	{
		ref[parsing->m1 - x] = 1;
		x++;
		if ((parsing->m1 - x) < 0)
			break ;
	}
}

void	init_split_tokens(t_parsing *p, char *str)
{
	int		len;

	len = ft_strlen(str);
	p->p_start = str;
	p->p_end = &str[len];
	p->line_end = &str[len];
	p->q_open = NULL;
	p->quote = '\0';
}
