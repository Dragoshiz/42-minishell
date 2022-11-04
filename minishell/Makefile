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

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

AF = ar rcs

SRCS = \
execution/execution.utils/minish_utils.c\
execution/execution.utils/exec_utils.c\
execution/execution.utils/hrdc.c\
execution/execution.utils/pipes.c\
execution/execution.utils/searchers.c\
execution/execution.utils/exit.c\
execution/execution.utils/exec_file.c\
execution/execution.c\
execution/new_exec.c\
parsing/parsing.utils/env_list_util.c\
parsing/parsing.utils/line_util.c\
parsing/parsing.utils/pipeline_util.c\
parsing/parsing.utils/tokens_util.c\
parsing/parsing.utils/expansion_util.c\
parsing/parsing.c\
builtins/ft_env.c\
builtins/ft_export.c\
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