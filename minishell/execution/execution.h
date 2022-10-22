/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:14:09 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/22 14:28:09 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

void	execution(t_vars *vars);

// minish_utils.c

void	ft_free_doublepoint(char **to_free);
void	ft_cpy_env(t_vars *vars, char **env);
char	*ft_find_arg_path(t_vars *vars, char *arg);
void	ft_exec(t_vars *vars);
int		ft_double(t_vars *vars, int i);
int		ft_check_pipes(t_vars *vars);
void	ft_assign_symbs(t_vars *vars, char arg, int i);//try
void	ft_iter(t_vars *vars);//try
void	ft_exec1(t_vars *vars);

// pipes.c

void	ft_create_pipes(t_vars *vars);
void	ft_close_pipes(t_vars *vars);
void	ft_pipeio(t_vars *vars, char **cmd, int cmd_count);

#endif