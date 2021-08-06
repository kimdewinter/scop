# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kde-wint <kde-wint@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2019/08/13 19:02:32 by kde-wint      #+#    #+#                  #
#    Updated: 2021/08/04 17:25:30 by kde-wint      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
EXTRA =
FLAGS = -Wall -Werror -Wextra $(EXTRA)

CC=gcc

SRC_DIR=.
OBJ_DIR=./.obj
INC_DIR=./includes
TEST_MAIN=main.c

OBJ_NAMES=	\
			ft_atoi \
			ft_bzero \
			ft_countchr \
			ft_fprintf \
			ft_findnextline \
			ft_findnextword \
			ft_get_next_line \
			ft_isalnum \
			ft_isalpha \
			ft_isascii \
			ft_isdigit \
			ft_iseven \
			ft_isprint \
			ft_itoa \
			ft_fprintf \
			ft_lastchar \
			ft_lastchari \
			ft_lookup \
			ft_lstalloc \
			ft_lstadd \
			ft_lstdel \
			ft_lstdelone \
			ft_lstiter \
			ft_lstmap \
			ft_lstnew \
			ft_lltoa \
			ft_lltoa_base \
			ft_memalloc \
			ft_memccpy \
			ft_memchr \
			ft_memcmp \
			ft_memcpy \
			ft_memdel \
			ft_memmove \
			ft_memset \
			ft_powllong \
			ft_printf \
			ft_putendl \
			ft_putendl_fd \
			ft_putchar \
			ft_putchar_fd \
			ft_putnbr \
			ft_putnbr_fd \
			ft_putstr \
			ft_putstr_fd \
			ft_putstrn \
			ft_putstrn_fd \
			ft_skipalnum \
			ft_skipchars \
			ft_skipdigits \
			ft_sprintf \
			ft_sqrt \
			ft_strcap \
			ft_strcat \
			ft_strchr \
			ft_strclr \
			ft_strcmp \
			ft_strcpy \
			ft_strdel \
			ft_strdup \
			ft_strequ \
			ft_striter \
			ft_striteri \
			ft_strjoin \
			ft_strlcat \
			ft_strlen \
			ft_strmap \
			ft_strmapi \
			ft_strncat \
			ft_strncmp \
			ft_strndup \
			ft_strnequ \
			ft_strncpy \
			ft_strnew \
			ft_strnstr \
			ft_strrchr \
			ft_strreplace \
			ft_strrev \
			ft_strsplit \
			ft_strstr \
			ft_strsub \
			ft_strtolower \
			ft_strtoupper \
			ft_strtrim \
			ft_substrreplace \
			ft_tolower \
			ft_toupper \
			ft_ulltoa \
			ft_ulltoa_base \
			print_binary \
			print_char \
			print_colour \
			print_float \
			print_float_aux \
			print_float_roundoff \
			print_float_post_separator \
			print_int \
			print_percent \
			print_ptr \
			print_uint \
			print_uint_aux \
			print_str \
			props_parser \
			writers \

OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(OBJ_NAMES))
SRCS = $(patsubst %, $(SRC_DIR)/%.c, $(OBJ_NAMES))

all: $(NAME)

$(NAME): $(OBJS)
	@ar crs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c -o $@ $<

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME) a.out a.out.dSYM test.txt

re:
	$(MAKE) fclean
	$(MAKE) all
