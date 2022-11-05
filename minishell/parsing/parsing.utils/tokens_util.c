/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:03:59 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/05 21:35:43 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
int	is_whitespace_char(char c)
{
	if (c != 32 && !(c >= 9 && c <= 13))
		return (0);
	return (1);
}

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
void	add_token(t_parsing *parsing, void *data)
{
	t_token	*node;

	node = ft_calloc(1, sizeof(t_token));
	node->data = data;
	node->pipe_nbr = parsing->num_cmds;
	node->type = 0;
	node->next = NULL;
	if (parsing->token_list->head == NULL)
		parsing->token_list->head = node;
	else
		parsing->token_list->tail->next = node;
	parsing->token_list->tail = node;
}

// DEBUG prints the list
void	display_token_list(t_token_list *list)
{
	t_token	*current;
	char	*temp;

	current = list->head;
	temp = NULL;
	while (current != NULL)
	{
		ft_putstr_fd("token[pipe #", 1);
		temp = ft_itoa(current->pipe_nbr);
		ft_putstr_fd(temp, 1);
		free(temp);
		ft_putstr_fd(" type: ", 1);
		temp = ft_itoa(current->type);
		ft_putstr_fd(temp, 1);
		free(temp);
		ft_putstr_fd("]:\t\t$", 1);
		ft_putstr_fd(current->data, 1);
		ft_putstr_fd("$\n", 1);
		current = current->next;
	}
}

void	delete_token_list(t_token_list *list)
{
	t_token			*temp;

	while (list->head != NULL)
	{
		temp = list->head;
		list->head = list->head->next;
		free(temp->data);
		free(temp);
	}
}
