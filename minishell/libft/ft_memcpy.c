/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:48:57 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/16 15:55:10 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
       The memcpy() function copies n bytes from memory area src to
       memory area dest.  The memory areas must not  overlap.   Use
       memmove(3) if the memory areas do overlap.
*/
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*ptd;
	const char	*pts;
	size_t		i;

	if (!dest && !src)
		return (NULL);
	ptd = (char *)dest;
	pts = (const char *)src;
	i = 0;
	while (i < n)
	{
		ptd[i] = pts[i];
		i++;
	}
	return (dest);
}
