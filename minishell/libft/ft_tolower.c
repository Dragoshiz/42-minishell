/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:49:17 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/04 16:12:33 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: This function receives an iteger, treats it as a character, 
returning the lowercase variant if the input variable is a upper case letter. 
Otherwise it's returning the same symbol.
*/
#include "libft.h"

int	ft_tolower(int ch)
{
	if (ch > 64 && ch < 91)
		return (ch + 32);
	return (ch);
}
