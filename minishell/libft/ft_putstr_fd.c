/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:00:50 by dimbrea           #+#    #+#             */
/*   Updated: 2022/01/04 16:21:54 by dimbrea          ###   ########.fr       */
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

	len = ft_strlen(s);
	write(fd, s, len);
}
