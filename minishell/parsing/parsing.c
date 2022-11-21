/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:38:33 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/21 16:15:36 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// displays error message. 1:near unexpected token 2:unclosed quote
static void	syntax_errors(t_parsing *parsing)
{
	if (parsing->vars->syntax_error == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		write(2, &parsing->vars->s_err_c, 1);
		ft_putstr_fd("' \n", 2);
		g_exit = 258;
	}
	else if (parsing->vars->syntax_error == 2)
	{
		ft_putstr_fd("minishell: syntax error unclosed quote \n", 2);
		g_exit = 259;
	}
}

// parsing edge cases
static void	edge_cases(t_parsing *parsing)
{
	if (s_err_token(parsing))
		return ;
	s_err_pipe(parsing);
	s_err_redir(parsing);
}

// Initialize parsing struct
static void	initialize_parsing(t_parsing *parsing, t_vars *vars)
{
	parsing->vars = vars;
	parsing->line_len = ft_strlen(vars->line);
	parsing->line_end = &vars->line[parsing->line_len];
	parsing->p_start = vars->line;
	parsing->p_end = parsing->line_end;
	parsing->q_open = NULL;
	parsing->num_cmds = 0;
	parsing->quote = '\0';
	parsing->len = 0;
	parsing->status = 0;
	parsing->check = 0;
	parsing->var_name_len = 0;
	parsing->var_value_len = 0;
	parsing->var_name = NULL;
	parsing->var_value = NULL;
	parsing->p_len = 0;
	parsing->ix = 0;
	parsing->m1 = -1;
	parsing->m2 = -1;
	parsing->d_quote = DQUOTE;
	parsing->s_quote = SQUOTE;
	parsing->token_nbr = 0;
	parsing->pipelen = 0;
}

// Main function for Parsing & initial checks
void	parsing(t_parsing *parsing, t_vars *vars)
{	
	initialize_parsing(parsing, vars);
	initialize_pipeline(parsing);
	split_pipeline(parsing);
	expand_variables(parsing);
	pipe_trim_white(parsing);
	initialize_token_list(parsing);
	split_tokens(parsing);
	token_trim_white(parsing);
	token_trim_quotes(parsing);
	edge_cases(parsing);
	syntax_errors(parsing);
}

// cleanup parsing
void	parsing_cleanup(t_parsing *parsing)
{
	delete_list(parsing->pipeline);
	free(parsing->pipeline);
	delete_token_list(parsing->token_list);
	free(parsing->token_list);
}
