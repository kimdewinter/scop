NAME:=	scop

# FILES AND FOLDERS

SRC_FILES:=	buffer_handler\
			centralizer\
			event_handler\
			file_handler\
			opengl_handler\
			obj_loader\
			printers\
			sdl_handler\
			shader_compiler\
			utils\
			texture_handler\
			transformation_handler\
			main_args_parser\
			main\
			glad# For MAC, remove this file
INC_FILES:=	main\
			glad\
			khrplatform# For MAC, remove "glad" and "khrplatform"

SRC_DIR:=	src
OBJ_DIR:=	.obj
INC_DIR:=	include

SRCS:=	$(patsubst %,$(SRC_DIR)/%.c,$(SRC_FILES))
OBJS:=	$(patsubst %,$(OBJ_DIR)/%.o,$(SRC_FILES))
INCS:=	$(patsubst %,$(INC_DIR)/%.h,$(INC_FILES))

# LIBRARIES

LIBS_DIR:=		lib

LIBFT_NAME:=	libft
LIBFT_DIR:=		$(LIBS_DIR)/libft
LIBFT:=			$(LIBFT_DIR)/$(LIBFT_NAME).a

# FOR MAC
#SDL2_INC?=		~/.brew/include
#SDL2_LIB?=		~/.brew/lib
# FOR LINUX
SDL2_INC?=		/usr/include
SDL2_LIB?=		/usr/lib/x86_64-linux-gnu/libSDL2.a\
				/usr/lib/x86_64-linux-gnu/libSDL2main.a
# END FOR

LIBOBJ_NAME=	libobj
LIBOBJ_DIR:=	$(LIBS_DIR)/libobj
LIBOBJ:=		$(LIBOBJ_DIR)/$(LIBOBJ_NAME).a

LIBMATH_NAME=	libmath
LIBMATH_DIR:=	$(LIBS_DIR)/libmath
LIBMATH:=		$(LIBMATH_DIR)/$(LIBMATH_NAME).a

# COMPILATION

CFLAGS?=	-Wall -Wextra -Werror\
			-I$(INC_DIR)\
			-I$(LIBFT_DIR)/includes\
			-I$(LIBOBJ_DIR)/include\
			-I$(LIBMATH_DIR)/include\
			-I$(SDL2_INC)\
			-D GL_SILENCE_DEPRECATION
# FOR MAC, add: -framework OpenGL
LDFLAGS?=	-L$(LIBFT_DIR) -lft\
			-L$(LIBOBJ_DIR) -lobj\
			-L$(LIBMATH_DIR) -lmath\
			-L/usr/lib -lSDL2 -lSDL2main\
			-ldl -lm
DEBUGFLAGS?=-g -DDEBUG

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBOBJ) $(LIBMATH)
	@echo "Compiling $@ executable"
	@$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(LIBFT):
	@echo "Compiling libft library"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(LIBOBJ):
	@echo "Compiling libobj library"
	@$(MAKE) -s -C $(LIBOBJ_DIR)

$(LIBMATH):
	@echo "Compiling libmath library"
	@$(MAKE) -s -C $(LIBMATH_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@echo "Cleaning $(NAME) object files"
	@rm -rf $(OBJ_DIR)
	@echo "Cleaning $(LIBFT_NAME) object files"
	@make clean -s -C $(LIBFT_DIR)
	@echo "Cleaning $(LIBOBJ_NAME) object files"
	@make clean -s -C $(LIBOBJ_DIR)
	@echo "Cleaning $(LIBMATH_NAME) object files"
	@make clean -s -C $(LIBMATH_DIR)

fclean: clean
	@echo "Removing $(NAME)"
	@rm -rf $(NAME) $(NAME).dSYM
	@echo "Removing $(LIBFT_NAME)"
	@make fclean -s -C $(LIBFT_DIR)
	@echo "Removing $(LIBOBJ_NAME)"
	@make fclean -s -C $(LIBOBJ_DIR)
	@echo "Removing $(LIBMATH_NAME)"
	@make fclean -s -C $(LIBMATH_DIR)

re: fclean all

debug: $(LIBFT) $(LIBOBJ) $(LIBMATH) $(SRCS) $(INCS)
	@echo "Compiling debuggable $(NAME) executable"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(DEBUGFLAGS) -o $(NAME) $(SRCS)

.PHONY: all clean fclean re debug
