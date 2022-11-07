/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:38:33 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/11/07 23:11:24 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// displays error message. 1:near unexpected token 2:unclosed quote
static void	syntax_errors(t_parsing *parsing)
{
	if (parsing->vars->syntax_error == 1)
		ft_putstr_fd("minish: syntax error near unexpected token '|' \n", 1);
	if (parsing->vars->syntax_error == 2)
		ft_putstr_fd("minish: syntax error unclosed quote \n", 1);
	if (parsing->vars->syntax_error == 3)
		ft_putstr_fd("minish: syntax error near unexpected token `<<' \n", 1);
	if (parsing->vars->syntax_error == 4)
		ft_putstr_fd("minish: syntax error near unexpected token `>>' \n", 1);
	if (parsing->vars->syntax_error == 5)
		ft_putstr_fd("minish: syntax error near unexpected token `>' \n", 1);
	if (parsing->vars->syntax_error == 6)
		ft_putstr_fd("minish: syntax error near unexpected token `<' \n", 1);
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
	parsing->index = 0;
	parsing->m1 = -1;
	parsing->m2 = -1;
	parsing->d_quote = DQUOTE;
	parsing->s_quote = SQUOTE;
}

// Main function for Parsing & initial checks
void	parsing(t_vars *vars, t_parsing *parsing)
{
	initialize_parsing(parsing, vars);
	initialize_pipeline(parsing);
	split_pipeline(parsing);
	initialize_token_list(parsing);
	split_tokens(parsing);
	expand_tokens(parsing);
	token_trim_white(parsing);
	token_trim_quotes(parsing);
	fill_args(parsing);
	debug_print_args(parsing->vars->args, parsing->vars->num_args);
	display_token_list(parsing->token_list);
	edge_cases(parsing);
	syntax_errors(parsing);
}

void	parsing_cleanup(t_parsing *parsing)
{
	delete_list(parsing->pipeline);
	free(parsing->pipeline);
	delete_token_list(parsing->token_list);
	free(parsing->token_list);
	ft_free_doublepoint(parsing->vars->args);
	delete_list(parsing->vars->env_list);
	free(parsing->vars->env_list);
	ft_free_doublepoint(parsing->vars->env_sh);
}
