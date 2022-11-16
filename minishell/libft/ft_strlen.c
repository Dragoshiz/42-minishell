/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:00:49 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/16 16:14:32 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
strlen - calculate the length of a string
The strlen() function calculates the length of
the string pointed to by s, excluding the terminating null byte ('\0').
*/
#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	if (!str)
		return (n);
	while (str[n])
		n++;
	return (n);
}
