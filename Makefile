# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kde-wint <kde-wint@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/04 11:44:17 by kde-wint      #+#    #+#                  #
#    Updated: 2021/08/04 20:03:23 by kde-wint      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME:=	scop

CFLAGS?=	-Wall -Wextra -Werror

# FILES AND FOLDERS

SRC_FILES:=	main
INC_FILES:=	main

SRC_DIR:=	src
OBJ_DIR:=	.obj
INC_DIR:=	inc

SRCS=	$(patsubst %,$(SRC_DIR)/%.c,$(SRC_FILES))
OBJS=	$(patsubst %,$(OBJ_DIR)/%.o,$(SRC_FILES))
INCS=	$(patsubst %,$(INC_DIR)/%.h,$(INC_FILES))

# LIBRARIES

LIBFT_NAME:=	libft
LIBFT_DIR:=		libft
LIBFT=			$(LIBFT_DIR)/$(LIBFT_NAME).a
LIBFT_INC=		$(LIBFT_DIR)/includes
LIBFT_FLAGS=	-L$(LIBFT_DIR) -lft

# INCLUDES

INCLUDES=	-I$(INC_DIR)\
			-I$(LIBFT_INC)

# COMPILATION

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "Compiling $@ executable"
	@$(CC) $(CFLAGS) -o $@ $^

$(LIBFT):
	@echo "Compiling libft library"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(OBJS): $(SRCS) $(INCS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) -o $@ $< $(INCLUDES)

clean:
	@echo "Cleaning $(NAME) object files"
	@if [ -d $(OBJ_DIR) ]; then rm -rf $(OBJ_DIR); fi
	@echo "Cleaning $(LIBFT_NAME) object files"
	@make clean -s -C $(LIBFT_DIR)

fclean: clean
	@echo "Removing $(NAME)"
	@rm -rf $(NAME)
	@echo "Removing $(LIBFT_NAME)"
	@make fclean -s -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
