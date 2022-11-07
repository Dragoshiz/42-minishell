/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:53:03 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/04 17:19:33 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Description Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.
afewawef/feaafwef/faefdsa/file
../
*/

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		i;
	int		j;

	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, (int)s1[i]) != NULL)
		i++;
	j = ft_strlen(s1) - 1;
	while (j > i && ft_strchr(set, (int)s1[j]) != NULL)
		j--;
	trimmed = malloc((j - i + 2) * sizeof(char));
	if (trimmed == NULL)
		return (NULL);
	ft_strlcpy(trimmed, s1 + i, (j - i) + 2);
	return (trimmed);
}
