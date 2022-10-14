/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:05:28 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/15 16:47:29 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
		The  memcmp() function compares the first n bytes (each interpreted 
		as unsigned char) of the  memory  areas  s1 and s2.
*/
#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			i;
	unsigned char	*pts1;
	unsigned char	*pts2;

	pts1 = (unsigned char *)str1;
	pts2 = (unsigned char *)str2;
	i = 0;
	while (i < n)
	{
		if (pts1[i] != pts2[i])
			return ((pts1[i]) - pts2[i]);
		i++;
	}
	return (0);
}
