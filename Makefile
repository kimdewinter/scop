# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kde-wint <kde-wint@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/08/04 11:44:17 by kde-wint      #+#    #+#                  #
#    Updated: 2021/08/06 16:28:10 by kde-wint      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#don't forget to change "SDL2_INC" and "SDL2_LIB" to
#your local locations of SDL2's .h and .a files respectively

NAME:=	scop

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

SDL2_INC?=		/Users/kde-wint/.brew/Cellar/sdl2/2.0.14_1/include/SDL2
SDL2_LIB?=		/Users/kde-wint/.brew/Cellar/sdl2/2.0.14_1/lib -lSDL2

# COMPILATION

CFLAGS?=	-Wall -Wextra -Werror\
			-I$(INC_DIR)\
			-I$(LIBFT_DIR)/includes\
			-I$(SDL2_INC)
LDFLAGS?=	-L$(LIBFT_DIR) -lft\
			-L$(SDL2_LIB) -lSDL2\
			-framework OpenGL

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "Compiling $@ executable"
	@$(CC) $(LDFLAGS) -o $@ $<

$(LIBFT):
	@echo "Compiling libft library"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(OBJS): $(SRCS) $(INCS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) -o $@ $<

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

debug: $(LIBFT) $(SRCS) $(INCS)
	@echo "Compiling debuggable $(NAME) executable"
	@$(CC) $(CFLAGS) $(LDFLAGS) -g -o $(NAME) $(SRCS)

.PHONY: all clean fclean re debug
