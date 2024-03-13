#ifndef LIGHT_H
#define LIGHT_H

#include "raytracing.h"
#include "vecteur.h"

typedef struct s_light t_light;

t_light *create_light(t_tuple position, t_color intensity, double brightness);
t_material material();
t_sphere create_sphere();

#endif