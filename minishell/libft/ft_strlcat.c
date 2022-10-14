/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:11:01 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/10 17:42:00 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
       The  strcat()  function  appends  the  src string to the dest string,
       overwriting the terminating null byte ('\0') at the end of dest,  and
       then  adds a terminating null byte.  The strings may not overlap, and
       the dest string must have enough space for the result.   If  dest  is
       not  large enough, program behavior is unpredictable; buffer overruns
       are a favorite avenue for attacking secure programs.
       As  with strcat(), the resulting string in dest is always null-termi‐
       nated.

       If src contains n or more bytes, strncat() writes n+1 bytes  to  dest
       (n  from src plus the terminating null byte).  Therefore, the size of
       dest must be at least strlen(dest)+n+1.
*/
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dlen;
	size_t	i;
	size_t	j;
	size_t	vsize;

	vsize = size;
	dlen = ft_strlen(dest);
	i = 0;
	if (dlen < size)
	{
		vsize = dlen;
		j = size - dlen - 1;
		while (i < j && src[i] != '\0')
		{	
			dest[dlen] = src[i];
			i++;
			dlen++;
		}
		dest[dlen] = '\0';
	}
	return (vsize + ft_strlen(src));
}
