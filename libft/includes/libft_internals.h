/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_internals.h                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/13 19:02:00 by kde-wint       #+#    #+#                */
/*   Updated: 2019/12/09 17:27:40 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_INTERNALS_H
# define LIBFT_INTERNALS_H

# define FLAG_MINUS (1 << 0)
# define FLAG_PLUS (1 << 1)
# define FLAG_SPACE (1 << 2)
# define FLAG_ZERO (1 << 3)
# define FLAG_HT (1 << 4)
# define FLAG_APOSTROPHE (1 << 5)
# define FLAG_PRECIS (1 << 6)
# define FLAG_MINFW (1 << 7)
# define NAN (pfd->f != pfd->f)
# define POSINF (pfd->f == 1.0 / 0.0)
# define NEGINF (pfd->f == -1.0 / 0.0)
# define BUFF_SIZE 32

# include "libft.h"

typedef enum		e_convtype
{
	CONV_BIN,
	CONV_CHAR,
	CONV_CHAR_BIN,
	CONV_CHAR_UHEX_LWRCASE,
	CONV_CHAR_UHEX_UPRCASE,
	CONV_CHAR_INT,
	CONV_CHAR_UINT,
	CONV_CHAR_UOCT,
	CONV_DOUBLE,
	CONV_FLOAT,
	CONV_UHEX_LWRCASE,
	CONV_UHEX_UPRCASE,
	CONV_INT,
	CONV_LONG_DOUBLE,
	CONV_LONG_BIN,
	CONV_LONG_UHEX_LWRCASE,
	CONV_LONG_UHEX_UPRCASE,
	CONV_LONG_INT,
	CONV_LONG_UINT,
	CONV_LONG_UOCT,
	CONV_LONGLONG_BIN,
	CONV_LONGLONG_UHEX_LWRCASE,
	CONV_LONGLONG_UHEX_UPRCASE,
	CONV_LONGLONG_INT,
	CONV_LONGLONG_UINT,
	CONV_LONGLONG_UOCT,
	CONV_PERCENT,
	CONV_PTR,
	CONV_SHORT_BIN,
	CONV_SHORT_UHEX_LWRCASE,
	CONV_SHORT_UHEX_UPRCASE,
	CONV_SHORT_INT,
	CONV_SHORT_UINT,
	CONV_SHORT_UOCT,
	CONV_STRING,
	CONV_UINT,
	CONV_UOCT,
	CONV_INVALID = 99
}					t_convtype;

typedef struct		s_colour
{
	char			*uk_key;
	size_t			uk_keylen;
	char			*us_key;
	size_t			us_keylen;
	char			*value;
	size_t			valuelen;
}					t_colour;

typedef struct		s_kvpair
{
	char			*key;
	t_convtype		value;
	size_t			keylen;
}					t_kvpair;

typedef struct		s_sprintf_data
{
	char			*dst;
	char			*dst_walker;
}					t_sprintf_data;

typedef struct		s_writer
{
	size_t			(*write)(struct s_writer *self, const char *str,
						size_t len);
	void			*data;
	int				written;
}					t_writer;

typedef struct		s_argprops
{
	int				minfw;
	int				precision;
	int				flags;
	t_convtype		convtype;
	t_writer		*writer;
}					t_argprops;

typedef void		(*t_print_fn)(
						t_argprops *props, va_list args, t_writer *writer);

typedef struct		s_printer
{
	void			(*print)(struct s_printer *self, char *str, size_t len);
}					t_printer;

typedef struct		s_print_float_data
{
	long double		f;
	long double		decimals;
	int				decimator;
	char			*prefix;
	int				prefix_len;
	char			*pre_separator;
	int				pre_separator_len;
	char			*separator;
	int				separator_len;
	char			*post_separator;
	int				post_separator_len;
	char			*postfix;
	int				postfix_len;
}					t_print_float_data;

int					fill_pfd(t_argprops *props, va_list args,
						t_print_float_data *pfd);
void				print_binary(t_argprops *props, va_list args,
						t_writer *writer);
void				print_char(t_argprops *props, va_list args,
						t_writer *written);
int					print_colour(char **str, t_writer *writer,
						const int chars_remaining);
void				print_float(t_argprops *props, va_list args,
						t_writer *written);
void				fill_post_separator(
						t_argprops *props, t_print_float_data *pfd);
void				print_fn();
void				print_int(t_argprops *props, va_list args,
						t_writer *written);
void				print_percent(t_argprops *props, va_list args,
						t_writer *written);
void				print_str(t_argprops *props, va_list args,
						t_writer *written);
void				print_uint(t_argprops *props, va_list args,
						t_writer *written);
void				props_finder(char **str, t_argprops *props,
						int steps, va_list args);
void				round_off(int i, t_print_float_data *pfd, char *str);
void				print_ptr(t_argprops *props, va_list args,
						t_writer *written);
void				print_uint_prefix(t_argprops *props, int *written,
						unsigned long long ull);
void				uint_minfw_padder(t_argprops *props, int *written);
size_t				file_write(t_writer *self, const char *str, size_t len);
size_t				str_write(t_writer *self, const char *str, size_t len);
size_t				out_write(t_writer *self, const char *str, size_t len);
void				putnstr_w(t_writer *writer, const char *str, size_t len);

#endif
