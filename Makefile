# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/10 18:36:52 by nfukada           #+#    #+#              #
#    Updated: 2021/02/25 19:28:05 by totaisei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
NAME_DEBUG	:= minishell_debug

ifdef DEBUG
NAME		:= $(NAME_DEBUG)
endif

SRC_DIR		:= srcs
INC_DIR		:= includes
LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a
INC			:= -I$(INC_DIR) -I$(LIBFT_DIR)

SRCS		:= srcs/lexer/lexer_general_state.c srcs/lexer/lexer.c srcs/lexer/lexer_quote_state.c srcs/utils/token_utils.c srcs/utils/token.c srcs/utils/env.c srcs/utils/error.c srcs/utils/env_utils.c srcs/parser/parser_utils.c srcs/parser/redirect.c srcs/parser/print_node_label.c srcs/parser/parser.c srcs/parser/node.c srcs/parser/print_node.c srcs/expander/expander.c srcs/expander/expand_tokens.c srcs/expander/expand_var.c srcs/main.c srcs/exec/exec.c srcs/exec/command.c srcs/exec/build_path.c srcs/exec/exec_pipe.c srcs/exec/build_path_utils.c srcs/builtin/buildin.c
OBJS		:= $(SRCS:%.c=%.o)
LIBS		:= -lft -L$(LIBFT_DIR)

DEBUG		:= FALSE

CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra $(INC) -g -fsanitize=address -D DEBUG=$(DEBUG)

.PHONY: all clean fclean re bonus debug norm srcs

all		: $(NAME)

$(NAME)	: $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

bonus	: all

clean	:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean	: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME) $(NAME_DEBUG)

re		: fclean all

debug	: clean
	$(MAKE) DEBUG=TRUE
	$(MAKE) clean

norm	:
ifeq ($(shell which norminette),)
	~/.norminette/norminette.rb $(SRCS) $(INC_DIR)
else
	norminette $(SRCS) $(INC_DIR)
endif

srcs	:
	sed -i .bak -e "s#^\(SRCS.*= \).*#\1$$(find srcs -name '*.c' -type f | tr '\n' ' ')#" ./Makefile
