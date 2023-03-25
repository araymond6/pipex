NAME = pipex
LIBFT = libft/libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra

LIB_DIR = libft
SRC_DIR = src
INC_DIR = include

SRCS = src/main.c src/utils.c src/parsing.c src/process.c
OBJS = $(SRCS:%.c=%.o)
DEP = $(INC_DIR)/pipex.h

# Colors
RESET = \033[0m
YELLOW = \033[93m
BLUE = \033[94m

all: lib $(NAME)

%.o: %.c $(DEP)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	@echo "$(BLUE)------$(YELLOW) Compiling pipex.. $(BLUE)------$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)
	@echo "$(BLUE)-------$(YELLOW) Pipex compiled! $(BLUE)-------$(RESET)"

lib:
	@echo "$(BLUE)------$(YELLOW) Compiling libft.. $(BLUE)------$(RESET)"
	@make -C $(LIB_DIR)
	@echo "$(BLUE)-------$(YELLOW) Libft compiled! $(BLUE)-------$(RESET)"

clean:
	@echo "$(BLUE)-----$(YELLOW) Cleaning project... $(BLUE)-----$(RESET)"
	@make clean -C $(LIB_DIR)
	@rm -rf $(OBJS)
	@echo "$(BLUE)------$(YELLOW) Project cleaned!! $(BLUE)------$(RESET)"

fclean: clean
	@echo "$(BLUE)-----$(YELLOW) Removing program... $(BLUE)-----$(RESET)"
	@make fclean -C $(LIB_DIR)
	@rm -rf $(NAME)
	@echo "$(BLUE)------$(YELLOW) Program removed!! $(BLUE)------$(RESET)"

re: fclean all