/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:46:28 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/04 12:31:38 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
checks for any printable character including space
The values returned are nonzero if the character c falls  into  the
tested class, and zero if not.
*/
#include "libft.h"

int	ft_isprint(int ch)
{
	if ((ch >= 32) && (ch <= 126))
	{
		return (ch);
	}
	return (0);
}
