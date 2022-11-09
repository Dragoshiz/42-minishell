/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:03:59 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/09 04:49:42 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	add_token_quotes(t_parsing *p, char *str)
{
	p->p_start = &str[p->ix];
	while (p->q_open != NULL && str[p->ix])
	{
		p->ix++;
		check_token_quotes(p, str, p->ix);
	}
	p->p_end = &str[p->ix];
	add_token(p, dup_range(&p->p_start[1], p->p_end), 0);
}

static void	add_token_opt(t_parsing *p, char *str, int opt)
{
	int	i;

	if (opt == 1)
	{
		p->p_start = &str[p->ix];
		seek_word_r(p, str);
		p->p_end = &str[p->ix];
		if (p->q_open != NULL)
			p->p_end = &str[p->ix - 1];
		add_token(p, dup_range(p->p_start, p->p_end), 0);
		p->ix--;
	}
	if (opt == 2)
	{
		i = p->ix;
		p->p_start = &str[p->ix];
		seek_red_r(p, str);
		p->p_end = &str[p->ix];
		add_token(p, dup_range(p->p_start, p->p_end), \
		token_value_red(p, str, i));
		p->ix--;
	}
}

static void	check_string(t_parsing *p, char *str)
{
	p->ix = 0;
	while (str[p->ix])
	{
		check_token_quotes(p, str, p->ix);
		if (p->q_open == NULL)
		{
			if (is_word_c(str[p->ix]))
				add_token_opt(p, str, 1);
			else if (is_redc(str[p->ix]))
				add_token_opt(p, str, 2);
			else if (is_whs_c(str[p->ix]))
			{
				p->p_start = &str[p->ix];
				seek_whs_r(p, str);
				p->p_end = &str[p->ix];
				p->ix--;
			}
		}
		if (p->q_open != NULL)
			add_token_quotes(p, str);
		p->ix++;
	}
}

static void	init_split_tokens(t_parsing *p, char *str)
{
	int		len;

	len = ft_strlen(str);
	p->p_start = str;
	p->p_end = &str[len];
	p->line_end = &str[len];
	p->q_open = NULL;
	p->quote = '\0';
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
