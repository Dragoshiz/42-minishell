/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:25:23 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/23 16:12:11 by dimbrea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define WHITESPACE " \t\r\n\v"
# define NUMPIPES 50

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

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
	char			**paths; // ENV list
	char			**args; // array of commands for the executor
	char			**env_sh;// cpy of env variable
	char			**cmds;// array of commandse
	char			**cmdbypipes;
	int				**pipefds;// pipe file descriptors
	char			*line;
	pid_t			pid;
	int				one_cmd;
	int				num_paths;
	int				num_args;
	int				num_cmds;
	int				num_pipes;
	int				index_pipe[NUMPIPES];
	int				num_env_sh;
	int				outfd;
	int				hv_infile_idx[2];
	int				hv_outfile;
	int				hv_append;
	int				hv_heredoc;
	t_linkedList	*env_sh_list;
}t_vars;

# include "execution/execution.h"
# include "parsing/parsing.h"
# include "builtins/builtins.h"

#endif