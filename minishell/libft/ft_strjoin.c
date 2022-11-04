/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:46:31 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/04 13:22:27 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Description Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.
*/
#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	p[i] = '\0';
	return (p);
}
