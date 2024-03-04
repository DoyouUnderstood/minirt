#include <stdio.h>
#include "../include/ray.h"

// calculate_discriminant: Calcule le discriminant de l'équation quadratique pour l'intersection rayon-sphère.
double calculate_discriminant(double a, double b, double c) {
    return b * b - 4 * a * c;
}

// initialize_intersections: Initialise une structure t_intersections vide.
t_intersections initialize_intersections() {
    t_intersections intersections;
    intersections.count = 0;
    intersections.intersections = NULL;
    return intersections;
}

// fill_intersections: Remplit la structure t_intersections avec les intersections trouvées.
void fill_intersections(t_intersections *intersections, double discriminant, double a, double b, t_sphere sphere) {
    double sqrt_discriminant = sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2 * a);
    double t2 = (-b + sqrt_discriminant) / (2 * a);

    intersections->count = discriminant > 0 ? 2 : 1;
    intersections->intersections = malloc(sizeof(t_intersection) * intersections->count);
    
    intersections->intersections[0].t = t1;
    intersections->intersections[0].object = &sphere; // Assurez-vous d'avoir un moyen de passer la sphère correctement
    if (discriminant > 0) {
        intersections->intersections[1].t = t2;
        intersections->intersections[1].object = &sphere; // De même ici
    }
}

// sort_intersections: Trie les intersections par valeur t croissante.
void sort_intersections(t_intersections *intersections) {
    if (intersections->count > 1 && intersections->intersections[0].t > intersections->intersections[1].t) {
        t_intersection temp = intersections->intersections[0];
        intersections->intersections[0] = intersections->intersections[1];
        intersections->intersections[1] = temp;
    }
}


// intersect_sphere: Calcule les intersections d'un rayon avec une sphère, renvoyant un ensemble d'intersections.

t_intersections intersect_sphere(t_sphere sphere, t_ray ray) {
    t_tuple sphere_to_ray = subtract_tuples(ray.origin, vector(sphere.center.x, sphere.center.y, sphere.center.z));
    double a = dot(ray.direction, ray.direction);
    double b = 2 * dot(ray.direction, sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - pow(sphere.diameter / 2, 2);
    double discriminant = calculate_discriminant(a, b, c);
    t_intersections intersections = initialize_intersections();

    if (discriminant >= 0) {
        fill_intersections(&intersections, discriminant, a, b, sphere);
        sort_intersections(&intersections);
    }

    return intersections;
}

