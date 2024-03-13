#ifndef RAY_H
# define RAY_H

#include "../include/raytracing.h"
#include "../include/vecteur.h"

// typedef struct s_ray 
// {
//     t_tuple origin;    // L'origine du rayon
//     t_tuple direction; // La direction du rayon
// } t_ray;

typedef struct s_ray t_ray;

typedef struct {
    void *object; // Un pointeur vers l'objet intersecté
    double t;     // La valeur t de l'intersection
} t_intersection;

typedef struct {
    int count;
    t_intersection *intersections; // Un tableau dynamique d'intersections
} t_intersections;

t_tuple position(t_ray ray, double t);
void fill_intersections(t_intersections *intersections, double discriminant, double a, double b, t_sphere sphere);
t_intersections initialize_intersections();
void sort_intersections(t_intersections *intersections);
t_intersections intersect_sphere(t_sphere sphere, t_ray ray);

#endif 