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
			main
ifeq ($(shell uname),Linux)
SRC_FILES+=	glad
endif

INC_FILES:=	main
ifeq ($(shell uname),Linux)
INC_FILES+=	glad\
			khrplatform
endif

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

ifeq ($(shell uname),Darwin)
SDL2_INC?=		~/.brew/include
endif
ifeq ($(shell uname),Linux)
SDL2_INC?=		/usr/include
endif

LIBOBJ_NAME=	libobj
LIBOBJ_DIR:=	$(LIBS_DIR)/libobj
LIBOBJ:=		$(LIBOBJ_DIR)/$(LIBOBJ_NAME).a

LIBMATH_NAME=	libmath
LIBMATH_DIR:=	$(LIBS_DIR)/libmath
LIBMATH:=		$(LIBMATH_DIR)/$(LIBMATH_NAME).a

ifeq ($(shell uname),Darwin)
LIBCGLM_NAME=	libcglm_mac
endif
ifeq ($(shell uname),Linux)
LIBCGLM_NAME=	libcglm_linux
endif
LIBCGLM_DIR:=	$(LIBS_DIR)/libcglm
LIBCGLM:=		$(LIBCGLM_DIR)/$(LIBCGLM_NAME).a

# COMPILATION

CFLAGS?=	-Wall -Wextra -Werror\
			-I$(INC_DIR)\
			-I$(LIBFT_DIR)/includes\
			-I$(LIBOBJ_DIR)/include\
			-I$(LIBMATH_DIR)/include\
			-I$(SDL2_INC)\
			-I$(LIBCGLM_DIR)/include/cglm\
			-D GL_SILENCE_DEPRECATION
LDFLAGS?=	-L$(LIBFT_DIR) -lft\
			-L$(LIBOBJ_DIR) -lobj\
			-L$(LIBMATH_DIR) -lmath\
			-L$(LIBCGLM_DIR) -$(patsubst lib%,l%,$(LIBCGLM_NAME))\
			-lSDL2 -lSDL2main
ifeq ($(shell uname),Darwin)
LDFLAGS+=	-framework OpenGL
endif
ifeq ($(shell uname),Linux)
LDFLAGS+=	-ldl -lm
endif
DEBUGFLAGS?=-g -DDEBUG

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBOBJ) $(LIBMATH) $(INCS)
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

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
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
	@$(CC) $(DEBUGFLAGS) -o $(NAME) $(SRCS) $(CFLAGS) $(LDFLAGS)

.PHONY: all clean fclean re debug
