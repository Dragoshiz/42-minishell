/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:38:33 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/25 17:26:40 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	peek(char *line, char s)
{
	// char	*ps;
	// char	*pe;
	int	i;

	i = 0;
	while (line[i])
	{
		if(line[i] == s)
			return (1);
		i++;
	}
	return (0);
}

void	parsing(t_vars *vars)
{
	char	*line;
	int		len_line;

	line = ft_strdup(vars->line); // TODO protect 
	if (peek(line, 39))
		printf("contains single quote in line\n");
	// i = 0;
	// if (!ft_strncmp(line, "ENV", 3)) // DEBUG
	// {
	// 	while (vars->env_sh[i])
	// 		printf("%s\n", vars->env_sh[i++]);
	// }
	// else
	// 	printf("copy of line: %s\n", line);
	//displayLinkedList(vars->env_list);
	free(line);
}
