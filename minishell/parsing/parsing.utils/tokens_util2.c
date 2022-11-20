/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:21:45 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/20 15:32:59 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// checks if in quoted area
void	check_token_quotes(t_parsing *parsing, char *str, int i)
{
	if ((str[i] == SQUOTE || \
	str[i] == DQUOTE) && (parsing->q_open == NULL))
	{
		parsing->q_open = &str[i];
		parsing->quote = str[i];
	}
	else if (parsing->quote == str[i])
		parsing->q_open = NULL;
}

//function that checks for whitespace characters
int	is_whs_c(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

// initializes the token list
void	initialize_token_list(t_parsing *parsing)
{
	parsing->token_list = NULL;
	parsing->q_open = NULL;
	parsing->quote = '\0';
	parsing->token_list = ft_calloc(1, sizeof(t_token_list));
	parsing->token_list->head = NULL;
	parsing->token_list->tail = NULL;
	parsing->token_list->current = NULL;
}

// adds a node at the tail
void	add_token(t_parsing *parsing, void *data, int type, t_node *current)
{
	t_token	*node;

	node = NULL;
	if (!is_whitespace(data))
	{
		node = ft_calloc(1, sizeof(t_token));
		node->data = data;
		node->pipe_nbr = current->pipe_nbr;
		node->type = type;
		node->next = NULL;
		if (parsing->token_list->head == NULL)
			parsing->token_list->head = node;
		else
			parsing->token_list->tail->next = node;
		parsing->token_list->tail = node;
		return ;
	}
	free(data);
}

// delete token list
void	delete_token_list(t_token_list *list)
{
	t_token	*temp;

	while (list->head != NULL)
	{
		temp = list->head;
		list->head = list->head->next;
		free(temp->data);
		free(temp);
	}
}
