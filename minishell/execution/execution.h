/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:14:09 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/29 18:19:21 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

//iov stand for Input Output Variables
typedef struct s_iovars
{
	char	*cmd;
	char	*delim;
	char	*filename;
	int		hrdc_pipe[2];
	int		size_delim;
	int		tmpin;
	int		tmpout;
	int		fdin;
	int		fdout;
}t_iovars;

//execution.c
void	ft_exec_cmd(t_vars *vars, t_iovars *iov);
void	ft_exec_utils(t_vars *vars, t_iovars *iov, int numcmds);
void	ft_get_path(t_vars *vars, char *env[]);
void	execution(t_vars *vars, t_iovars *iov);
void	ft_put_backsl(t_vars *vars);
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
int		ft_hrdoc(t_vars *vars, t_iovars *iov, char *arg, int i);
//searchers.c
int		ft_find_in(t_vars *vars);
int		ft_find_out(t_vars *vars, t_iovars *iov, char *arg);
void	ft_find_io(t_vars *vars, t_iovars *iov, char *arg);
char	*ft_find_delim(t_vars *vars, t_iovars *iov, char *arg, int i);
//exec_utils.c
void	ft_find_hrdc(t_vars *vars, t_iovars *iov);
int		ft_size_rl(char *line, t_iovars *iov);
char	*ft_custom_strjoin(char *s1, char *s2);
void	ft_errmsg(t_vars *vars, int i);
//hrdc.c
void	ft_set_redir(t_vars *vars);
void	ft_find_hrdc(t_vars *vars, t_iovars *iov);
void	ft_find_io(t_vars *vars, t_iovars *iov, char *arg);

#endif