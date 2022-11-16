/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:11:30 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/16 20:26:35 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * DESCRIPTION
 * Allocates (with malloc(3)) and returns an array of strings
 * obtained by splitting ’s’ using the character ’c’ as a delimiter.
 * The array must be ended by a NULL pointer.
 */
#include "libft.h"

static int	ft_rows(char const *s, char c)
{
	int	i;
	int	rows;

	i = 0;
	rows = 0;
	if (!s[0])
		return (rows);
	while (s[i] == c && s[i] != '\0')
		i++;
	if (s[i] != c && s[i] != '\0')
		rows = 1;
	while (s[++i] != '\0')
	{
		if (s[i] != c && s[i - 1] == c)
			rows++;
	}
	return (rows);
}

static int	ft_make_row(char *s, char c, char **dest, int dest_rows)
{
	int	a;

	a = 0;
	while (s[a] != c && s[a] != '\0')
		a++;
	dest[dest_rows] = (char *)malloc(sizeof(char) * (a + 1));
	if (NULL == dest[dest_rows])
		return (0);
	ft_strlcpy(dest[dest_rows], (char *)s, (size_t)(a + 1));
	return (a);
}

static char	**ft_dest_row(char const *s, char c, char **dest, int rows)
{
	int	i;
	int	dest_rows;
	int	a;

	dest_rows = 0;
	i = 0;
	if (rows > 0)
	{
		while (s[i] == c)
			i++;
		while (dest_rows < rows)
		{
			if (s[i] != c && s[i] != '\0')
			{
				a = ft_make_row((char *)(s + i), c, dest, dest_rows);
				i = i + a;
			}
			dest_rows++;
			while (s[i] == c && s[i] != '\0')
				i++;
		}
	}
	dest[dest_rows] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		rows;

	if (!s)
		return (NULL);
	rows = ft_rows(s, c);
	dest = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!dest)
		return (NULL);
	ft_dest_row(s, c, dest, rows);
	return (dest);
}
