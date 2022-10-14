/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:45:42 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/16 15:43:19 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Description			Applies the function f to each character of the
					string passed as argument, and passing its index
					as first argument. Each character is passed by
					address to f to be modified if necessary
*/
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;
	int	len;

	if (!s || !f)
		return ;
	len = ft_strlen(s);
	i = 0;
	if (s != NULL)
	{
		while (i < len)
		{
			(*f)(i, (s + i));
			i++;
		}
	}
}
