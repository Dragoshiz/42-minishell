/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:32:34 by dimbrea           #+#    #+#             */
/*   Updated: 2021/12/30 23:00:20 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
       The calloc() function allocates memory for an array of nmemb elements
       of  size  bytes  each  and returns a pointer to the allocated memory.
       The memory is set to zero.  If nmemb or size is 0, then calloc()  re‐
       turns  either  NULL, or a unique pointer value that can later be suc‐
       cessfully passed to free().  If the multiplication of nmemb and  size
       would result in integer overflow, then calloc() returns an error.  By
       contrast, an integer overflow would not be detected in the  following
       call  to malloc(), with the result that an incorrectly sized block of
       memory would be allocated:
           malloc(nmemb * size);
RETURN VALUE
       The malloc() and calloc() functions return a pointer to the allocated
       memory,  which  is suitably aligned for any built-in type.  On error,
       these functions return NULL.  NULL may also be returned by a success‐
       ful  call to malloc() with a size of zero, or by a successful call to
       calloc() with nmemb or size equal to zero.
*/
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = malloc(nmemb * size);
	if (p == NULL)
		return (NULL);
	ft_memset(p, 0, nmemb * size);
	return (p);
}
