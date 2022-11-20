/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 21:48:33 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/20 12:34:53 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	echo_print(t_token *curr, int pipe_num, int opt, int fd)
{
	if (curr->type == 0)
	{
		while (curr && curr->type == 0 && curr->pipe_nbr == pipe_num)
		{
			ft_putstr_fd(curr->data, fd);
			if (curr->next && curr->next->pipe_nbr == pipe_num)
				ft_putstr_fd(" ", fd);
			curr = curr->next;
		}
	}
	if (opt == 0)
		ft_putstr_fd("\n", fd);
	g_exit = 0;
}

static void	ft_echo2(t_token *curr, t_iovars *iov, int pipe_num)
{
	if (!curr->next)
	{
		write(1, "\n", 1);
		return ;
	}
	curr = curr->next;
	if (iov->vars->parse->num_cmds > 1
		&& pipe_num < iov->vars->parse->num_cmds - 1)
		echo_print(curr, pipe_num, 0, iov->pipefds[pipe_num][1]);
	else if (iov->hv_out == 1)
		echo_print(curr, pipe_num, 0, iov->fdout);
	else
		echo_print(curr, pipe_num, 0, 1);
}

void	ft_echo(t_token *curr, t_iovars *iov, int pipe_num)
{
	if (curr->next && ft_strncmp(curr->next->data, "-n", 2) == 0 \
		&& ft_strlen(curr->next->data) == 2)
	{
		if (curr->next->next == NULL)
			return ;
		curr = curr->next->next;
		if (iov->vars->parse->num_cmds > 1)
		{
			echo_print(curr, pipe_num, 1, iov->pipefds[pipe_num][1]);
		}
		else if (iov->hv_out)
			echo_print(curr, pipe_num, 1, iov->fdout);
		else
			echo_print(curr, pipe_num, 1, 1);
	}
	else
		ft_echo2(curr, iov, pipe_num);
}
