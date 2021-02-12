NAME=libft.a
SRCS=\
ft_atoi.c\
ft_bzero.c\
ft_calloc.c\
ft_find_new_line.c\
ft_get_lower.c\
ft_get_next_line.c\
ft_get_upper.c\
ft_isalnum.c\
ft_isalpha.c\
ft_isascii.c\
ft_isdigit.c\
ft_isprint.c\
ft_itoa.c\
ft_lstadd_back.c\
ft_lstadd_front.c\
ft_lstclear.c\
ft_lstdelone.c\
ft_lstiter.c\
ft_lstlast.c\
ft_lstmap.c\
ft_lstnew.c\
ft_lstsize.c\
ft_memccpy.c\
ft_memchr.c\
ft_memcmp.c\
ft_memcpy.c\
ft_memmove.c\
ft_memset.c\
ft_nbrdig.c\
ft_putabs_fd.c\
ft_putchar_fd.c\
ft_putendl_fd.c\
ft_puthex_fd.c\
ft_putnbr_fd.c\
ft_putstr_fd.c\
ft_putstr_limit.c\
ft_safe_free.c\
ft_split.c\
ft_strchr.c\
ft_strdup.c\
ft_strjoin.c\
ft_strlcat.c\
ft_strlcpy.c\
ft_strlen.c\
ft_strmapi.c\
ft_strncmp.c\
ft_strnstr.c\
ft_strrchr.c\
ft_strtrim.c\
ft_substr.c\
ft_tolower.c\
ft_toupper.c\
ft_through.c

CC=gcc
CCFLAGS=-Wall -Wextra -Werror
AR=ar
ARFLAGS=crs
OBJS=$(SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONEY	: all clean fclean re
