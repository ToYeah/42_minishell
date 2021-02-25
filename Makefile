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

SRC_DIR		:= srcs
INC_DIR		:= includes
LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a
INC			:= -I$(INC_DIR) -I$(LIBFT_DIR)

SRCS		:= srcs/lexer/lexer_quote_state.c srcs/lexer/lexer.c srcs/lexer/lexer_general_state.c srcs/expander/expander.c srcs/expander/expand_var.c srcs/expander/expand_tokens.c srcs/main.c srcs/builtin/buildin.c srcs/utils/env.c srcs/utils/error.c srcs/utils/token.c srcs/utils/token_utils.c srcs/utils/env_utils.c srcs/exec/build_path.c srcs/exec/build_path_utils.c srcs/exec/exec_command.c srcs/exec/command.c srcs/parser/print_node_label.c srcs/parser/node.c srcs/parser/print_node.c srcs/parser/redirect.c srcs/parser/parser_utils.c srcs/parser/parser.c 
OBJS		:= $(SRCS:%.c=%.o)
LIBS		:= -lft -L$(LIBFT_DIR)

CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra $(INC) -g -fsanitize=address

.PHONY: all clean fclean re bonus norm srcs

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
	rm -f $(NAME)

re		: fclean all

norm	:
ifeq ($(shell which norminette),)
		~/.norminette/norminette.rb $(SRCS) $(INC_DIR)
else
		norminette $(SRCS) $(INC_DIR)
endif

srcs	:
	sed -i .bak -e "s#^\(SRCS.*= \).*#\1$$(find srcs -name '*.c' -type f | tr '\n' ' ')#" ./Makefile
