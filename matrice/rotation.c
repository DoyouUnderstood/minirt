#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/vecteur.h"
#include "../include/mlxinit.h"

// Applique une rotation autour de l'axe X à un point
t_tuple rotateX(t_tuple point, double angle) {
    t_tuple rotatedPoint;
    
    rotatedPoint.x = point.x;
    rotatedPoint.y = point.y * cos(angle) - point.z * sin(angle);
    rotatedPoint.z = point.y * sin(angle) + point.z * cos(angle);
    rotatedPoint.w = point.w; // La rotation ne change pas la composante w

    return rotatedPoint;
}

// Rotation autour de l'axe Y
t_tuple rotateY(t_tuple point, double angle) {
    t_tuple rotatedPoint;
    
    rotatedPoint.x = point.x * cos(angle) + point.z * sin(angle);
    rotatedPoint.y = point.y;
    rotatedPoint.z = -point.x * sin(angle) + point.z * cos(angle);
    rotatedPoint.w = point.w; // La rotation ne change pas la composante w

    return rotatedPoint;
}

// Rotation autour de l'axe Z
t_tuple rotateZ(t_tuple point, double angle) {
    t_tuple rotatedPoint;
    
    rotatedPoint.x = point.x * cos(angle) - point.y * sin(angle);
    rotatedPoint.y = point.x * sin(angle) + point.y * cos(angle);
    rotatedPoint.z = point.z;
    rotatedPoint.w = point.w; // La rotation ne change pas la composante w

    return rotatedPoint;
}

// Applique une transformation de cisaillement sur un point
t_tuple shear(t_tuple point, double sh_xy, double sh_xz, double sh_yx, double sh_yz, double sh_zx, double sh_zy) {
    t_tuple shearedPoint;
    
    shearedPoint.x = point.x + sh_xy * point.y + sh_xz * point.z;
    shearedPoint.y = point.y + sh_yx * point.x + sh_yz * point.z;
    shearedPoint.z = point.z + sh_zx * point.x + sh_zy * point.y;
    shearedPoint.w = point.w; // La transformation de cisaillement ne change pas la composante w

    return shearedPoint;
}


#define WIDTH 1400
#define HEIGHT 1400

typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
} t_data;

typedef struct s_point {
    double x;
    double y;
} t_point;

// Fonction pour dessiner un pixel sur le canevas
void my_mlx_pixel_put(t_data *data, int x, int y, int color) {
    mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
}

// Fonction pour calculer la position des heures et les dessiner
void draw_clock(t_data *data) {
    t_point center = {WIDTH / 2, HEIGHT / 2};
    double radius = WIDTH * 3 / 8;
    double angle;
    int i;
    t_point hour_pos;

    for (i = 0; i < 12; i++) {
        angle = M_PI / 6 * i;
        hour_pos.x = center.x + radius * cos(angle);
        hour_pos.y = center.y + radius * sin(angle);
        my_mlx_pixel_put(data, hour_pos.x, hour_pos.y, 0xFFFFFF);
    }
}

// int main(void) {
//     t_data data;

//     data.mlx_ptr = mlx_init();
//     data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Horloge Analogique");
    
//     draw_clock(&data);
    
//     mlx_loop(data.mlx_ptr);
//     return (0);
// }
