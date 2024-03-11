
#include "../include/dashboard.h"

#define KEY_a 'a'
#define KEY_s 's'
#define KEY_d 'd'
#define KEY_f 'f'


void afficher_dashboard(t_dashboard *dashboard, void *mlx_ptr, void *win_ptr) {
    char info[128];

    sprintf(info, "Ambient: %.2f", dashboard->material->ambient);
    mlx_string_put(mlx_ptr, win_ptr, 10, 20, 0xFFFFFF, info);

    sprintf(info, "Diffuse: %.2f", dashboard->material->diffuse);
    mlx_string_put(mlx_ptr, win_ptr, 10, 40, 0xFFFFFF, info);

    // Continuez pour les autres propriétés...
}


int gestion_entree(int keycode, t_dashboard *dashboard) 
{
    switch (keycode) {
        case KEY_a: // Exemple pour augmenter l'ambiance
            dashboard->material->ambient = fmin(dashboard->material->ambient + 0.1, 1.0);
            break;
        case KEY_d: // Exemple pour diminuer l'ambiance
            dashboard->material->ambient = fmax(dashboard->material->ambient - 0.1, 0.0);
            break;
        case KEY_s: // Exemple pour augmenter la diffusion
            dashboard->material->diffuse = fmin(dashboard->material->diffuse + 0.1, 1.0);
            break;
        case KEY_f: // Exemple pour diminuer la diffusion
            dashboard->material->diffuse = fmax(dashboard->material->diffuse - 0.1, 0.0);
            break;
        default:
                return 0;
        }
    mlx_clear_window(dashboard->mlx_ptr, dashboard->win_ptr);
    afficher_dashboard(dashboard, dashboard->mlx_ptr, dashboard->win_ptr);    return 0;
}
