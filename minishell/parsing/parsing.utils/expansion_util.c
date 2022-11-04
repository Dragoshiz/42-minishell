/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:53:08 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/03 20:10:10 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*insert_expanded_string(t_linked_list *env_list, void *data, int index)
{
	char	*str;
	t_node	*current;
	int		i;
	int		j;
	int		var_name_len;
	char	*var_name;
	char	*var_value;
	int		var_value_len;
	int		p_len;
	char	*p;
	

	i = index + 1; // + 1 to pass $ sign
	current = env_list->head;
	str = ft_strdup(data);
	var_name_len = 0;
	var_value_len = 0;
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
			var_value_len = ft_strlen(var_value);
			break;
		}
		current = current->next;
	}
	i = 0;
	p_len = ft_strlen(data) - (ft_strlen(var_name) + 1) + var_value_len;
	p = ft_calloc((p_len + 1), sizeof(char));
	str = ft_strdup(data);
	j = 0;
	while (i < index)
	{
		p[i] = str[j];
		i++;
		j++;
	}
	j = 0;
	if (var_value_len > 0)
	{
		while (j < var_value_len)
		{
			p[i] = var_value[j];
			i++;
			j++;
		}
		j = 0;
	}
	while (i < p_len)
	{
		p[i] = str[j + index + var_name_len + 1];
		i++;
		j++;
	}
	p[i] = '\0';
	free(var_name);
	free(var_value);
	free(str);
	return (p);
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

//function that checks for whitespace characters
int	is_variable_char(char c)
{
	if (c != 95 && !(c >= 65 \
	&& c <= 90) && !(c >= 97 && c <= 122))
		return (0);
	return (1);
}
