#include "../include/vecteur.h"
#include "../include/mlxinit.h"

typedef struct s_projectile {
    t_tuple position;
    t_tuple velocity;
} t_projectile;

typedef struct s_environment {
    t_tuple gravity;
    t_tuple wind;
} t_environment;


// Fonction pour dessiner un carré à une position donnée
void draw_square2(t_mlx *mlx, int x, int y, int size, int color) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int pixel = ((y + i) * mlx->line_length) + ((x + j) * (mlx->bits_per_pixel / 8));
            if ((x + j) >= 0 && (x + j) < mlx->width && (y + i) >= 0 && (y + i) < mlx->height) {
                *(int *)(mlx->addr + pixel) = color;
            }
        }
    }
}

// Fonction de mise à jour appelée par mlx_loop_hook
int update(void *param) {
    static int y = 500; // Position initiale du projectile
    t_mlx *mlx = (t_mlx *)param;

    // Efface l'écran
    mlx_clear_window(mlx->ptr, mlx->win);

    // Dessine le projectile et met à jour sa position
    draw_square2(mlx, 400, y, 10, 0xFFFFFF); // Dessine en blanc
    y -= 5; // Fait monter le projectile

    // Vérifie la condition de fin
    if (y < 0) exit(0); // Quitte si le projectile sort de l'écran

    return 1;
}

// int main() {
//     t_mlx mlx;

//     mlx.ptr = mlx_init();
//     mlx.width = 800;
//     mlx.height = 600;
//     mlx.win = mlx_new_window(mlx.ptr, mlx.width, mlx.height, "Projectile Simple");

//     mlx_loop(mlx.ptr); // Commence la boucle d'événements
//     return 0;
// }