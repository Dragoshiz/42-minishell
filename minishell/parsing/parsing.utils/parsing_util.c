/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:56:45 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/09 04:12:06 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	display_token_list(t_token_list *list)
{
	t_token	*current;
	char	*temp;

	current = list->head;
	temp = NULL;
	while (current != NULL)
	{
		ft_putstr_fd("token[pipe #", 1);
		temp = ft_itoa(current->pipe_nbr);
		ft_putstr_fd(temp, 1);
		free(temp);
		ft_putstr_fd(" type: ", 1);
		temp = ft_itoa(current->type);
		ft_putstr_fd(temp, 1);
		free(temp);
		ft_putstr_fd("]:\t$", 1);
		ft_putstr_fd(current->data, 1);
		ft_putstr_fd("$\n", 1);
		current = current->next;
	}
}

void	debug_print_args(char *args[], int num_args)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (i < num_args)
	{
		ft_putstr_fd("arg[", 1);
		temp = ft_itoa(i);
		ft_putstr_fd(temp, 1);
		free(temp);
		ft_putstr_fd("]:\t\t\t\t$", 1);
		ft_putstr_fd(args[i], 1);
		ft_putstr_fd("$\n", 1);
		i++;
	}
}

int	is_word_c(char c)
{
	if (is_whs_c(c) || is_quote_char(c) || is_redc(c))
		return (0);
	return (1);
}
