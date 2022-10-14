/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:35:42 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/04 14:40:51 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Description Outputs the character ’c’ to the given file
descriptor.
*/
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
