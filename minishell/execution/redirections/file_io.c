/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:21:51 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/18 16:23:17 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_get_fin(t_token *current)
{
	int		fdin;
	char	*filename;
	t_token	*curr;

	curr = current->next;
	fdin = 0;
	if (curr->data == NULL)
		return (fdin);
	filename = ft_strdup(curr->data);
	fdin = open(filename, O_RDONLY);
	if (fdin < 0)
	{
		g_exit = 1;
		perror("");
	}
	curr->type = 7;
	free(filename);
	return (fdin);
}

int	ft_appnd(t_token *current)
{
	int		fdout;
	char	*filename;
	t_token	*curr;

	curr = current->next;
	fdout = 1;
	if (curr->data == NULL)
		return (fdout);
	filename = ft_strdup(curr->data);
	fdout = open(filename, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fdout < 0)
	{
		g_exit = 1;
		perror("");
	}
	curr->type = 8;
	free(filename);
	return (fdout);
}

int	ft_overwrite(t_token *current)
{
	int		fdout;
	char	*filename;
	t_token	*curr;

	curr = current->next;
	fdout = 1;
	if (curr->data == NULL)
		return (fdout);
	filename = ft_strdup(curr->data);
	fdout = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fdout < 0)
	{
		g_exit = 1;
		perror("");
	}
	curr->type = 9;
	free(filename);
	return (fdout);
}

int	ft_get_inp(t_iovars *iov, t_parsing *parse, int pipe_nbr)
{
	int			fdin;
	t_token		*curr;

	curr = parse->token_list->head;
	while (curr->pipe_nbr != pipe_nbr)
		curr = curr->next;
	fdin = 0;
	while (curr->pipe_nbr == pipe_nbr && curr != NULL)
	{
		if (curr->type == 1 && curr->next && curr->next->pipe_nbr == pipe_nbr)
			fdin = ft_get_meta(curr, curr->type, iov);
		if (curr->type == 3 && curr->next && curr->next->pipe_nbr == pipe_nbr)
			fdin = ft_get_meta(curr, curr->type, iov);
		if (curr->next == NULL)
			break ;
		curr = curr->next;
	}
	return (fdin);
}

int	ft_get_out(t_iovars *iov, t_parsing *parse, int pipe_nbr)
{
	int			fdout;
	t_token		*curr;

	fdout = 0;
	curr = parse->token_list->head;
	while (curr->pipe_nbr != pipe_nbr)
		curr = curr->next;
	iov->hv_out = 0;
	while (curr->pipe_nbr == pipe_nbr && curr != NULL)
	{
		if (curr->type == 2 && curr->next && curr->next->pipe_nbr == pipe_nbr)
			fdout = ft_get_meta(curr, curr->type, iov);
		if (curr->type == 4 && curr->next && curr->next->pipe_nbr == pipe_nbr)
			fdout = ft_get_meta(curr, curr->type, iov);
		if (curr->next == NULL)
			break ;
		curr = curr->next;
	}
	return (fdout);
}
