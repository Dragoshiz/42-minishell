/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 20:46:19 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/04 12:28:47 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
checks  for an alphabetic character; in the standard "C" locale, 
it is equivalent to (isupper(c)  ||  islower(c)).
In some  locales,  there may be additional characters for which
isalpha() is true—letters which are  neither  uppercase  nor
lowercase.
*/
#include "libft.h"

int	ft_isalpha(int ch)
{
	if ((ch > 64 && ch < 91) || (ch > 96 && ch < 123))
	{
		return (ch);
	}
	return (0);
}
