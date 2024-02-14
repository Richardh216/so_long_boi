NAME  = so_long

CFLAGS = -g -O3 -Werror -Wextra -Wall

CC = gcc

LIB = lib

OBJ_DIR = obj/

SRC_DIR = src/

LIBMLX := ./lib/MLX42

HEADERS := -I ./include -I $(LIBMLX)/include

SRC := main.c gnl_utils.c get_next_line.c map_n_check.c solv_check.c init.c build.c collectibles.c freedom.c movement.c

OBJ = $(SRC:.c=.o)

SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

LIBS = $(LIBMLX)/build/libmlx42.a

LDFLAGS := -ldl -lglfw -pthread -lm -flto -framework Cocoa -framework OpenGL -framework IOKit

LIBFT = ./libft/libft.a

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(HEADERS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	cd	libft && make
	mkdir lib && cd lib && git clone https://github.com/codam-coding-college/MLX42.git
	cd lib/MLX42 && cmake -B build && cmake --build build -j4

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) $(HEADERS) $(LDFLAGS) -o $(NAME)

clean:
	cd libft && make clean
	rm -rf $(OBJ_DIR)
	rm -rf ./lib

fclean: clean
	cd libft && make fclean
	rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re
