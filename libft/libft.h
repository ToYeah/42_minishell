/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 23:39:20 by nfukada           #+#    #+#             */
/*   Updated: 2020/06/24 18:01:07 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

char			*ft_strnstr(const char *haystack, const char *needle,
							size_t len);
int				ft_isdigit(int c);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strchr(const char *s, int c);
void			ft_bzero(void *s, size_t n);
int				ft_isascii(int c);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
int				ft_isprint(int c);
int				ft_toupper(int c);
char			*ft_strrchr(const char *s, int c);
int				ft_isalpha(int c);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memset(void *b, int c, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
int				ft_atoi(const char *str);
int				ft_isalnum(int c);
int				ft_tolower(int c);

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_itoa(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));
#endif
