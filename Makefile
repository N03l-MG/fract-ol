################################################################################
#                                                                              #
#                                    MAKEFILE                                  #
# Project:     fract-ol                                                        #
# Created:     19/11/2024                                                      #
# Author:      kixk                                                            #
#                                                                              #
################################################################################


################################################################################
###############                     BUILD SETUP                  ###############
################################################################################

NAME = fractol
CC = cc
FLAGS = -Wall -Wextra -Werror -flto -Ofast -march=native -MMD -MP $(addprefix -I, $(INCLUDES))
LDFLAGS = -flto
LIBFT = ./libft/libft.a
MLX = ./MLX42/build/libmlx42.a

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

SRCS = fractol_main.c fractol_render.c fractol_math.c fractol_error.c fractol_userinput.c \
	   fractol_ui.c fractol_color.c fractol_utils.c

OBJ = $(addprefix $(OBJECTS)/, $(SRCS:.c=.o))

################################################################################
###############                 COMPILATION RULES                ###############
################################################################################

all: mlx_lib ft_lib $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $^ $(LIBFT) $(MLX) $(MLX_FLAGS) -o $@

$(OBJECTS)/%.o: %.c | $(OBJECTS)
	@$(CC) $(FLAGS) -c $< -o $@ $(LDFLAGS)

$(OBJECTS):
	@mkdir -p $@

mlx_lib:
	cd MLX42 && cmake -B build && make -C build -j4

ft_lib:
	$(MAKE) -C libft

clean:
	rm -rf $(OBJECTS)
	$(MAKE) -C libft clean
	cd MLX42 && rm -rf build

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(OBJ:.o=.d)

.PHONY: all clean fclean re