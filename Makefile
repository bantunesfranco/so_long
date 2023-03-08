RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
CYAN=\033[1;36m
END=\033[0m

CC = gcc
CFLAGS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -g -fsanitize=address
NAME = so_long

SOURCES = main.c\
		utils/arrays_and_lists.c\
		utils/init_game.c\
		maps/make_map.c\
		maps/validate_map.c\
		maps/validate_path.c\
		player/actions.c\
		player/stats.c\
		graphics/draw_player.c\
		graphics/render_walls.c

LIBFT = libft/libft.a
MLX = MLX42/build/libmlx42.a

SRCS = ${addprefix ${DIR_S}/,${SOURCES}}

DIR_S = srcs
DIR_I = incs

${NAME}: ${SRCS} 
	@cmake MLX42 -B MLX42/build
	@make -C MLX42/build -j4
	@make -s -C libft
	@echo "${BLUE}Compiling ${NAME}${END}"
	@${CC} ${CFLAGS} ${SRCS} ${LIBFT} ${MLX} -I ${DIR_I} -I  MLX42/include/ -o ${NAME}
	@echo "${GREEN}Done!${END}"

test:
	@cmake MLX42 -B MLX42/build
	@make -C MLX42/build -j4
	@make -s -C libft
	@echo "${YELLOW}Testing ${NAME}${END}"
	@${CC} ${CFLAGS} -fsanitize=address ${SRCS} ${LIBFT} ${MLX} -I ${DIR_I} -I MLX42/include -o ${NAME}
	@echo "${GREEN}Done!${END}"

bonus: ${NAME}

all: ${NAME}

clean:
	@make -s -C libft
	@echo "${RED}Removing MLX42${END}"
	@rm -rf MLX42/build
	@echo "${GREEN}Done!${END}"

fclean: clean
	@echo "${RED}Removing ${NAME}${END}"
	@rm -rf ${NAME}
	@echo "${GREEN}Done!${END}"

re: fclean all

git:
	git commit -m "auto commit"
	git push

update:
	git submodule update --recursive --remote

.PHONY: all clean fclean re bonus test update git