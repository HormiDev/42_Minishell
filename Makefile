# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/10 21:51:45 by ide-dieg          #+#    #+#              #
#    Updated: 2025/02/19 22:11:27 by ide-dieg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
CFILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LDFLAGS = -lreadline
OFILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(CFILES))
LIBFT = 42_Libft/libft.a

all: $(NAME)

$(NAME): update_submodules build_libft $(OFILES)
	$(CC) $(CFLAGS) $(BUILD_DIR)/*.o $(LIBFT) -o $(NAME) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c |  $(BUILD_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean: fclean_libft
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


build_libft:
	@if [ ! -f 42_Libft/libft.a ]; then \
		echo "$(NARANJA)Compiling Libft...$(NC)"; \
		make all -C 42_Libft > /dev/null 2>&1; \
		tput cuu1 && tput el; \
		echo "$(VERDE)Libft compiled!$(NC)"; \
	fi

fclean_libft:
	@echo "Cleaning Libft..."
	@make fclean -C 42_Libft > /dev/null 2>&1
	@echo "Libft cleaned!"

update_submodules:
	@echo "$(NARANJA)Updating submodules...$(NC)"
	@git submodule update --init --recursive > /dev/null 2>&1
	@tput cuu1 && tput el
	@echo "$(VERDE)Submodules updated!$(NC)"

ROJO = \033[0;31m
NC = \033[0m
NARANJA = \033[0;33m
AZUL = \033[0;34m
VERDE = \033[0;32m