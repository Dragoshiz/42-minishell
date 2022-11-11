/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 21:48:33 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/11 16:58:01 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
1. if type zero and not the first token -> print
2. if second token is "-n" then print without newlines

print all folling arguments with type 0 in current pipe
*/

static void	echo_print(t_vars *vars, int opt)
{
	(void)vars;
	if (opt == 2)
		printf("ECHO\n"); // DEBUG
	else if (opt == 1)
		printf("ECHO -n\n"); // DEBUG
}

void	ft_echo(t_vars *vars)
{
	t_token	*curr;
	int		pipe_nr;

	curr = vars->parse->token_list->head;
	pipe_nr = curr->pipe_nbr;
	if (ft_strncmp(curr->data, "echo", 4) == 0)
	{
		if ((curr->next != NULL && curr->next->data[0] == '-'))
			echo_print(vars, 1);
		else if (curr->next != NULL)
			echo_print(vars, 2);
		g_exit = 0;
	}
}
