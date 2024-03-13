
#include "../include/dashboard.h"

#define KEY_A 'a'
#define KEY_S 's'
#define KEY_D 'd'
#define KEY_F 'f'
#define KEY_G 'g'
#define KEY_H 'h'
#define KEY_J 'j'
#define KEY_K 'k'

void afficher_dashboard(t_scene *scene) {
    char info[128];
    int yOffset = 20; // Début de l'affichage en Y
    int yStep = 20; // Pas vertical entre les lignes

    sprintf(info, "Ambient: %.2f", scene->dashboard.material->ambient);
    mlx_string_put(scene->mlx->ptr, scene->mlx->win, 10, yOffset, 0xFFFFFF, info);

    sprintf(info, "Diffuse: %.2f", scene->dashboard.material->diffuse);
    mlx_string_put(scene->mlx->ptr, scene->mlx->win, 10, yOffset + yStep, 0xFFFFFF, info);

    sprintf(info, "Specular: %.2f", scene->dashboard.material->specular);
    mlx_string_put(scene->mlx->ptr, scene->mlx->win, 10, yOffset + 2 * yStep, 0xFFFFFF, info);

    sprintf(info, "Shininess: %.2f", scene->dashboard.material->shininess);
    mlx_string_put(scene->mlx->ptr, scene->mlx->win, 10, yOffset + 3 * yStep, 0xFFFFFF, info);
}


int gestion_entree(int keycode, t_scene *scene) {
    switch (keycode) {
        case KEY_A: // Augmenter l'ambiant
            scene->dashboard.material->ambient = fmin(scene->dashboard.material->ambient + 0.1, 1.0);
            break;
        case KEY_D: // Diminuer l'ambiant
            scene->dashboard.material->ambient = fmax(scene->dashboard.material->ambient - 0.1, 0.0);
            break;
        case KEY_S: // Augmenter le diffus
            scene->dashboard.material->diffuse = fmin(scene->dashboard.material->diffuse + 0.1, 1.0);
            break;
        case KEY_F: // Diminuer le diffus
            scene->dashboard.material->diffuse = fmax(scene->dashboard.material->diffuse - 0.1, 0.0);
            break;
        case KEY_G: // Augmenter le spéculaire
            scene->dashboard.material->specular = fmin(scene->dashboard.material->specular + 0.1, 1.0);
            break;
        case KEY_H: // Diminuer le spéculaire
            scene->dashboard.material->specular = fmax(scene->dashboard.material->specular - 0.1, 0.0);
            break;
        case KEY_J: // Augmenter la brillance
            scene->dashboard.material->shininess = fmin(scene->dashboard.material->shininess + 5, 100); // La plage peut varier selon vos besoins
            break;
        case KEY_K: // Diminuer la brillance
            scene->dashboard.material->shininess = fmax(scene->dashboard.material->shininess - 5, 0); // La plage peut varier selon vos besoins
            break;
        default:
            return 0;
    }

    redraw_scene(scene);
    return 0;
}

