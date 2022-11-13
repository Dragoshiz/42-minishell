/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 21:48:33 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/13 11:05:34 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	echo_print(t_token *curr, int pipe_nr, int opt)
{
	while (curr && curr->pipe_nbr == pipe_nr)
	{
		if (curr->type == 0)
			ft_putstr_fd(curr->data, 1);
		if (curr->next && curr->next->pipe_nbr == pipe_nr)
			ft_putstr_fd(" ", 1);
		curr = curr->next;
	}
	if (opt == 0)
		ft_putstr_fd("\n", 1);
	g_exit = 0;
}

void	ft_echo(t_vars *vars)
{
	t_token	*curr;
	int		pipe_nr;

	curr = vars->parse->token_list->head;
	pipe_nr = curr->pipe_nbr;
	if (curr->next && ft_strncmp(curr->next->data, "-n", 2) == 0)
	{
		curr = curr->next->next;
		echo_print(curr, pipe_nr, 1);
	}
	else
	{
		curr = curr->next;
		echo_print(curr, pipe_nr, 0);
	}
}
