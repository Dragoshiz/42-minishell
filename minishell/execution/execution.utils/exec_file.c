/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:12:35 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/03 10:58:28 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exec_file(t_parsing *parsing)
{
	int		i;
	t_token	*current;

	current = parsing->token_list->head;
	i = 0;
	while (current != NULL)
	{
		printf("%s",current->data);
		current = current->next;
	}
}

