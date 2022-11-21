/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:24:01 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/21 13:09:40 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_get_meta(t_token *current, int type, t_iovars *iov)
{
	int	fd;

	fd = 0;
	if (type == 1)
		fd = ft_get_fin(current);
	else if (type == 2)
	{
		fd = ft_overwrite(current);
		iov->hv_out = 1;
	}
	else if (type == 3)
		ft_get_hrdoc(current, iov);
	else if (type == 4)
	{
		fd = ft_appnd(current);
		iov->hv_out = 1;
	}
	return (fd);
}

//ft_creates pipes
void	ft_create_pipes(t_parsing *parse, t_iovars *iov)
{
	int	i;

	i = 0;
	if (parse->num_cmds == 1)
		return ;
	iov->pipefds = malloc(sizeof(int *) * parse->num_cmds);
	while (i < parse->num_cmds - 1)
	{
		iov->pipefds[i] = ft_calloc(sizeof(int), 2);
		if (pipe(iov->pipefds[i]) < 0)
		{
			perror("");
			g_exit = 1;
		}
		i++;
	}
	iov->pipefds[i] = NULL;
}
