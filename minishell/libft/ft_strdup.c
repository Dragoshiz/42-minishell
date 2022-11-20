/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:57:16 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/20 19:25:46 by dimbrea          ###   ########.fr       */
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

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	p = ft_calloc((len + 1), sizeof(char));
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
