/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:53:03 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/12 17:39:41 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DESCRIPTION
	 The strlcpy() and strlcat() functions copy and concatenate strings re‐
	 spectively.  They are designed to be safer, more consistent, and less
	 error prone replacements for strncpy(3) and strncat(3).  Unlike those
	 functions, strlcpy() and strlcat() take the full size of the buffer
	 (not just the length) and guarantee to NUL-terminate the result (as
	 long as size is larger than 0 or, in the case of strlcat(), as long as
	 there is at least one byte free in dst).  Note that a byte for the NUL
	 should be included in size.  Also note that strlcpy() and strlcat()
	 only operate on true “C” strings.  This means that for strlcpy() src
	 must be NUL-terminated and for strlcat() both src and dst must be NUL-
	 terminated.

	 The strlcpy() function copies up to size - 1 characters from the NUL-
	 terminated string src to dst, NUL-terminating the result.

	 The strlcat() function appends the NUL-terminated string src to the end
	 of dst.  It will append at most size - strlen(dst) - 1 bytes, NUL-ter‐
	 minating the result.
*/

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	int		srclen;
	size_t	i;

	srclen = ft_strlen(src);
	i = 0;
	if (n > 0)
	{
		while (src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
			if (i == n)
			{
				i--;
				break ;
			}
		}
		dest[i] = '\0';
	}
	return (srclen);
}
