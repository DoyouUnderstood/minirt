#ifndef DASHBOARD_H
#define DASHBOARD_H


#include "raytracing.h"
#include "matrix.h"
#include "ray.h"
#include "light.h"

typedef struct s_dashboard {
    t_material *material;
    void *mlx_ptr;
    void *win_ptr;
} t_dashboard;

int gestion_entree(int keycode, t_dashboard *dashboard);
void afficher_dashboard(t_dashboard *dashboard, void *mlx_ptr, void *win_ptr);

#endif