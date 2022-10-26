/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:09:34 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/26 17:58:10 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//check all of the cmd for infile
//need to change for exit statuses;
int	ft_find_in(t_vars *vars, t_iovars *iov)
{
	int		fd;
	int		i;
	int		j;

	i = 0;
	while (vars->args[i])
	{
		j = 0;
		while (vars->args[i][j])
		{
			if (vars->args[i][j - 1] != '<' && vars->args[i] \
				[j] == '<' && vars->args[i][j + 1] == ' ')
			{
				vars->hv_infile = 1;
				iov->filename2 = ft_get_filename(vars->args[i], \
					j + 2);
				fd = open(iov->filename2, O_RDONLY);
				if (fd < 0)
					perror("");
				free(iov->filename2);
			}
			j++;
		}
		i++;
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

//function finds delimiter and returns the size of it
//free iov_delim
char	*ft_find_delim(t_vars *vars, t_iovars *iov, char *arg, int i)
{
	int		start;
	int		diff;
	int		j;
	char	dlm;

	(void)vars;
	start = i;
	dlm = ' ';
	if (arg[i] == '\"')
		dlm = '\"';
	while (arg[i] != dlm && arg[i])
		i++;
	diff = i - start;
	iov->delim = malloc(sizeof(char) * diff + 1);
	j = 0;
	while (start < i)
		iov->delim[j++] = arg[start++];
	iov->delim[j] = '\0';
	return (iov->delim);
}

void	ft_find_hrdc(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->args[0][i])
	{
		if (vars->args[0][i - 1] != '<' && vars->args[0][i] == '<' && \
		vars->args[0][i + 1] == '<' && vars->args[0][i + 2] == ' ')
		{
			vars->hv_heredoc = 1;
		}
		i++;
	}
}

void	ft_find_io(t_vars *vars, t_iovars *iov, char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i - 1] != '>' && arg[i] == '>' && arg[i + 1] == ' ')
			ft_find_out(vars, iov, arg);
		else if (arg[i - 1] != '>' && arg[i] == '>' && arg[i + 1] == '>' \
			&& arg[i + 2] == ' ')
			ft_find_out(vars, iov, arg);
		else if (arg[i - 1] != '<' && arg[i] == '<' && arg[i + 1] == '<' \
			&& arg[i + 2] == ' ')
			iov->hrdc_fd = ft_hrdoc(vars, iov, arg, i + 3);
		i++;
	}
}
