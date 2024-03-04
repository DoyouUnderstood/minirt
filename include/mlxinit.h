#ifndef MLXINIT_H
# define MLXINIT_H

//#include "parse.h"
#include "vecteur.h"
#include <unistd.h>
#include <stdlib.h>
#include "../lib/mlx/mlx.h"

typedef struct s_mlx
{
    void    *ptr;   // Pointeur vers la connexion MLX
    void    *win;   // Pointeur vers la fenêtre
    void    *img;   // Pointeur vers l'image
    char    *addr;  // Adresse de l'image en mémoire
    int     bits_per_pixel; // Nombre de bits par pixel
    int     line_length;    // Longueur d'une ligne de l'image en octets
    int     endian;         // Endianess de l'image
    int     width;          // Largeur de l'image
    int     height;         // Hauteur de l'image
}               t_mlx;

int handle_key(int keycode, void *param);
void put_pixel_to_img(t_mlx *mlx, int x, int y, int color);
int handle_keypress(int keysym, t_mlx *mlx);
int close_window(t_mlx *mlx);
void mlx_cleanup(t_mlx *mlx);
t_mlx   *mlx_init_and_create_window(int width, int height, char *title);
int mlx_create_image(t_mlx *mlx);
void draw_square(t_mlx *mlx, int x, int y, int size, int color);
#endif