/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:54:48 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/28 17:27:10 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// duplicates str-range from p_start to p_end and gives back a pointer to it.
char	*dup_range(char *p_start, char *p_end)
{
	int		i;
	char	*p;
	int		len;

	len = 0;
	while(p_start[len] != *p_end)
		len++;
	p = malloc(sizeof(char) * len + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = p_start[i];
		i++;
	}
	p[len] = '\0';
	return (p);
}

// search s between p_start and end of line and return pointer to first occurence
char	*peek(char *p_start, char *line_end, char s)
{
	char	*p;
	int		i;

	i = 0;
	p = NULL;
	while (p_start[i] != *line_end)
	{
		if (p_start[i] == s)
		{
			p = &p_start[i];
			return (p);
		}
		i++;
	}
	return (p);
}
