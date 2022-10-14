/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:00:49 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/04 15:15:47 by dimbrea          ###   ########.fr       */
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
	while (str[n] != '\0')
		n++;
	return (n);
}
