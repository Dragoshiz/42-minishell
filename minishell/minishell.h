/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:25:23 by dimbrea           #+#    #+#             */
/*   Updated: 2022/10/31 10:39:57 by dimbrea          ###   ########.fr       */
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
# include <sys/wait.h>
# include "libft/libft.h"

// typedef struct s_node {
// 	void			*data;
// 	struct s_node	*next;
// }	t_node;

// typedef struct s_linkedList {
// 	t_node	*head;
// 	t_node	*tail;
// 	t_node	*current;
// }	t_linked_ist;

typedef struct s_node {
	void					*data;
	void					*type;
	struct s_node			*next;
	struct s_linked_list	*sublist;
}	t_node;

typedef struct s_linked_list {
	t_node	*head;
	t_node	*tail;
	t_node	*current;
}	t_linked_list;

typedef struct s_vars{
	char			**paths; // ENV list
	char			**args; // array of commands for the executor
	char			**env_sh;// cpy of env variable on startup
	char			**cmds;// array of commandse
	int				**pipefds;// pipe file descriptors
	char			*line;
	pid_t			pid;
	int				num_args;
	int				num_env_sh;
	int				hv_infile;
	int				hv_outfile;
	int				hv_append;
	int				hv_heredoc;
	int				syntax_error;
	int				exit_status;
	t_linked_list	*env_list; // working env list
}t_vars;

# include "execution/execution.h"
# include "parsing/parsing.h"
# include "builtins/builtins.h"

#endif