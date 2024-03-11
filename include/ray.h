#ifndef RAY_H
# define RAY_H

#include "../include/vecteur.h"
#include "../include/raytracing.h"

// typedef struct s_ray 
// {
//     t_tuple origin;    // L'origine du rayon
//     t_tuple direction; // La direction du rayon
// } t_ray;

typedef struct {
    void *object; // Un pointeur vers l'objet intersecté
    double t;     // La valeur t de l'intersection
} t_intersection;

typedef struct {
    int count;
    t_intersection *intersections; // Un tableau dynamique d'intersections
} t_intersections;

t_tuple position(t_ray ray, double t);

#endif 