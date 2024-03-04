#include <stdio.h>
#include <math.h>
#include "../include/raytracing.h"
#include "../include/matrix.h"


t_tuple calculate_transformed_normal(t_ray *ray, t_sphere *sphere, double t, Matrice4x4 transformation_matrix) {
    // Calcul du point d'intersection en espace monde
    t_tuple intersection_point_world = add_tuples(ray->origin, multiply_tuple(ray->direction, t));

    // Conversion du point d'intersection vers l'espace objet
    Matrice4x4 inverse_transformation = inverse_matrix(transformation_matrix);
    t_tuple intersection_point_object = multiplyMatrixByTuple(inverse_transformation, intersection_point_world);

    // Calcul de la normale en espace objet
    t_tuple normal_object_space = subtract_tuples(intersection_point_object, sphere->center);
    t_tuple normalized_normal_object_space = normalize_tuple(normal_object_space);

    // Conversion de la normale retour à l'espace monde
    Matrice4x4 transpose_of_inverse = transposeMatrix(inverse_transformation);
    t_tuple normal_world_space = multiplyMatrixByTuple(transpose_of_inverse, normalized_normal_object_space);
    normal_world_space.w = 0.0; // Assurer que c'est traité comme un vecteur
    t_tuple normalized_normal_world_space = normalize_tuple(normal_world_space);
    return normalized_normal_world_space;
}


t_tuple calculate_normal_at_point(t_sphere *sphere, t_ray *ray, double t) {
    // Calcul du point d'intersection
    t_tuple point = add_tuples(ray->origin, multiply_tuple(ray->direction, t));
    // Calcul du vecteur normale au point d'intersection
    t_tuple normal = subtract_tuples(point, sphere->center);
    // Normalisation du vecteur normale
    t_tuple normalized_normal = normalize_tuple(normal);
    return normalized_normal;
}

t_tuple calculate_normal_at_point_in_object_space(t_sphere *sphere, t_tuple intersection_point) {
    // Soustraction du centre de la sphère (qui est l'origine dans l'espace objet) au point d'intersection
    t_tuple normal = subtract_tuples(intersection_point, sphere->center);
    // Normalisation du vecteur pour obtenir la normale
    t_tuple normalized_normal = normalize_tuple(normal);
    return normalized_normal;
}

t_tuple convert_normal_to_world_space(t_tuple normal_in_object_space, Matrice4x4 transformation_matrix) {
    // Inverse de la matrice de transformation
    Matrice4x4 inverse_transformation = inverse_matrix(transformation_matrix);
    // Transposition de la matrice inversée
    Matrice4x4 transpose_of_inverse = transposeMatrix(inverse_transformation);
    // Multiplication de la normale dans l'espace objet par la matrice de transposition inverse
    t_tuple normal_in_world_space = multiplyMatrixByTuple(transpose_of_inverse, normal_in_object_space);
    // Remise à zéro de la composante w pour garantir que c'est un vecteur et non un point
    normal_in_world_space.w = 0.0;
    // Normalisation du vecteur pour s'assurer qu'il reste de longueur unitaire
    t_tuple normalized_normal_in_world_space = normalize_tuple(normal_in_world_space);
    return normalized_normal_in_world_space;
}


/*

Résumé les étapes essentielles pour recalculer la normale à un point d'intersection entre un vecteur (rayon)
et une sphère, surtout en tenant compte des transformations appliquées à l'objet

Pour recalculer la normale a un point d'intersection entre un vecteur et une sphere,
c'est simple(mais comment faire ?)
Le plus dur reside dans le fait de calculer la nornmale lors de d'une transformation d'un object.
Il faut d'abord convertir le point d'intersection rayon sphere qui est en espace monde en epsace object
(espace monde = cadre de reference global de la scene) // (espace object = cadre de reference local d'un object)
pour cela il faut multiplier le point par l'inverse de la matrice de la transformation applique a l'object
une fois le point convertit, la normale est calcule comme si l'object n'a subit aucune transformation.
pour une sphere on doit soustraire le centre de la sphere du point de surface pour obtenir le vecteru normale ce vecteur et ensuite normalise
Ensuite il faut reconvertir la normale en espace monde cela implique de multiplier la normale par la matrice de transposition inverse de la matrice originale

*/