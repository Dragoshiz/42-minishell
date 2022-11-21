  # **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dimbrea <dimbrea@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 16:27:48 by dimbrea           #+#    #+#              #
#    Updated: 2022/10/14 10:47:46 by dimbrea          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

AF = ar rcs

SRCS = \
execution/redirections/file_io.c\
execution/redirections/heredoc.c\
execution/redirections/redirect.c\
execution/execution.utils/minish_utils.c\
execution/execution.utils/minish_utils2.c\
execution/execution.utils/exec_utils.c\
execution/execution.utils/exit.c\
execution/execution.c\
execution/execve.c\
execution/execve2.c\
execution/exec.c\
parsing/parsing.utils/parsing_util.c\
parsing/parsing.utils/parsing_util2.c\
parsing/parsing.utils/env_list_util.c\
parsing/parsing.utils/env_list_util2.c\
parsing/parsing.utils/line_util.c\
parsing/parsing.utils/pipeline_util.c\
parsing/parsing.utils/pipeline_util2.c\
parsing/parsing.utils/tokens_util.c\
parsing/parsing.utils/tokens_util2.c\
parsing/parsing.utils/tokens_util3.c\
parsing/parsing.utils/tokens_util4.c\
parsing/parsing.utils/expansion_util.c\
parsing/parsing.utils/expansion_util2.c\
parsing/parsing.utils/expansion_util3.c\
parsing/parsing.utils/expansion_util4.c\
parsing/parsing.utils/edge_cases.c\
parsing/parsing.c\
builtins/export/ft_export.c\
builtins/export/ft_export1.c\
builtins/export/ft_export2.c\
builtins/ft_unset.c\
builtins/ft_unset2.c\
builtins/ft_env.c\
builtins/ft_echo.c\
builtins/ft_cd.c\
builtins/ft_cd2.c\
main.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		make -C libft
		$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -I ~/goinfre/.brew/opt/readline/include/ -L ~/goinfre/.brew/opt/readline/lib/ -lreadline -o $(NAME)

clean:
	$(RM) $(OBJS)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

norminette:
	norminette $(SRCS)