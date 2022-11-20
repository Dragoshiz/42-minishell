/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:19:46 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/20 15:30:31 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_custom_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	p[i] = '\0';
	if (*s1)
		free(s1);
	return (p);
}

static void	ft_get_hrdoc2(t_iovars *iov, char *line)
{
	free(line);
	g_exit = 0;
	close(iov->hrdc_pipe[1]);
}

void	ft_get_hrdoc(t_token *current, t_iovars *iov)
{
	char		*line;
	char		*delim;
	size_t		size_delim;
	t_token		*curr;

	curr = current->next;
	delim = curr->data;
	iov->hv_heredoc = 1;
	curr->type = 6;
	size_delim = ft_strlen(delim);
	pipe(iov->hrdc_pipe);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return ;
		if ((ft_strncmp(line, delim, size_delim) == 0)
			&& (ft_strlen(line) == size_delim))
			break ;
		line = ft_custom_strjoin(line, "\n");
		write(iov->hrdc_pipe[1], line, ft_strlen(line));
		free(line);
	}
	ft_get_hrdoc2(iov, line);
}
