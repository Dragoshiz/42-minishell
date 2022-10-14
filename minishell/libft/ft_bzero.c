/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:19:22 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/04 19:54:01 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The  bzero() function erases the data in the n bytes of the memory 
starting at the location pointed to by s, by  writing  zeros
(bytes containing '\0') to that area.
The  bzero() function erases the data in the n bytes of the mem
ory starting at the location pointed to by s, by  writing  zeros
RETURN VALUE None.
*/
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptc;
	size_t	i;

	i = 0;
	ptc = (char *)s;
	while (i < n)
	{
		ptc[i] = '\0';
		i++;
	}
}
