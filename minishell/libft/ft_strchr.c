/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 09:56:46 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/06 15:39:48 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The  strchr()  function  returns  a  pointer  to the first 
occurrence of the character c in the string s.
Here "character" means "byte"; these functions do not work with wide 
or multibyte characters.
*/
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (c == '\0' && *(str) == '\0')
		return ((char *)str);
	return (NULL);
}
