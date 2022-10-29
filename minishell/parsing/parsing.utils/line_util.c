/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:54:48 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/29 20:01:43 by vfuhlenb         ###   ########.fr       */
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
	while(&p_start[len] != p_end)
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
