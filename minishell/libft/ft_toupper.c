/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 21:00:58 by dimbrea           #+#    #+#             */
/*   Updated: 2021/12/03 09:52:40 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: This function receives an integer, treats it as a character, 
returning the uppercase variant if the input variable is a small letter. 
Otherwise it's returning the same symbol.*/
#include "libft.h"

int	ft_toupper(int ch)
{
	if (ch > 96 && ch < 123)
		return (ch - 32);
	else
		return (ch);
}
