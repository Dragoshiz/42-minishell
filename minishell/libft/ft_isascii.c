/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:21:23 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/04 12:30:00 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
checks  whether  c  is a 7-bit unsigned char value 
that fits into the ASCII character set.
The values returned are nonzero if the character c falls 
into  the tested class, and zero if not.
*/
#include "libft.h"

int	ft_isascii(int ch)
{
	if (ch == 0)
		return (1);
	if (ch > 0 && ch <= 127)
	{
		return (ch);
	}
	return (0);
}
