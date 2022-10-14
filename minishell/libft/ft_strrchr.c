/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:20:24 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/10 15:29:21 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The strrchr() function returns a pointer to the last  occurrence  of  the
	   character c in the string s.
*/
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*found;

	found = NULL;
	while (*str != '\0')
	{
		if (*str == (unsigned char)c)
			found = (char *)str;
		str++;
	}
	if (!found && !c)
		return (found = (char *)str);
	return (found);
}
