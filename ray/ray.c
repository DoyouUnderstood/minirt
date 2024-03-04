#include <stdio.h>
#include "../include/ray.h"

// Fonction pour initialiser un rayon
t_ray create_ray(t_tuple origin, t_tuple direction) {
    t_ray ray;
    ray.origin = origin;
    ray.direction = direction;
    return ray;
}

// Fonction pour afficher un rayon
void print_ray(t_ray ray) {
    printf("Ray Origin: (%.2f, %.2f, %.2f)\n", ray.origin.x, ray.origin.y, ray.origin.z);
    printf("Ray Direction: (%.2f, %.2f, %.2f)\n", ray.direction.x, ray.direction.y, ray.direction.z);
}

// Fonction pour calculer le point à la distance t le long du rayon
t_tuple position(t_ray ray, double t) 
{
    t_tuple displacement = multiply_tuple(ray.direction, t);
    return add_tuples(ray.origin, displacement);
}


// int main() {
//     t_tuple origin = point(2, 3, 4); // Origine du rayon
//     t_tuple direction = vector(1, 0, 0); // Direction du rayon
//     t_ray ray = {origin, direction}; // Création du rayon

//     t_tuple pos0 = position(ray, 0); // Point à la distance 0
//     t_tuple pos1 = position(ray, 1); // Point à la distance 1
//     t_tuple posNeg1 = position(ray, -1); // Point à la distance -1
//     t_tuple pos2_5 = position(ray, 2.5); // Point à la distance 2.5

//     printf("Position à t=0 : (%.2f, %.2f, %.2f)\n", pos0.x, pos0.y, pos0.z);
//     printf("Position à t=1 : (%.2f, %.2f, %.2f)\n", pos1.x, pos1.y, pos1.z);
//     printf("Position à t=-1 : (%.2f, %.2f, %.2f)\n", posNeg1.x, posNeg1.y, posNeg1.z);
//     printf("Position à t=2.5 : (%.2f, %.2f, %.2f)\n", pos2_5.x, pos2_5.y, pos2_5.z);
//     return 0;
// }