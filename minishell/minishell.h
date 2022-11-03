/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:25:23 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/03 18:49:54 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define WHITESPACE " \t\r\n\v"
# define NUMPIPES 50
# define MAX_PATH_LEN 256
# define PIPE '|'
# define SQUOTE 39
# define DQUOTE 34
# define EMPTY_SPACE 32
# define DOLLAR 36

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
// # include <readline/readline.h>
// # include <readline/history.h>
# include "/Users/vfuhlenb/goinfre/.brew/Cellar/readline/8.2.1/include/readline/readline.h"
# include "/Users/vfuhlenb/goinfre/.brew/Cellar/readline/8.2.1/include/readline/history.h"
# include <sys/wait.h>
# include <signal.h>
# include "libft/libft.h"


typedef struct s_token {
	char			*data;
	void			*type;
	int				pipe_nbr;
	struct s_token	*next;
}	t_token;

typedef struct s_token_list {
	t_token	*head;
	t_token	*tail;
	t_token	*current;
}	t_token_list;

typedef struct s_node {
	void				*data;
	struct s_node		*next;
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
	int				call_minish;
	t_linked_list	*env_list; // working env list
}	t_vars;

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

typedef struct s_parsing {
	t_vars			*vars;
	t_linked_list	*pipeline;
	t_token_list	*token_list;
	int				line_len;
	char			*p_start;
	char			*p_end;
	char			*line_end;
	char			*q_open;
	char			quote;
	int				num_pipes;
}	t_parsing;

// BUILTINS
void	env_list_create(t_vars *vars);
void	ft_env(t_vars *vars);

// EXECUTION

//execution.c
void	ft_exec_cmd(t_vars *vars, t_iovars *iov);
void	ft_exec_utils(t_vars *vars, t_iovars *iov, int numcmds);
void	ft_get_path(t_vars *vars, char *env[]);
void	ft_start_exec(t_vars *vars, t_iovars *iov);
void	ft_put_backsl(t_vars *vars);
void	ft_execution(t_vars *vars, t_iovars *iov);
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

void	ft_init_exc(t_iovars *iov);
void	ft_builtins(t_vars *vars, t_iovars *iov, int i);
void	ft_built_env(t_vars *vars);
void	ft_built_pwd(void);
void	ft_executable(t_vars *vars, t_iovars *iov);

// other
int		is_whitespace(char *line);
void	ft_cpy_env(t_vars *vars, char **env);
void	ft_init_vars(t_vars *vars);
int		check_builtins(t_vars *vars, t_iovars *iov);
void	ft_builtins(t_vars *vars, t_iovars *iov, int i);
void	ft_exec_file(t_parsing *parsing);


// PARSING

void	parsing(t_vars *vars);

// EXPANSION UTILITIES

char	*insert_expanded_string(t_linked_list *env_list, void *data, int i);
void	check_expansion_quotes(char *quote, int *status, char c);
void	expand_tokens(t_parsing *parsing);
int		is_variable_char(char c);

// TOKEN UTILITIES

void	add_token(t_parsing *parsing, void *data);
int		is_whitespace_char(char c);
void	initialize_token_list(t_parsing *parsing);
void	check_token_quotes(t_parsing *parsing, char *str, int i);
void	display_token_list(t_token_list *list); // DEBUG
void	delete_token_list(t_token_list *list);
void	split_tokens(t_parsing *parsing);

// PIPELINE UTILITIES

void	initialize_pipeline(t_parsing *parsing);
void	fill_args(t_parsing *parsing);
void	check_quotes(t_parsing *parsing, int i);

// LINE UTIL

void	initialize_line(t_parsing *parsing);
char	*dup_range(char *p_start, char *p_end);
void	check_quotes(t_parsing *parsing, int i);

// LIST UTIL

void	add_head(t_linked_list *list, void *data);
void	add_tail(t_linked_list *list, void *data);
void	display_linked_list(t_linked_list *list);
void	initialize_list(t_linked_list *list);
int		count_linked_list(t_linked_list *list);
void	delete_list(t_linked_list *list); // TODO also delete sub-list

#endif