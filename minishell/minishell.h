/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:25:23 by dimbrea           #+#    #+#             */
/*   Updated: 2022/11/14 15:13:05 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define WHITESPACE " \t\r\n\v"
# define HEREDOC "<<"
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
// # include "/Users/vfuhlenb/goinfre/.brew/Cellar/readline/8.2.1/include/readline/\
// readline.h"
// # include "/Users/vfuhlenb/goinfre/.brew/Cellar/readline/8.2.1/include/readline/\
history.h"
# include "/Users/dimbrea/goinfre/.brew/Cellar/readline/8.2.1/include/readline/readline.h"
# include "/Users/dimbrea/goinfre/.brew/Cellar/readline/8.2.1/include/readline/history.h"
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct s_parsing	t_parsing;
typedef struct s_iovars		t_iovars;
typedef struct s_vars		t_vars;

int	g_exit;

typedef struct s_token {
	char			*data;
	int				type;
	int				pipe_nbr;
	struct s_token	*next;
}	t_token;

typedef struct s_token_list {
	t_token	*head;
	t_token	*tail;
	t_token	*current;
}	t_token_list;

typedef struct s_node {
	char				*data;
	int					pipe_nbr;
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
	char			*line;
	pid_t			pid;
	int				num_args;
	int				num_env_sh;
	int				hv_infile;
	int				hv_outfile;
	int				hv_append;
	int				syntax_error;
	char			s_err_c;
	int				exit_status;
	int				call_minish;
	t_linked_list	*env_list; // working env list
	t_linked_list	*exp_lst;
	t_parsing		*parse;
}	t_vars;

//iov stand for Input Output Variables
typedef struct s_iovars
{
	char	*cmd;
	char	*delim;
	char	*filename;
	int		**pipefds;
	int		hrdc_pipe[2];
	int		size_delim;
	int		tmpin;
	int		tmpout;
	int		fdin;
	int		fdout;
	int		hv_heredoc;
	int		hv_builtin;
	t_vars	*vars;
}t_iovars;

typedef struct s_parsing {
	t_vars			*vars;
	t_linked_list	*pipeline;
	t_token_list	*token_list;
	int				token_nbr;
	int				line_len;
	char			*p_start;
	char			*p_end;
	char			*line_end;
	char			*q_open;
	char			quote;
	int				num_cmds;
	int				len;
	int				status;
	int				check;
	int				var_name_len;
	int				var_value_len;
	char			*var_name;
	char			*var_value;
	int				p_len;
	int				ix;
	int				m1;
	int				m2;
	char			d_quote;
	char			s_quote;
}t_parsing;

// BUILTINS
void	env_list_create(t_vars *vars);
void	ft_env(t_vars *vars);
void	ft_echo(t_token *current, t_iovars *iov, int pipe_num);

// EXECUTION

//execution.c
void	ft_exec_cmd(t_vars *vars, t_iovars *iov);
void	ft_exec_utils(t_vars *vars, t_iovars *iov, int numcmds);
void	ft_get_path(t_vars *vars, char *env[]);
void	ft_start_exec(t_vars *vars, t_iovars *iov, t_parsing *parse);
void	ft_put_backsl(t_vars *vars);
void	ft_execution(t_vars *vars, t_iovars *iov, t_parsing *parse);
// minish_utils.c
void	ft_free_doublepoint(char **to_free);
void	ft_free_doublepointi(int **to_free);
char	*ft_find_arg_path(t_vars *vars, char *arg);
void	ft_count_args(t_vars *vars);
void	ft_dup2nclose(int fd, int std);
// pipes.c
char	*ft_get_filename(char *arg, int i);
// void	ft_get_cmd(t_vars *vars, char *arg);
int		ft_hrdoc(t_vars *vars, t_iovars *iov, char *arg, int i);
//searchers.c
int		ft_find_in(t_vars *vars);
int		ft_find_out(t_vars *vars, t_iovars *iov, char *arg);
void	ft_find_io(t_vars *vars, t_iovars *iov, char *arg);
char	*ft_find_delim(t_vars *vars, t_iovars *iov, char *arg, int i);
//exec_utils.c
void	ft_find_hrdc(t_vars *vars, t_iovars *iov);
int		t_size_rl(char *line, int size_delim);
char	*ft_custom_strjoin(char *s1, char *s2);
void	ft_errmsg(t_vars *vars, int i);
//hrdc.c
void	ft_set_redir(t_vars *vars);
void	ft_find_hrdc(t_vars *vars, t_iovars *iov);
void	ft_find_io(t_vars *vars, t_iovars *iov, char *arg);

void	ft_init_exc(t_iovars *iov);
void	ft_builtins(t_token *current, t_iovars *iov, int i, int pipe_num);
void	ft_built_env(t_vars *vars);
void	ft_built_pwd(void);
void	ft_executable(t_vars *vars, t_iovars *iov, t_parsing *parsing);

//export.c
void	ft_get_export(t_vars *vars);
void	ft_export(t_vars *vars);

//export1.c
int		ft_chk_chars(char *data);
int		ft_hv_equal(char *curr_data);
int		is_ordered(t_linked_list *exp_lst);
int		ft_update_data(t_vars *vars, char	*data);
int		ft_update_exp(t_linked_list *exp_lst, char *data);

//export2.c
void	ft_printnsortexp(t_linked_list *exp_lst);
void	ft_add2env(t_vars *vars, char *data);
int		ft_chk_cur_env(t_linked_list *exp_lst, char *data);
int		ft_is_valid(t_token *curr, char *curr_data);
void	ft_get_var(t_vars *vars);
//unset.c
void	ft_unset(t_vars *vars);

//ft_cd.c
void	ft_cd(t_vars *vars);

// other
int		is_whitespace(char *line);
void	ft_cpy_env(t_vars *vars, char **env);
void	ft_init_vars(t_vars *vars);
int		check_builtins(t_token *current, t_iovars *iov, int pipe_num);
int		ft_exec_file(t_parsing *parsing);

// PARSING

void	parsing(t_parsing *parsing, t_vars *vars);
void	parsing_cleanup(t_parsing *parsing);

// PARSING DEBUG

void	debug_print_args(char *args[], int num_args);
void	display_token_list(t_token_list *list);

// PARSING UTILS

void	seek_word_r(t_parsing *parsing, char *str);
void	seek_red_r(t_parsing *parsing, char *str);
void	seek_whs_r(t_parsing *parsing, char *str);
int		peek_dollar_quote(t_parsing *p, char *str);
int		is_redc(char c);
int		is_variable_char(char c);
int		is_variable_start_char(char c);
int		is_quote_char(char c);
int		is_whs_c(char c);
int		is_word_c(char c);

// EDGE CASES UTILS

void	s_err_pipe(t_parsing *p);
void	s_err_redir(t_parsing *p);
void	add_syntax_error(t_parsing *p, char *c, int i);

// EXPANSION UTILITIES

char	*insert_exit_status(t_parsing *parsing, void *data);
char	*insert_expanded_string(t_parsing *parsing, void *data);
void	check_expansion_quotes(char *quote, int *status, char c);
void	expand_variables(t_parsing *parsing);

// TOKEN UTILITIES

void	remove_quote_pairs(char *p, int *ref, char *str);
void	token_trim_white(t_parsing *parsing);
void	token_trim_quotes(t_parsing *parsing);
int		token_value_red(t_parsing *parsing, char *str, int i);
void	redir_error_check(t_parsing *p, char *str, int i);
void	add_token(t_parsing *parsing, void *data, int type, t_node *current);
void	initialize_token_list(t_parsing *parsing);
void	check_token_quotes(t_parsing *parsing, char *str, int i);
void	delete_token_list(t_token_list *list);
void	split_tokens(t_parsing *parsing);

// PIPELINE UTILITIES

void	split_pipeline(t_parsing *parsing);
void	initialize_pipeline(t_parsing *parsing);
void	fill_args(t_parsing *parsing);
void	check_quotes(t_parsing *parsing, int i);
void	pipe_trim_white(t_parsing *parsing);
void	add_tail_pipe(t_parsing *parsing, void *data);

// LINE UTIL

void	initialize_line(t_parsing *parsing);
char	*dup_range(char *p_start, char *p_end);

// LIST UTIL

void	add_head(t_linked_list *list, void *data);
void	add_tail(t_linked_list *list, void *data);
void	display_linked_list(t_linked_list *list);
void	initialize_list(t_linked_list *list);
int		count_linked_list(t_linked_list *list);
int		count_token_list(t_token_list *list);
void	delete_list(t_linked_list *list);

//NEW EXEC
char	*ft_exe(t_parsing *parse, t_iovars *iov);
void	ft_execv2(t_parsing *parse, t_iovars *iov);
int		ft_get_out(t_iovars *iov, t_parsing *parse, int pipe_nbr);
int		ft_get_inp(t_iovars *iov, t_parsing *parse, int pipe_nbr);
void	ft_get_hrdoc(t_token *current, t_iovars *iov);
int		ft_size_rl(char *line, int size_delim);
char	*ft_custom_strjoin(char *s1, char *s2);
void	ft_create_pipes(t_parsing *parse, t_iovars *iov);
void	ft_close_pipes(t_parsing *parse, t_iovars *iov);
void	ft_ctrl(int sig);
void	ft_ctrl_hrdc(int sig);

#endif