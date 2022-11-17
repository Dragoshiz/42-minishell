/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:00:50 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/17 12:02:09 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
description Outputs the string ’s’ to the given file
descriptor.
*/
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = 0;
	len = ft_strlen(s);
	write(fd, s, len);
}
