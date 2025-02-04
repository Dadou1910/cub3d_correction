MAKEFLAGS		+= --no-print-directory
MAKEFLAGS		+= --silent

NAME			= cub3D
CC				= cc
CFLAGS			= -g3
MLX_FLAGS		= -lXext -lX11 -lm -lz
INCLUDES_DIR	= includes
PARSING_DIR		= parsing
EXEC_DIR		= exec
OBJ_DIR			= .obj
LIBFT_DIR		= Libft
MLX_DIR			= minilib/mlx
INCLUDES_H		= -I./$(INCLUDES_DIR) -I./minilib/mlx
DEPS			= Makefile $(INCLUDES_DIR)/cub3D.h

EXEC_SRC		= $(EXEC_DIR)/main.c $(EXEC_DIR)/calculate_dist.c $(EXEC_DIR)/init.c \
					$(EXEC_DIR)/key_events.c $(EXEC_DIR)/move_player.c $(EXEC_DIR)/dda.c \
					$(EXEC_DIR)/rendering.c $(EXEC_DIR)/init_2.c \
					$(EXEC_DIR)/get_next_line.c
PARSING_SRC		= $(PARSING_DIR)/check_map.c $(PARSING_DIR)/check_texture.c \
					$(PARSING_DIR)/cleanup.c $(PARSING_DIR)/flood_fill.c $(PARSING_DIR)/parse_file.c \
					$(PARSING_DIR)/parsing_utils.c $(PARSING_DIR)/map_dimension.c \
					$(PARSING_DIR)/utils.c $(PARSING_DIR)/last.c
SOURCES			=  $(EXEC_SRC) $(GNL_SRC) $(PARSING_SRC)
EXEC_OBJ		= $(EXEC_SRC:$(EXEC_DIR)/%.c=$(OBJ_DIR)/$(EXEC_DIR)/%.o)
PARSING_OBJ		= $(PARSING_SRC:$(PARSING_DIR)/%.c=$(OBJ_DIR)/$(PARSING_DIR)/%.o)
OBJ_FILES		= $(EXEC_OBJ) $(PARSING_SRC)

all: $(NAME)

$(OBJ_DIR)/%.o: %.c $(DEPS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES_H) -c -o $@ $<

$(NAME): $(OBJ_FILES)
	@echo "\e[38;2;255;105;180mConfiguring MiniLibX...🌸\e[0m"
	@cd $(MLX_DIR) && ./configure > /dev/null 2>&1
	@echo "\e[38;2;255;105;180mBuilding libmlx.a...🌸\e[0m"
	@make -C $(MLX_DIR) -f Makefile.mk
	@make -C $(LIBFT_DIR)
	@echo "\e[38;2;255;105;180mBuilding $(NAME)...🌸\e[0m"
	@$(CC) $(CFLAGS) $(INCLUDES_H) $(OBJ_FILES) -L$(LIBFT_DIR) -L$(MLX_DIR) -lmlx -lft $(MLX_FLAGS) -o $(NAME)
	@echo "\e[38;2;235;21;133mDone ✨\e[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@make -C $(MLX_DIR) -f Makefile.mk clean
	@echo "\e[38;5;217mObject files of cub3D, mlx, and libft removed 🥰\e[0m"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make -C $(MLX_DIR) -f Makefile.mk clean
	@rm -f $(MLX_DIR)/libmlx.a
	@echo "\e[38;5;217m$(NAME), mlx, and libft removed 💖\e[0m"

re: fclean all

.PHONY: all clean fclean re
