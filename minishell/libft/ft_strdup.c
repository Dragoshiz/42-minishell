/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:57:16 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/04 14:49:27 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
       The strdup() function returns a pointer to a new string which is
       a duplicate of the string s.  Memory for the new string  is  ob‐
       tained with malloc(3), and can be freed with free(3).
*/
#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*p;
	int		len;

	len = ft_strlen(src);
	p = malloc(sizeof(char) * len + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		p[i] = src[i];
		i++;
	}
	p[len] = '\0';
	return (p);
}
