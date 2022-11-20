/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:03:59 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/20 15:48:46 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	add_word_token(t_parsing *p, char *str, t_node *current);
static void	add_redir_token(t_parsing *p, char *str, t_node *current);
static void	check_string(t_parsing *p, char *str, t_node *current);
static void	check_string2(t_parsing *p, char *str, t_node *current);

// splits into tokens. 0 if cmd or word, 1 >, 2 <, 3 >>, 4 <<
void	split_tokens(t_parsing *parsing)
{
	char	*str;
	t_node	*current;

	current = parsing->pipeline->head;
	while (current)
	{
		str = current->data;
		init_split_tokens(parsing, str);
		check_string(parsing, str, current);
		if (parsing->q_open != NULL)
			parsing->vars->syntax_error = 2;
		current = current->next;
	}
	parsing->token_nbr = count_token_list(parsing->token_list);
}

static void	add_word_token(t_parsing *p, char *str, t_node *current)
{
	p->p_end = &str[p->ix + 1];
	add_token(p, dup_range(p->p_start, p->p_end), 0, current);
	p->p_start = p->p_end;
}

static void	add_redir_token(t_parsing *p, char *str, t_node *current)
{
	int	i;

	i = p->ix;
	p->p_start = &str[p->ix];
	if (!is_redc(str[p->ix + 1]))
	{
		p->p_end = &str[p->ix + 1];
		add_token(p, dup_range(p->p_start, p->p_end), \
		token_value_red(p, str, i), current);
		p->p_start = p->p_end;
	}
	else
	{
		seek_red_r(p, str);
		p->p_end = &str[p->ix];
		add_token(p, dup_range(p->p_start, p->p_end), \
		token_value_red(p, str, i), current);
		p->p_start = p->p_end;
		check_token_quotes(p, str, p->ix);
	}
}

static void	check_string2(t_parsing *p, char *str, t_node *current)
{
	if (p->ix > 0 && !is_whs_c(str[p->ix - 1]) \
		&& !is_redc(str[p->ix - 1]))
	{
		p->p_end = &str[p->ix];
		add_token(p, dup_range(p->p_start, p->p_end), 0, current);
		p->p_start = &p->p_end[1];
	}
}

static void	check_string(t_parsing *p, char *str, t_node *current)
{
	p->ix = 0;
	while (str[p->ix])
	{
		check_token_quotes(p, str, p->ix);
		if (p->q_open == NULL)
		{
			if (is_redc(str[p->ix]))
				add_redir_token(p, str, current);
			else if (is_whs_c(str[p->ix]))
			{
				check_string2(p, str, current);
			}
			else if (is_word_c(str[p->ix]) && is_redc(str[p->ix + 1]))
				add_word_token(p, str, current);
		}
		if (!str[p->ix])
			break ;
		if (str[p->ix + 1] == '\0' && !is_whs_c(str[p->ix]) \
		&& !is_redc(str[p->ix]))
			add_token(p, dup_range(p->p_start, p->line_end), 0, current);
		p->ix++;
	}
}
