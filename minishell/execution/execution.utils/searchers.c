/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:09:34 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/31 17:15:53 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_opn_fin(char *arg, int i)
{
	char	*filename;
	int		fd;

	filename = ft_get_filename(arg, i);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("");
	}
	free(filename);
	return (fd);
}

//check all of the cmd for infile
int	ft_find_in(t_vars *vars)
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
			if (vars->args[i][j] == '<')
			{
				if (vars->args[i][j - 1] != '<' && vars->args[i][j + 1] == ' ')
				{
					vars->hv_infile = 1;
					fd = ft_opn_fin(vars->args[i], j + 2);
				}
			}
			j++;
		}
		i++;
	}
	return (fd);
}

int	ft_opn_fout(t_iovars *iov, int g)
{
	int	fd;

	fd = 0;
	if (g == 1)
		fd = open(iov->filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (g == 2)
		fd = open(iov->filename, O_RDWR | O_CREAT | O_APPEND, 0777);
	free(iov->filename);
	return (fd);
}

//check if there is an > in the cmd and creates it
int	ft_find_out(t_vars *vars, t_iovars *iov, char *arg)
{
	int		i;
	int		fd;

	i = 0;
	fd = 0;
	while (arg[i++])
	{
		if (arg[i - 1] == ' ' && arg[i] == '>' && arg[i + 1] == ' ')
		{
			vars->hv_outfile = 1;
			iov->filename = ft_get_filename(arg, i + 2);
			fd = ft_opn_fout(iov, 1);
		}
		else if (arg[i - 1] == ' ' && arg[i] == '>' && arg[i + 1] == '>'
			&& arg[i + 2] == ' ')
		{
			vars->hv_append = 1;
			iov->filename = ft_get_filename(arg, i + 3);
			fd = ft_opn_fout(iov, 2);
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
	iov->size_delim = diff;
	iov->delim = malloc(sizeof(char) * diff + 1);
	j = 0;
	while (start < i)
		iov->delim[j++] = arg[start++];
	iov->delim[j] = '\0';
	return (iov->delim);
}
