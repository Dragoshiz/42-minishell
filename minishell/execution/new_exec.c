/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:02:50 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/04 16:08:14 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
int	ft_get_hrdoc(t_token *data)
{
	
}
int	ft_get_meta(t_token *data, int i)
{
	int	fd;

	if (i == 0)
		fd = get_hrdoc()
	if (i == 1)

	if (i == 2)

	if (i == 3)

	if (i == 4)

	if (i == 5)
}
int	ft_compare(t_parsing *parse, int pipe_nbr)
{
	const char	**meta[6];
	int			i;
	int			current_pipe;
	t_token		*current;

	current_pipe = first_tkn->pipe_nbr;
	current = first_tkn;
	meta[0] = "<<\0";
	meta[1] = ">>\0";
	meta[2] = "<\0";
	meta[3] = ">\0";
	meta[4] = "$?\0";
	meta[5] = NULL;
	while (current->pipe_nbr != pipe_nbr)
		current = current->next;
	i = 0;
	while (current->pipe_nbr == pipe_nbr)
	{
		while (meta[i])
		{
			if (ft_strncmp(current->data, meta[i],ft_strlen(current->data)))
				call funcion;
			i++;
		}
		current = current->next;
		i = 0;
	}
	return ()
}


void	ft_execv2(t_parsing *parsing, t_iovars *iov)
{
	t_token	*current;
	int i;

	i = 0;
	current = parse->token_list->head;
	while(i < parsing->num_cmds)
	{
		
	}
}
*/