/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:27:00 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/21 17:08:25 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	get_var_name_len(t_parsing *parsing, void *data, int ix, int i);
static char	*get_var_value(t_parsing *parsing, void *data);
static char	*write_expanded_string(t_parsing *parsing, int i, char *str, \
char *p);

// function to insert the expanded string
char	*insert_expanded_string(t_parsing *parsing, void *data)
{
	int		i;
	int		j;
	char	*p;
	char	*str;

	parsing->var_name_len = 0;
	i = parsing->ix + 1;
	i = get_var_name_len(parsing, data, parsing->ix, i);
	str = get_var_value(parsing, data);
	i = 0;
	p = ft_calloc((parsing->p_len + 1), sizeof(char));
	j = 0;
	while (i < parsing->ix)
	{
		p[i] = str[j];
		i++;
		j++;
	}
	p = write_expanded_string(parsing, i, str, p);
	free(parsing->var_name);
	free(parsing->var_value);
	free(str);
	return (p);
}

static int	get_var_name_len(t_parsing *parsing, void *data, int ix, int i)
{
	char	*str;

	str = ft_strdup(data);
	if (ft_isdigit(str[ix + 1]) || is_quote_char(str[ix + 1]))
	{
		str[ix + 2] = '\0';
		parsing->var_name_len = 1;
		i = 1;
	}
	else if (!ft_isdigit(str[ix + 1]))
	{
		while (str[i])
		{
			if (!is_variable_char(str[i]))
			{
				str[i] = '\0';
				break ;
			}
			parsing->var_name_len++;
			i++;
		}
	}
	parsing->var_name = ft_strdup(&str[ix + 1]);
	free (str);
	return (i);
}

static char	*get_var_value(t_parsing *parsing, void *data)
{
	t_node	*current;
	char	*str;

	str = NULL;
	current = parsing->vars->env_list->head;
	while (current)
	{
		if (ft_strncmp(current->data, parsing->var_name, \
		parsing->var_name_len) == 0)
		{
			parsing->var_value = ft_strdup(&current->data[parsing->\
			var_name_len + 1]);
			parsing->var_value_len = ft_strlen(parsing->var_value);
			break ;
		}
		current = current->next;
	}
	parsing->p_len = ft_strlen(data) - (ft_strlen(parsing->var_name) + 1) \
	+ parsing->var_value_len;
	str = ft_strdup(data);
	return (str);
}

static char	*write_expanded_string(t_parsing *parsing, int i, char *str, \
char *p)
{
	int	j;

	j = 0;
	if (parsing->var_value_len > 0)
	{
		while (j < parsing->var_value_len)
		{
			p[i] = parsing->var_value[j];
			i++;
			j++;
		}
		j = 0;
	}
	while (i < parsing->p_len)
	{
		p[i] = str[j + parsing->ix + parsing->var_name_len + 1];
		i++;
		j++;
	}
	p[i] = '\0';
	return (p);
}
