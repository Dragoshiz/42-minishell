/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:03:59 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/03 17:04:22 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*insert_expanded_string(t_linked_list *env_list, void *data, int index)
{
	char	*str;
	t_node	*current;
	int		i;
	int		var_name_len;
	char	*var_name;
	char	*var_value;
	

	i = index + 1; // + 1 to pass $ sign
	current = env_list->head;
	str = ft_strdup(data);
	var_name_len = 0;
	var_value = NULL;
	while (str[i]) // get variable name length and set null character 
	{
		if (!is_variable_char(str[i]))
		{
			str[i] = '\0';
			break;
		}
		var_name_len++;
		i++;
	}
	var_name = ft_strdup(&str[index + 1]);
	free (str);
	while (current)
	{
		if (ft_strncmp(current->data, var_name, var_name_len) == 0)
		{
			var_value = ft_strdup(&current->data[var_name_len + 1]);
			break;
		}
		current = current->next;
	}
	
	return (var_value);
}

void	check_expansion_quotes(char *quote, int *status, char c)
{
	if (c == DQUOTE && (*status == 0))
		*quote = c;
	if (c == SQUOTE && (*status == 0) && *quote != DQUOTE)
	{
		*status = 1;
		*quote = c;
	}
	else if (*quote == c)
		*status = 0;
}

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

//function that checks for whitespace characters
int	is_variable_char(char c)
{
	if (c != 95 && !(c >= 48 && c <= 57) && !(c >= 65 && c <= 90) && !(c >= 97 && c <= 122))
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
	node->pipe_nbr = parsing->num_pipes;
	node->type = NULL;
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

	current = list->head;
	while (current != NULL)
	{
		printf("token[pipe#%d]: $%s$\n", current->pipe_nbr, current->data); // DEBUG remove $ for production
		current = current->next;
	}
}

void	delete_token_list(t_token_list *list)
{
	t_token	*temp;

	if (list->current == list->head)
	{
		if (list->head->next == NULL)
			list->head = list->tail = NULL;
		else
			list->head = list->head->next;
	}
	else
	{
		temp = list->head;
		while (temp != NULL && temp->next != list->current)
		{
			free (temp->data);
			temp = temp->next;
		}
		if (temp != NULL)
			temp->next = list->current->next;
	}
	free(list->current);
	if (list)
		free(list);
}