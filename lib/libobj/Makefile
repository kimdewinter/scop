NAME:=	libobj

# FILES AND FOLDERS

SRC_FILES:=	extractor\
			libobj\
			utils\
			vector
INC_FILES:=	libobj_internal\
			libobj\
			vector
TEST_MAIN=	$(SRC_DIR)/main.c

SRC_DIR:=	src
OBJ_DIR:=	.obj
INC_DIR:=	include

SRCS:=	$(patsubst %,$(SRC_DIR)/%.c,$(SRC_FILES))
OBJS:=	$(patsubst %,$(OBJ_DIR)/%.o,$(SRC_FILES))
INCS:=	$(patsubst %,$(INC_DIR)/%.h,$(INC_FILES))

# COMPILATION

CFLAGS?=	-Wall -Wextra -Werror\
			-I$(INC_DIR)
DEBUGFLAGS?=-g

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling $@ executable"
	@ar crs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@echo "Cleaning $(NAME) object files"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Removing $(NAME)"
	@rm -rf $(NAME) $(NAME).dSYM

re: fclean all

debug: $(SRCS) $(INCS)
	@echo "Compiling debuggable $(NAME) executable"
	@$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(NAME) $(SRCS) $(TEST_MAIN)

.PHONY: all clean fclean re debug
