/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:39:00 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/02 19:51:22 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define PIPE '|'
# define SQUOTE 39
# define DQUOTE 34
# define EMPTY_SPACE 32

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
}	t_parsing;

void	parsing(t_vars *vars);

// TOKEN UTILITIES

void	add_token(t_token_list *list, void *data);
int		is_whitespace_char(char c);
char	*dup_range_token(char *p_start, char *p_end);
void	initialize_token_list(t_parsing *parsing);
void	check_token_quotes(t_parsing *parsing, char *str, int i);
void	display_token_list(t_token_list *list); // DEBUG

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