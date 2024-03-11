#include "../include/object.h"
#include "../include/parse.h"
#include "../include/vecteur.h"

// Fonction pour créer une nouvelle lumière ponctuelle
t_light *point_light(t_tuple position, t_color intensity, double brightness) 
{
    t_light *new_light = (t_light *)malloc(sizeof(t_light));
    if (!new_light) {
        return NULL;
    }
    new_light->position = position;
    new_light->color = intensity;
    new_light->brightness = brightness;
    return new_light;
}

// Fonction pour créer un matériau avec des valeurs par défaut
t_material material() {
    t_material m;

    m.color.r = 25.0;
    m.color.g = 25.0;
    m.color.b = 25.0;
    m.ambient = 0.1;
    m.diffuse = 0.9;
    m.specular = 0.9;
    m.shininess = 200.0;

    return m;
}

// Fonction pour créer une sphère avec un matériau par défaut
t_sphere sphere() {
    t_sphere s;
    
    s.center = (t_tuple){0.0, 0.0, 0.0, 0};
    s.diameter = 1.0;
    s.material = material();

    return s;
}

