/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:09:34 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/25 18:06:41 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//check all of the cmd for infile
int	ft_find_in(t_vars *vars, t_iovars *iov)
{
	int		fd;

	iov->i = 0;
	while (vars->args[iov->i])
	{
		iov->j = 0;
		while (vars->args[iov->i][iov->j])
		{
			if (vars->args[iov->i][iov->j - 1] != '<' && vars->args[iov->i] \
				[iov->j] == '<' && vars->args[iov->i][iov->j + 1] == ' ')
			{
				vars->hv_infile = 1;
				iov->filename2 = ft_get_filename(vars->args[iov->i], \
					iov->j + 2);
				fd = open(iov->filename2, O_RDONLY);
				if (fd < 0)
					perror("");
				free(iov->filename2);
			}
			iov->j++;
		}
		iov->i++;
	}
	return (fd);
}

//check if there is an outfile in the cmd and creates it
int	ft_find_out(t_vars *vars, t_iovars *iov, char *arg)
{
	int		i;
	int		fd;

	i = 0;
	while (arg[i++])
	{
		if (arg[i - 1] == ' ' && arg[i] == '>' && arg[i + 1] == ' ')
		{
			vars->hv_outfile = 1;
			iov->filename = ft_get_filename(arg, i + 2);
			fd = open(iov->filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
			free(iov->filename);
		}
		else if (arg[i - 1] == ' ' && arg[i] == '>' && arg[i + 1] == '>'
			&& arg[i + 2] == ' ')
		{
			vars->hv_append = 1;
			iov->filename = ft_get_filename(arg, i + 3);
			fd = open(iov->filename, O_RDWR | O_CREAT | O_APPEND, 0777);
			free(iov->filename);
		}
		if (fd < 0)
			perror("");
	}
	return (fd);
}

//check if there is an heredoc in the cmd
void	ft_find_hdoc(t_vars *vars, char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ' && cmd[i] == '<' && cmd[i + 1] == '<'
			&& cmd[i + 2] == ' ')
			vars->hv_heredoc = 1;
		i++;
	}
}

void	ft_find_io(t_vars *vars, char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i - 1] != '>' && arg[i] == '>' && arg[i + 1] == ' ')
			vars->hv_outfile = 1;
		else if (arg[i - 1] != '>' && arg[i] == '>' && arg[i + 1] == '>'
			&& arg[i + 2] == ' ')
			vars->hv_append = 1;
		i++;
	}
}
