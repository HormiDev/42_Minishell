# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/10 21:51:45 by ide-dieg          #+#    #+#              #
#    Updated: 2025/05/07 13:28:11 by ide-dieg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc

SRC =	src/ft_array_to_list.c \
		src/ft_create_heredocs.c \
		src/ft_exit.c \
		src/ft_getenv.c \
		src/ft_parsing_and_exec.c \
		src/ft_refresh_env_array.c \
		src/ft_update_prompt.c \
		src/utils.c \
		src/ft_builtin_management.c \
		src/ft_echo.c \
		src/ft_export.c \
		src/ft_history.c \
		src/ft_pipeline.c \
		src/ft_save_heredocs.c \
		src/main.c \
		src/ft_cd.c \
		src/ft_errors.c \
		src/ft_export_utils.c \
		src/ft_init_env.c \
		src/ft_print_env.c \
		src/ft_search_in_path.c \
		src/mini_exec.c \
		src/ft_config_signals.c \
		src/ft_execute.c \
		src/ft_files.c \
		src/ft_loading_minishell.c \
		src/ft_pwd.c \
		src/ft_unset.c \
		src/tokenizer/create_cmd.c \
		src/tokenizer/create_data_container.c \
		src/tokenizer/ft_unquoted_dollar_variable_converter.c \
		src/tokenizer/parsing.c \
		src/tokenizer/special_tokens_management.c \
		src/tokenizer/tokenizer.c \
		src/tokenizer/create_cmd_list.c \
		src/tokenizer/dollar_variables_management.c \
		src/tokenizer/parenthesis_checker.c \
		src/tokenizer/parsing_checker.c \
		src/tokenizer/token_checker_mandatory.c \

SRC_BONUS =	src_bonus/ft_array_to_list_bonus.c \
			src_bonus/ft_create_heredocs_bonus.c \
			src_bonus/ft_export_bonus.c \
			src_bonus/ft_loading_minishell_bonus.c \
			src_bonus/ft_pwd_bonus.c \
			src_bonus/main_bonus.c \
			src_bonus/ft_echo_bonus.c \
			src_bonus/ft_export_utils_bonus.c \
			src_bonus/ft_refresh_env_array_bonus.c \
			src_bonus/mini_exec_bonus.c \
			src_bonus/ft_builtin_management_bonus.c \
			src_bonus/ft_errors_bonus.c \
			src_bonus/ft_files_bonus.c \
			src_bonus/ft_parsing_and_exec_bonus.c \
			src_bonus/ft_save_heredocs_bonus.c \
			src_bonus/ft_execute_bonus.c \
			src_bonus/ft_getenv_bonus.c \
			src_bonus/ft_pipeline_bonus.c \
			src_bonus/ft_search_in_path_bonus.c \
			src_bonus/utils_bonus.c \
			src_bonus/ft_cd_bonus.c \
			src_bonus/ft_exit_bonus.c \
			src_bonus/ft_history_bonus.c \
			src_bonus/ft_print_env_bonus.c \
			src_bonus/ft_unset_bonus.c \
			src_bonus/ft_config_signals_bonus.c \
			src_bonus/ft_init_env_bonus.c \
			src_bonus/ft_update_prompt_bonus.c \
			src_bonus/tokenizer/create_cmd_bonus.c \
			src_bonus/tokenizer/ft_manage_wildcards_bonus.c \
			src_bonus/tokenizer/ft_wildcards_utils_bonus.c \
			src_bonus/tokenizer/special_tokens_management_bonus.c \
			src_bonus/tokenizer/create_cmd_list_bonus.c \
			src_bonus/tokenizer/ft_order_wildcards_bonus.c \
			src_bonus/tokenizer/parenthesis_checker_bonus.c \
			src_bonus/tokenizer/token_checker_bonus.c \
			src_bonus/tokenizer/create_data_container_bonus.c \
			src_bonus/tokenizer/ft_process_wildcards_bonus.c \
			src_bonus/tokenizer/parsing_bonus.c \
			src_bonus/tokenizer/tokenizer_bonus.c \
			src_bonus/tokenizer/dollar_variables_management_bonus.c \
			src_bonus/tokenizer/ft_unquoted_dollar_variable_converter_bonus.c \
			src_bonus/tokenizer/parsing_checker_bonus.c

OBJDIR  = obj
OBJ     = $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))
OBJDIR_BONUS = obj_bonus
OBJ_BONUS = $(addprefix $(OBJDIR_BONUS)/, $(notdir $(SRC_BONUS:.c=.o)))

CFLAGS  = -Wall -Wextra -Werror 
LDFLAGS = -lreadline
LIBSA   = 42_Libft/libft.a

vpath %.c src src/tokenizer src_bonus src_bonus/tokenizer

all: $(NAME)

# Regla genérica para cualquiera de los .c en src/ o src/tokenizer/
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Regla genérica para cualquiera de los .c en src_bonus/ o src_bonus/tokenizer/
$(OBJDIR_BONUS)/%.o: %.c
	@mkdir -p $(OBJDIR_BONUS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): ide-dieg minishell_title update_submodules build_libft $(OBJ)
	@echo "Building $(NAME)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBSA) $(LDFLAGS)
	@tput cuu1 && tput el
	@echo "$(VERDE)$(NAME) built!$(NC)"

bonus: ide-dieg minishell_title update_submodules build_libft $(OBJ_BONUS)
	@echo "Building $(NAME) bonus..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_BONUS) $(LIBSA) $(LDFLAGS)
	@tput cuu1 && tput el
	@echo "$(VERDE)$(NAME) bonus built!$(NC)"

# Limpieza
clean: fclean_libft
	rm -rf $(OBJDIR) $(OBJDIR_BONUS)

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

ide-dieg:
	@clear	
	@echo "$(ROJO)██╗██████╗ ███████╗    ██████╗ ██╗███████╗ ██████╗ $(AZUL)         ██╗  ██╗██████╗ "
	@echo "$(ROJO)██║██╔══██╗██╔════╝    ██╔══██╗██║██╔════╝██╔════╝ $(AZUL)         ██║  ██║╚════██╗"
	@echo "$(ROJO)██║██║  ██║█████╗█████╗██║  ██║██║█████╗  ██║  ███╗$(AZUL)         ███████║ █████╔╝"
	@echo "$(ROJO)██║██║  ██║██╔══╝╚════╝██║  ██║██║██╔══╝  ██║   ██║$(AZUL)         ╚════██║██╔═══╝ "
	@echo "$(ROJO)██║██████╔╝███████╗    ██████╔╝██║███████╗╚██████╔╝$(AZUL)              ██║███████╗"
	@echo "$(ROJO)╚═╝╚═════╝ ╚══════╝    ╚═════╝ ╚═╝╚══════╝ ╚═════╝ $(AZUL)              ╚═╝╚══════╝"
	@echo "$(NARANJA)██████╗  █████╗  ██████╗ ██╗███╗   ███╗███████╗███╗   ██╗ ██████╗ $(VERDE)     ██╗  "
	@echo "$(NARANJA)██╔══██╗██╔══██╗██╔════╝ ██║████╗ ████║██╔════╝████╗  ██║██╔═══██╗$(VERDE) ██╗ ╚═██╗"
	@echo "$(NARANJA)██║  ██║███████║██║  ███╗██║██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║$(VERDE) ╚═╝   ██║"
	@echo "$(NARANJA)██║  ██║██╔══██║██║   ██║██║██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║$(VERDE) ██╗   ██║"
	@echo "$(NARANJA)██████╔╝██║  ██║╚██████╔╝██║██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝$(VERDE) ╚═╝ ██╔═╝"
	@echo "$(NARANJA)╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚═╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝ $(VERDE)     ╚═╝  $(NC)"

minishell_title:
	@echo " _  _  __  __ _  __  ____  _  _  ____  __    __   "
	@echo "( \/ )(  )(  ( \(  )/ ___)/ )( \(  __)(  )  (  )  "
	@echo "/ \/ \ )( /    / )( \___ \) __ ( ) _) / (_/\/ (_/\ "
	@echo "\_)(_/(__)\_)__)(__)(____/\_)(_/(____)\____/\____/"
