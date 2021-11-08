/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/23 17:18:01 by kde-wint       #+#    #+#                */
/*   Updated: 2020/03/04 13:11:44 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
size_t				ft_countchr(const char *s, const int c);
int					ft_fprintf(FILE *fd, char *str, ...);
char				*ft_findnextline(
						const char *str, const int linebreaks_to_skip);
char				*ft_findnextword(const char *str, const int spaces_to_skip);
int					ft_get_next_line(const int fd, char **line);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_iseven(long long n);
int					ft_isprint(int c);
char				*ft_itoa(int n);
char				*ft_lastchar(char *str);
int					ft_lastchari(char *str);
char				*ft_lltoa(long long n);
char				*ft_lltoa_base(const long long const_l,
						const unsigned int base);
int					ft_lookup(char c, char *arr, size_t size);
t_list				*ft_lstalloc(size_t content_size);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_memdel(void **ap);
long long			ft_powllong(const long long base, const long long exponent);
int					ft_printf(char *str, ...);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const *s);
void				ft_putstrn(char const *s, size_t n);
void				ft_putstrn_fd(char const *s, size_t n, int fd);
void				ft_putstr_fd(char const *s, int fd);
double				ft_sqrt(double x);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
void				ft_strdel(char **as);
void				ft_skipalnum(char **str);
void				ft_skipchars(char **str);
void				ft_skipdigits(char **str);
char				*ft_strdup(const char *s1);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strcap(char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strndup(const char *s1, size_t len);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(
						const char *haystack,
						const char *needle,
						size_t len);
int					ft_sprintf(char *dst, char *str, ...);
char				*ft_strrchr(const char *s, int c);
void				ft_strreplace(char **s, char *new);
char				*ft_strrev(const char *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtolower(const char *s);
char				*ft_strtoupper(const char *s);
char				*ft_strtrim(const char *s);
char				*replace_substring(
						const char *original, const char *start_replacing,
						const int length_to_replace, const char *replacement);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_ulltoa(unsigned long long n);
char				*ft_ulltoa_base(const unsigned long long const_l,
						const unsigned int base);

#endif
