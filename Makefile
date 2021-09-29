NAME:=	scop

# FILES AND FOLDERS

SRC_FILES:=	constructors\
			file_handler\
			sdl_handler\
			main\
			opengl_handler\
			printers\
			shader_compiler
INC_FILES:=	main

SRC_DIR:=	src
OBJ_DIR:=	.obj
INC_DIR:=	inc

SRCS:=	$(patsubst %,$(SRC_DIR)/%.c,$(SRC_FILES))
OBJS:=	$(patsubst %,$(OBJ_DIR)/%.o,$(SRC_FILES))
INCS:=	$(patsubst %,$(INC_DIR)/%.h,$(INC_FILES))

# LIBRARIES

LIBS_DIR:=		libs

LIBFT_NAME:=	libft
LIBFT_DIR:=		$(LIBS_DIR)/libft
LIBFT:=			$(LIBFT_DIR)/$(LIBFT_NAME).a

SDL2_DIR?=		~/.brew
SDL2_INC?=		$(SDL2_DIR)/include
SDL2_LIB?=		$(SDL2_DIR)/lib

# COMPILATION

CFLAGS?=	-Wall -Wextra -Werror\
			-I$(INC_DIR)\
			-I$(LIBFT_DIR)/includes\
			-I$(SDL2_INC)\
			-D GL_SILENCE_DEPRECATION
LDFLAGS?=	-L$(LIBFT_DIR) -lft\
			-lSDL2 -lSDL2main\
			-framework OpenGL
DEBUGFLAGS?=-g -DDEBUG

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "Compiling $@ executable"
	@$(CC) $(LDFLAGS) -o $@ $(OBJS)

$(LIBFT):
	@echo "Compiling libft library"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS)
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
	@$(CC) $(CFLAGS) $(LDFLAGS) $(DEBUGFLAGS) -o $(NAME) $(SRCS)

.PHONY: all clean fclean re debug
