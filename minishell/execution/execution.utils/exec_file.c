/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:12:35 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/03 13:06:18 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exec_file(t_parsing *parsing)
{
	int		pid;
	t_token	*current;

	pid = 0;
	current = parsing->token_list->head;
	while (current != NULL)
	{
		if (access(current->data, F_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				if (execve(current->data, NULL, NULL) < 0)
					perror("");
			}
			waitpid(pid, NULL, 0);
			return (1);
		}
		current = current->next;
	}
	return (0);
}
