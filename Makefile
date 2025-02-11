# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmaria <lmaria@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 15:20:43 by lmaria            #+#    #+#              #
#    Updated: 2025/02/11 15:11:58 by lmaria           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = so_long
SUBNAME = libft.a

# Compilateur et flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Dossiers
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
MLX_DIR = includes/minilibx-linux
LIBFT_DIR = includes/LibftUpToDate

# Fichiers source
SRC_FILES = main.c map_parser.c map_checker.c display.c window.c textures.c map_utils.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Flags pour MiniLibX et Libft
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
LIBFT_INC = -I$(LIBFT_DIR) -I$(MLX_DIR)

# Commandes Make
all: $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJS) $(MLX_DIR)/libmlx.a $(LIBFT_DIR)/libft.a
	@echo "Compiling $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)
	@echo "Executable $(NAME) created."

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(LIBFT_INC) -c $< -o $@

# Création du dossier obj si inexistant
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compilation de MiniLibX et Libft
$(MLX_DIR)/libmlx.a:
	@$(MAKE) --no-print-directory -C $(MLX_DIR)

$(LIBFT_DIR)/libft.a:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

# Nettoyage des fichiers objets
clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean --no-print-directory -C $(MLX_DIR)
	@$(MAKE) clean --no-print-directory -C $(LIBFT_DIR)

# Nettoyage complet (objets + exécutable)
fclean: clean
	@echo "Full clean, removing $(NAME)"
	@rm -f $(NAME)
	@$(MAKE) fclean --no-print-directory -C $(LIBFT_DIR)

# Recompilation complète
re: fclean all

# Règles pour éviter les erreurs Make
.PHONY: all clean fclean re
