/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 21:15:10 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/04 12:29:19 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
checks for an alphanumeric character; 
it is equivalent  to (isalpha(c) || isdigit(c)).
RETURN VALUE
The values returned are nonzero if the character 
c falls into  the  tested  class, and zero if not.
*/
#include "libft.h"

int	ft_isalnum(int ch)
{
	if ((ch > 47 && ch < 58) || (ch > 64 && ch < 91) || (ch > 96 && ch < 123))
		return (ch);
	return (0);
}
