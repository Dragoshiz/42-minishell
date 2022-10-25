/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:14:09 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/25 18:08:46 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_iovars
{
	char	*cmd;
	char	*filename;
	char	*filename2;
	int		tmpin;
	int		tmpout;
	int		fdin;
	int		fdout;
	int		i;
	int		j;
}t_iovars;

void	execution(t_vars *vars, t_iovars *iov);
// minish_utils.c
void	ft_free_doublepoint(char **to_free);
char	*ft_find_arg_path(t_vars *vars, char *arg);
void	ft_count_args(t_vars *vars);
void	ft_dup2nclose(int fd, int std);
// pipes.c
void	ft_create_pipes(t_vars *vars);
void	ft_close_pipes(t_vars *vars);
char	*ft_get_filename(char *arg, int i);
void	ft_get_cmd(t_vars *vars, char *arg);
void	ft_exec_cmd(t_vars *vars, t_iovars *iov);
//searchers.c
int		ft_find_in(t_vars *vars, t_iovars *iov);
int		ft_find_out(t_vars *vars, t_iovars *iov, char *arg);
void	ft_find_io(t_vars *vars, char *arg);

#endif