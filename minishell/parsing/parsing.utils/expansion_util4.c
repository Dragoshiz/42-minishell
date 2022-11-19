/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_util4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:27:00 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/19 17:30:54 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	while (i < parsing->p_len && str[j + \
	parsing->ix + parsing->var_name_len + 1])
	{
		p[i] = str[j + parsing->ix + parsing->var_name_len + 1];
		i++;
		j++;
	}
	p[i] = '\0';
	return (p);
}

// function to insert the expanded exit status
char	*insert_exit_status(t_parsing *parsing, void *data)
{
	int		i;
	char	*p;
	char	*str;

	parsing->var_value = ft_itoa(g_exit);
	parsing->var_value_len = ft_strlen(parsing->var_value);
	parsing->var_name_len = 1;
	str = ft_strdup(data);
	parsing->p_len = ft_strlen(str) + parsing->var_value_len;
	p = ft_calloc((parsing->p_len + 1), sizeof(char));
	i = 0;
	while (i < parsing->ix)
	{
		p[i] = str[i];
		i++;
	}
	p = write_expanded_string(parsing, i, str, p);
	free(parsing->var_value);
	free(str);
	return (p);
}

//function that checks for variable characters
int	is_variable_str(char *c)
{
	while (*c)
	{
		if (*c != 95 && !(*c >= 65 \
		&& *c <= 90) && !(*c >= 97 && *c <= 122) && !(*c >= 48 && *c <= 57))
			return (0);
		c++;
	}
	return (1);
}
