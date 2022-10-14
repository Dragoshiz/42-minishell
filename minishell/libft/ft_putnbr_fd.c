/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:26:40 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/12 18:55:15 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Description Outputs the integer ’n’ to the given file
descriptor.
*/

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	ln;
	long	nn;

	ln = (long)n;
	if (ln < 0)
	{
		ft_putchar_fd('-', fd);
		ln *= -1;
	}
	if (ln >= 10)
	{
		nn = ln % 10;
		ln /= 10;
		ft_putnbr_fd(ln, fd);
		ft_putchar_fd(nn + 48, fd);
		return ;
	}
	ft_putchar_fd(ln + 48, fd);
}
