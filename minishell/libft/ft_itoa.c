/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:45:14 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/12 18:43:31 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Description 		Allocates (with malloc(3)) and returns a string representing 
					the integer received as an argument. 
					Negative numbers must be handled.
*/
// #include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	ft_digits(long n)
{
	int	digits;

	digits = 0;
	if (n == 0)
	{
		digits++;
		return (digits);
	}
	while (n != 0)
	{
		if (n < 0)
		{
			n *= -1;
			digits++;
		}
		n /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	int		digits;
	char	*p;
	long	ln;

	ln = n;
	digits = ft_digits(ln);
	if (ln < 0)
	ln *= -1;
	p = malloc(sizeof(char) * digits + 1);
	if (p == NULL)
		return (NULL);
	p[digits] = '\0';
	while (digits--)
	{	
		p[digits] = ln % 10 + 48;
		ln /= 10;
	}
	if (n < 0)
		p[0] = '-';
	return (p);
}
