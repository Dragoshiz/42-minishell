/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:11:27 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/07 09:50:37 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
checks for a digit (0 through 9)
The values returned are nonzero if the character c falls  into  the
tested class, and zero if not.
*/
#include "libft.h"

int	ft_isdigit(int ch)
{
	if ((ch >= '0') && (ch <= '9'))
	{
		return (ch);
	}
	return (0);
}
