/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_util2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:55:14 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/07 17:55:26 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	display_linked_list(t_linked_list *list)
{
	t_node	*current;

	current = list->head;
	while (current != NULL)
	{
		ft_putstr_fd(current->data, 1);
		ft_putchar_fd('\n', 1);
		current = current->next;
	}
}
