#include "../include/mlxinit.h"


void put_pixel_to_img(t_mlx *mlx, int x, int y, int color) 
{
    if (!mlx || !mlx->addr)
        return;
    int pixel_index = (y * mlx->line_length) + (x * (mlx->bits_per_pixel / 8));
    *(unsigned int*)(mlx->addr + pixel_index) = mlx_get_color_value(mlx->ptr, color);
}


t_mlx   *mlx_init_and_create_window(int width, int height, char *title)
{
    t_mlx   *mlx;

    mlx = (t_mlx *)malloc(sizeof(t_mlx));
    if (!mlx)
        return (NULL);
    mlx->ptr = mlx_init();
    if (!mlx->ptr)
    {
        free(mlx);
        return (NULL);
    }
    mlx->win = mlx_new_window(mlx->ptr, width, height, title);
    if (!mlx->win)
    {
        free(mlx);
        return (NULL);
    }
    mlx->img = NULL;
    mlx->width = width;
    mlx->height = height;
    return (mlx);
}

int mlx_create_image(t_mlx *mlx)
{
    mlx->img = mlx_new_image(mlx->ptr, mlx->width, mlx->height);
    if (!mlx->img)
        return (0);
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
                                  &mlx->line_length, &mlx->endian);
    return (1);
}

void mlx_cleanup(t_mlx *mlx)
{
    if (mlx->img)
        mlx_destroy_image(mlx->ptr, mlx->img);
    if (mlx->win)
        mlx_destroy_window(mlx->ptr, mlx->win);
    if (mlx->ptr)
        free(mlx->ptr);
    free(mlx);
}

void draw_square(t_mlx *mlx, int x, int y, int size, int color)
{
    int i;
    int j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            // Calculer la position en mémoire du pixel à colorier
            int pixel = (y + i) * mlx->line_length + (x + j) * (mlx->bits_per_pixel / 8);

            // Vérifier si on est dans les limites de l'image
            if ((x + j) < mlx->width && (y + i) < mlx->height)
            {
                // Modifier la couleur du pixel
                *(int*)(mlx->addr + pixel) = color;
            }
        }
    }
}

void draw_vector(t_mlx *mlx, t_tuple *vec, int color)
{
    int i;
    int j;

    // Parcourir chaque pixel à l'intérieur des limites du carré
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            // Calculer la position en mémoire du pixel à colorier
            int pixel = (vec->y + i) * mlx->line_length + (vec->x + j) * (mlx->bits_per_pixel / 8);

            // Vérifier si on est dans les limites de l'image
            if ((vec->x + j) < mlx->width && (vec->y + i) < mlx->height)
            {
                // Modifier la couleur du pixel
                *(int*)(mlx->addr + pixel) = color;
            }
        }
    }
}

// int main(int ac, char **argv)
// {
//     (void)ac;
//     (void)argv;
//     // t_mlx *mlx;

//     // mlx = mlx_init_and_create_window(800, 600, "miniRT");
//     // if (!mlx)
//     //     return (1);

//     // if (!mlx_create_image(mlx))
//     // {
//     //     mlx_cleanup(mlx);
//     //     return (1);
//     // }
//     // t_vec3 v = vector(100, 100, 0);
//     // draw_square(mlx, 100, 100, 50, 0x00FF0000);
//     // draw_vector(mlx, &v(100, 100, 0), 0x00FF0000);
//     // // Brancher le gestionnaire de touches
//     // mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
//     // mlx_key_hook(mlx->win, handle_keypress, mlx);

//     // // Brancher le gestionnaire de fermeture de la fenêtre
//     // mlx_hook(mlx->win, 17, 0L, close_window, mlx);

//     // // Lancer la boucle d'événements
//     // mlx_loop(mlx->ptr);

//     return (0);
// }

