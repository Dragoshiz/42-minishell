/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfuhlenb <vfuhlenb@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:38:33 by vfuhlenb          #+#    #+#             */
/*   Updated: 2022/10/26 18:45:47 by vfuhlenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// return (1) if char s is present in string line, otherwise return (0)
int	peek(char *line, char s, int i)
{
	if ((size_t)i <= ft_strlen(line))
	{
		while (line[i])
		{
			if(line[i] == s)
				return (i);
			i++;
		}
	}
	return (-1);
}

void	separate_pipes(char *line, t_linkedList *pipeline)
{
	int		i;
	int		token;

	i = 0;
	token = 0;
	while(line[i])
	{
		if (line[i] == 32)
			while (line[i] == 32)
				i++;
		if (line[i] && line[i] == PIPE)
		{
			if (line[i] == 32)
			{
				while (line[i] == 32)
					i--;
				line[i + 1] = '\0';
				addTail(pipeline, ft_strdup(&line[token]));
				token = i + 2;
			}
			else
			{
				line[i] = '\0';
				addTail(pipeline, ft_strdup(&line[token]));
				token = i + 1;
			}
			if (line[i] == 32)
				while (line[i++] == 32);
		}
		i++;
	}
	addTail(pipeline, ft_strdup(&line[token]));
}

void	fill_args(t_vars *vars, t_linkedList *pipeline)
{
	int	i;

	pipeline->current = pipeline->head;
	vars->num_args = countLinkedList(pipeline);
	vars->args = malloc(sizeof(char *) * vars->num_args);
	i = 0;
	while(i < vars->num_args)
	{
		vars->args[i] = ft_strdup(pipeline->current->data);
		if (pipeline->current->next)
			pipeline->current = pipeline->current->next;
		i++;
	}
}

// process readline input and prepares args for the executor
void	parsing_pipeline(t_vars *vars)
{
	char			*line;
	t_linkedList	*pipeline;

	pipeline = NULL;
	line = ft_strdup(vars->line); // TODO protect
	pipeline = (t_linkedList *) malloc(sizeof(t_linkedList));
	initializeList(pipeline);
	separate_pipes(line, pipeline);
	fill_args(vars, pipeline);
	//displayLinkedList(pipeline);
	//clearLinkedList(pipeline);
	free(line);
}

// initial checks
void	parsing(t_vars *vars)
// TODO if || in line, then exit with error message "OR not implemented"
{
	// int	i;

	if (*vars->line == PIPE)
		exit(printf("minish: syntax error near unexpected token `|'")); // TODO create perror instance
	parsing_pipeline(vars);
	// i = 0;
	// while(i < vars->num_args)
	// {
	// 	printf("arg[%d]: %s $\n", i, vars->args[i]);
	// 	i++;
	// }
}



	// i = 0;
	// if (!ft_strncmp(line, "ENV", 3)) // DEBUG
	// {
	// 	while (vars->env_sh[i])
	// 		printf("%s\n", vars->env_sh[i++]);
	// }
	// else
	// 	printf("copy of line: %s\n", line);
	//displayLinkedList(vars->env_list);