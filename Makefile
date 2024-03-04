NAME = miniRT

LIBFT_DIR = lib/libft
FT_PRINTF_DIR = lib/ft_printf
GNL_DIR = lib/GNL
MLX_DIR = lib/mlx_linux

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# / pour compiler sous Mac, rajouter ceci a mlx_flags ==> -framework OpenGL -framework AppKit

MLX_FLAGS = -L$(MLX_DIR) -lmlx 

INC_FLAGS = -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I$(GNL_DIR) -I$(MLX_DIR) -lXext -lX11 -lm -lbsd

SRCS = parser/minirt.c parser/print.c parser/parse_utils.c \
		parser/parse.c parser/utils.c parser/free.c parser/object.c \
		mlx/mlx.c mlx/event.c vecteur/vecteur.c vecteur/projectile.c \
		matrice/matrice.c matrice/rotation.c matrice/submatrix.c \
		ray/ray.c raytracing/vecteur_test.c

OBJ = $(SRCS:.c=.o)

LIBS = $(LIBFT_DIR)/libft.a $(FT_PRINTF_DIR)/libftprintf.a $(GNL_DIR)/libgnl.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(OBJ) -o $(NAME) $(LIBS) $(MLX_FLAGS) $(INC_FLAGS)

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

$(FT_PRINTF_DIR)/libftprintf.a:
	make -C $(FT_PRINTF_DIR)

$(GNL_DIR)/libgnl.a:
	make -C $(GNL_DIR)

# Règle pour nettoyer les objets
clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(FT_PRINTF_DIR) clean
	make -C $(GNL_DIR) clean

# Règle pour nettoyer tout ce qui est compilé
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(FT_PRINTF_DIR) fclean
	make -C $(GNL_DIR) fclean

re: fclean all