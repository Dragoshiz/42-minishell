/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:25:23 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/18 16:38:37 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WHITESPACE " \t\r\n\v"

typedef struct s_node {
	void	*data;
	struct	s_node *next;
}	t_node;

typedef struct s_linkedList {
	t_node	*head;
	t_node	*tail;
	t_node	*current;
}	t_linkedList;

typedef struct s_vars{
	char	**paths; // ENV list
	char	**args; // array of commands for the executor
	char	**env_sh;
	char	*line;
	int		num_paths;
	int		num_args;
	int		num_cmds;
	int		num_pipes;
	int		num_env_sh;
	int		hv_infile;
	int		hv_outfile;
	int		hv_redirect;
	int		hv_heredoc;
  t_linkedList	env_sh_list; // working ENV (minishell)
}t_vars;

/*
BUILTINS
*/
// export.c

/*
PARSING
*/
// env_sh_list.c
void	initialize_env_sh_list(t_vars *vars, char *env[]);
// parseline.c
void	get_tokens(t_vars *vars);

/*
UTILS
*/
// list_sh_utils.c
void	addHead(t_linkedList *list, void *data);
void	addTail(t_linkedList *list, void *data);
void	displayLinkedList(t_linkedList *list);
void	initializeList(t_linkedList *list);
// minish_utils.c
void	ft_free_doublepoint(char **to_free);
void	ft_cpy_env(t_vars *vars, char **env);
char	*ft_find_arg_path(t_vars *vars, char *arg);
void	ft_exec(t_vars *vars);
int		ft_double(t_vars *vars, char arg, int i);
int		ft_check_pipes(t_vars *vars);
void	ft_assign_symbs(t_vars *vars, char arg, int i);//try
void	ft_iter(t_vars *vars);//try

#endif