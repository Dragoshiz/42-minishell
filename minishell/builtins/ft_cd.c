/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:55:15 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/11 16:18:54 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_vars *vars)
{
	t_token	*curr;
	int		pipe_nr;
	char	*home;

	curr = vars->parse->token_list->head;
	pipe_nr = curr->pipe_nbr;
	home = getenv("HOME");
	if (strncmp(curr->data, "cd", 2) == 0)
	{
		if ((curr->next != NULL && curr->next->pipe_nbr != pipe_nr)
			|| curr->next == NULL)
			chdir(home);
		else if (curr->next->pipe_nbr == pipe_nr && curr->next)
		{
			if (chdir(curr->next->data) != 0)
			{
				printf("minishell: cd: %s: No such file or directory\n"\
					, curr->next->data);
				g_exit = 1;
			}
		}
		g_exit = 0;
	}
}
