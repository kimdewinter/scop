# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kde-wint <kde-wint@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/04 11:44:17 by kde-wint      #+#    #+#                  #
#    Updated: 2021/08/06 12:09:31 by kde-wint      ########   odam.nl          #
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

SRCS:=	$(patsubst %,$(SRC_DIR)/%.c,$(SRC_FILES))
OBJS:=	$(patsubst %,$(OBJ_DIR)/%.o,$(SRC_FILES))
INCS:=	$(patsubst %,$(INC_DIR)/%.h,$(INC_FILES))

# LIBRARIES

LIBFT_NAME:=	libft
LIBFT_DIR:=		libft
LIBFT:=			$(LIBFT_DIR)/$(LIBFT_NAME).a
LIBFT_FLAGS:=	-L$(LIBFT_DIR) -lft

# COMPILATION

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "Compiling $@ executable"
	@$(CC) $(CFLAGS) -o $@ $< $(LIBFT_FLAGS)

$(LIBFT):
	@echo "Compiling libft library"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(OBJS): $(SRCS) $(INCS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) -o $@ $< -I$(INC_DIR)

clean:
	@echo "Cleaning $(NAME) object files"
	@rm -rf $(OBJ_DIR)
	@echo "Cleaning $(LIBFT_NAME) object files"
	@make clean -s -C $(LIBFT_DIR)

fclean: clean
	@echo "Removing $(NAME)"
	@rm -rf $(NAME) $(NAME).dSYM
	@echo "Removing $(LIBFT_NAME)"
	@make fclean -s -C $(LIBFT_DIR)

re: fclean all

debug: $(LIBFT)
	@echo "Compiling debuggable $(NAME) executable"
	@$(CC) $(CFLAGS) -g -o $(NAME) $(SRCS) -I$(INC_DIR) $(LIBFT_FLAGS)

.PHONY: all clean fclean re debug
