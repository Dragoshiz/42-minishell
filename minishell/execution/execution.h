/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:14:09 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/25 17:15:55 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

void	execution(t_vars *vars);

// minish_utils.c

void	ft_free_doublepoint(char **to_free);
void	ft_cpy_env(t_vars *vars, char **env);
char	*ft_find_arg_path(t_vars *vars, char *arg);
void	ft_count_args(t_vars *vars);


// pipes.c
void	ft_create_pipes(t_vars *vars);
void	ft_close_pipes(t_vars *vars);
//new approach
int		ft_find_in(t_vars *vars);
char	*ft_get_filename(char *arg, int i);
void	ft_get_cmd(t_vars *vars, char *arg);
void	ft_exec_cmd(t_vars *vars);

//searchers.c
int		ft_find_in(t_vars *vars);
int		ft_find_out(t_vars *vars, char *arg);
void	ft_dup2nclose(int fd, int std);
void	ft_find_io(t_vars *vars, char *arg);


#endif