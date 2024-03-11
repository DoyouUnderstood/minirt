#include "../include/mlxinit.h"
#include "../include/raytracing.h"

// MAC
// #define KEY_ESC 0xff1b
// #define KEY_RIGHT 123
// #define KEY_LEFT 124
// #define KEY_UP 126
// #define KEY_DOWN 125
// #define KEY_SHRINK_ROTATE 1 // s
// #define KEY_SHRINK_SHEAR 2  // d

// LINUX
#define KEY_ESC 0xff1b
#define KEY_RIGHT 0xff53
#define KEY_LEFT 0xff51
#define KEY_UP 0xff52
#define KEY_DOWN 0xff54
#define KEY_SHRINK_ROTATE 'q' // s
#define KEY_SHRINK_SHEAR 'w'  // d

int handle_keypress(int keysym, t_mlx *mlx)
{
    if (keysym == KEY_ESC)
    {
        mlx_cleanup(mlx); // Nettoie et libère les ressources
        exit(0); // Ferme l'application
    }
    return (0);
}

int close_window(t_mlx *mlx)
{
    exit(0);
    mlx_cleanup(mlx);
    return (0);
}


void apply_transformation_to_sphere(t_sphere *sphere, Matrice4x4 transformation) {
    sphere->center = multiplyMatrixByTuple(transformation, sphere->center);
}

int handle_key(int keycode, void *param) {
    t_scene *scene = (t_scene*)param;
    Matrice4x4 transformation = initMatriceIdentite();
    t_object *current_object;

    if (keycode == KEY_RIGHT) {
        transformation = translation_matrix(1, 0, 0);
    } else if (keycode == KEY_LEFT) {
        transformation = translation_matrix(-1, 0, 0);
    } else if (keycode == KEY_DOWN) {
        transformation = translation_matrix(0, -1, 0);
    } else if (keycode == KEY_UP) {
        transformation = translation_matrix(0, 1, 0);
    } else if (keycode == KEY_SHRINK_ROTATE) {
        Matrice4x4 rotation = rotation_z(M_PI / 4);
        Matrice4x4 scaling = scaling_matrix(0.5, 1, 1);
        transformation = multiplyMatrices(rotation, scaling);
    } else if (keycode == KEY_SHRINK_SHEAR) {
        Matrice4x4 shearing = shearing_matrix(1, 0, 0, 0, 0, 0);
        Matrice4x4 scaling = scaling_matrix(0.5, 1, 1);
        transformation = multiplyMatrices(shearing, scaling);
    }
    else
    {
        return (0);
    }
    current_object = scene->objects.head;
    while (current_object != NULL) {
        if (current_object->type == SPHERE) {
            apply_transformation_to_sphere((t_sphere *)current_object->obj, transformation);
        }
        current_object = current_object->next;
    }
    redraw_scene(scene);
    return 0;
}
