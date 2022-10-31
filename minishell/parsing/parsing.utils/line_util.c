/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:54:48 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/30 17:45:25 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Initialize parsing struct
void	initialize_line(t_parsing *parsing)
{
	parsing->p_start = parsing->s_vars->line;
	parsing->p_end = parsing->line_end;
	parsing->q_open = NULL;
	parsing->quote = '\0';
}

// duplicates str-range from p_start to p_end and gives back a pointer to it.
char	*dup_range(char *p_start, char *p_end)
{
	int		i;
	char	*p;
	int		len;

	len = 0;
	while (&p_start[len] != p_end)
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
