/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 22:20:01 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/24 10:48:38 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define MY_LONG_MAX 9223372036854775807
# define GNL_BUFFER_SIZE 1024

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			ft_bzero(void *s, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_putnbr_ui_fd(unsigned int n, int fd);
void			ft_putabs_fd(int n, int fd);
void			ft_puthex_fd(unsigned int n, t_bool format, int fd);
void			ft_puthex_ul_fd(unsigned long n, t_bool format, int fd);
void			ft_putstr_limit(char *str, int limit);
void			ft_safe_free_char(char **target);
void			ft_safe_free_split(char ***target);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strdup(const char *s1);
char			*ft_strnstr(const char *h, const char *needle, size_t len);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_find_new_line(const char *s, size_t len);
char			*ft_through_digit(char *str);
char			*ft_through_space(char *str);
int				ft_get_upper(int num1, int num2);
int				ft_get_lower(int num1, int num2);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strrncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_lstsize(t_list *lst);
int				ft_nbrdig(int n);
int				ft_nbrdig_hex(unsigned int n);
int				ft_nbrdig_hex_ul(unsigned long n);
int				ft_nbrdig_ui(unsigned int n);
int				ft_get_next_line(int fd, char **line);
int				ft_strcmp(char *s1, char *s2);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
t_list			*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *));
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
t_bool			ft_atoi_limit(const char *str, int *return_value);
#endif
