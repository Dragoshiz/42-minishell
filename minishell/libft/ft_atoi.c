/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:17:36 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/16 18:43:30 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The  atoi()  function  converts  the  initial  
portion of the string pointed to by str to int.
RETURN VALUE The converted value.
*/
#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sum;
	int	sign;

	i = 0;
	sum = 0;
	sign = 1;
	while ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && str[i])
			i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
			sum = sum * 10 + str[i] - '0';
		else
			break ;
		i++;
	}	
	return (sign * sum);
}
