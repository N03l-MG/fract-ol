################################################################################
#                                                                              #
#                                    MAKEFILE                                  #
# Project:     fract-ol                                                        #
# Created:     19/11/2024                                                      #
# Author:      Noel Monzon (nmonzon)                                           #
#                                                                              #
################################################################################


################################################################################
###############                     BUILD SETUP                  ###############
################################################################################

NAME = libft.a
CC = cc
FLAGS = -Wall -Wextra -Werror -MMD -MP $(addprefix -I, $(INCLUDES))
LIBFT = ./libft/libft.a
MLX = ./MLX42/libmlx42.a

ifeq ($(shell uname), Darwin)
	MLX_FLAGS = -ldl -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -pthread -lm
else ifeq ($(shell uname), Linux)
	MLX_FLAGS = -L./MLX42/build -lglfw -ldl -pthread -lm
endif

################################################################################
###############                     DIRECTORIES                  ###############
################################################################################

INCLUDES = ./include ./libft ./MLX42/include/MLX42
SOURCES = ./src
OBJECTS = _obj

vpath %.h $(INCLUDES)
vpath %.c $(SOURCES)

################################################################################
###############                    SOURCE FILES                  ###############
################################################################################

SRCS = fractol_main.c fractol_window.c fractol_error.c

OBJ = $(addprefix $(OBJECTS)/, $(SRCS:.c=.o))

################################################################################
###############                 COMPILATION RULES                ###############
################################################################################

all: submodule mlx_lib ft_lib $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $^ $(LIBFT) $(MLX) $(MLX_FLAGS) -o $@

$(OBJECTS)/%.o: %.c | $(OBJECTS)
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJECTS):
	@mkdir -p $@

submodule:
	@git submodule update --init

mlx_lib:
	cd MLX42 && cmake -B build && make -C build -j4

ft_lib:
	$(MAKE) -C libft

clean:
	rm -rf $(OBJECTS)
	$(MAKE) -C libft clean
	cd MLX42 && $(MAKE) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(OBJ:.o=.d)

.PHONY: all clean fclean re