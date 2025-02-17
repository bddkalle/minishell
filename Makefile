# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fschnorr <fschnorr@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/13 14:10:53 by fschnorr          #+#    #+#              #
#    Updated: 2025/02/13 16:50:57 by fschnorr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCLUDE = -I include $(LIBFT_INCLUDES)
SRC =	$(addsuffix .c,							\
		$(addprefix src/, 						\
								main			\
		))										\
		$(addsuffix .c,							\
		$(addprefix src/error/, 				\
								error			\
		))										\
		$(addsuffix .c,							\
		$(addprefix src/utils/, 				\
								init			\
								prompt			\
		))															
OBJS := $(SRC:.c=.o)

LIBFT_INCLUDES = -I $(LIBFT_DIR)/includes
LIBFT_DIR = lib/libft
LIBFT_AR = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra
MFLAGS = --no-print-directory
VFLAGS = -g -O0

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR) $(MFLAGS)
	@echo -n "run cc for minishell..."
	@$(CC) $^ $(LIBFT_AR) -o $(NAME) $(CFLAGS) $(INCLUDE)
	@echo "done"

%.o: %.c
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

clean:
	@rm -f $(OBJS)

fclean: clean
	@echo -n "run fclean for minishell..."
	@rm -f $(NAME)
	@echo "done"
	@make fclean -C $(LIBFT_DIR) $(MFLAGS)

re: fclean all

debug: CFLAGS += -g -O0
debug: $(NAME)
	@gdb so_long

run: re
	@./$(NAME) $(ARG) || true

valgrind: CFLAGS += -g -O0
valgrind: re
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(NAME) $(ARG)

checkup: CFLAGS += -Werror
checkup:
	@echo "Checking for memory leaks..."
	@make valgrind || true
	@make norm

norm:
	@echo "Checking for norm compliance..."
	@norminette

.PHONY: all setup clean fclean re debug run valgrind checkup norm
