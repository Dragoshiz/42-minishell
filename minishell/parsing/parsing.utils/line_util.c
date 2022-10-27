/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:54:48 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/27 15:56:05 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// return (1) if char s is present in string line, otherwise return (0)
int	peek(char *line, char s, int i)
{
	if ((size_t)i <= ft_strlen(line))
	{
		while (line[i])
		{
			if (line[i] == s)
				return (i);
			i++;
		}
	}
	return (-1);
}