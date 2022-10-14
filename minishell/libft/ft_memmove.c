/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shoppe <shoppe@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:20:13 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/15 20:59:05 by shoppe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
       The  memmove()  function copies n bytes from memory area src
       to memory area dest.  The memory areas may overlap:  copying
       takes place as though the bytes in src are first copied into
       a temporary array that does not overlap src or dest, and the
       bytes are then copied from the temporary array to dest.
*/
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*ptdest;
	char	*ptsrc;
	size_t	i;

	ptsrc = (char *)src;
	ptdest = (char *)dest;
	if (src > dest)
	{
		i = 0;
		while (i < n)
		{
			ptdest[i] = ptsrc[i];
			i++;
		}
	}
	if (src < dest)
	{
		i = n;
		while (i--)
			ptdest[i] = ptsrc[i];
	}
	return (ptdest);
}
