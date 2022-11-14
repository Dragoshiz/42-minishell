/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_util4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:27:00 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/14 11:52:17 by vfuhlenb         ###   ########.fr       */
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
	while (i < parsing->p_len)
	{
		p[i] = str[j + parsing->ix + parsing->var_name_len + 1];
		i++;
		j++;
	}
	p[i] = '\0';
	return (p);
}

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
