#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "parse.h"
#include "raytracing.h"
#include "matrix.h"
#include "ray.h"
#include "light.h"

typedef struct s_scene t_scene;

int gestion_entree(int keycode, t_scene *scene);
void afficher_dashboard(t_scene *scene);

#endif