RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
CYAN=\033[1;36m
END=\033[0m

CC = gcc
CFLAGS =  -Wall -Werror -Wextra -g #-fsanitize=address
NAME = so_long
LIBFT = libft/libft.a
MLX = MLX42/build/libmlx42.a

DIR_S = srcs
DIR_I = incs
DIR_O = obj

INCS = -I $(DIR_I) -I libft/$(DIR_I) -IMLX42/include

SRCS = main.c\
		graphics/draw_player.c graphics/draw_poi.c graphics/make_player_anim.c graphics/make_poi_anim.c \
		graphics/play_anim.c graphics/render_map.c graphics/render_walls.c graphics/ui.c \
		utils/arrays_and_lists.c utils/end_game.c utils/exit.c \
		utils/init_game.c utils/reset_game.c utils/split_texture.c\
		maps/make_map.c maps/validate_map.c maps/validate_path.c\
		player/actions.c player/stats.c 

OBJS =  ${SRCS:%.c=${DIR_O}/%.o}

ifeq ($(OS), Windows_NT)
	FW_FLAGS := -lglfw3 -lopengl32 -lgdi32
	NAME := so_long.exe
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		FW_FLAGS := -ldl -lglfw -pthread -lm
	else ifeq ($(UNAME_S), Darwin)
		FW_FLAGS := -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
	else
		$(error OS: $(OS) is not supported!)
	endif
endif

all: ${NAME}

${MLX}:
	@cmake MLX42 -B MLX42/build
	@make -C MLX42/build -j4

${NAME}: ${MLX} ${OBJS} ${DIR_I}/${NAME}.h
	@make -s -C libft
	@echo "${BLUE}Compiling ${NAME}${END}"
	@${CC} ${CFLAGS} ${FW_FLAGS} ${OBJS} ${LIBFT} ${MLX} -o ${NAME} 
	@echo "${GREEN}Done!${END}"

${OBJS}: ${DIR_O}/%.o: ${DIR_S}/%.c
	@mkdir -p ${@D}
	@echo "${BLUE}Compiling $<${END}"
	@${CC} ${CFLAGS} ${INCS} -c $< -o $@

bonus: ${NAME}

clean:
	@make clean -s -C libft 
	@echo "${RED}Removing MLX42${END}"
	@rm -rf MLX42/build
	@echo "${RED}Removing objs${END}"
	@rm -rf obj
	@echo "${GREEN}Done!${END}"

fclean: clean
	@echo "${RED}Removing ${NAME}${END}"
	@rm -rf ${NAME}
	@echo "${GREEN}Done!${END}"

re: fclean all

git:
	git commit
	git push

submodules:
	git pull --recurse-submodules

update:
	git submodule update libft

.PHONY: all clean fclean re bonus update git