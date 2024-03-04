/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecteur_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:48:04 by alletond          #+#    #+#             */
/*   Updated: 2024/02/21 17:32:12 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"
#include "raytracing.h"





void* find_first_object_of_type(t_obj_list *obj_list, t_obj_type type) {
    t_object *current = obj_list->head;
    while (current != NULL) {
        if (current->type == type) {
            return current->obj; // Retourne un pointeur vers l'objet trouvé
        }
        current = current->next;
    }
    return NULL; // Aucun objet du type spécifié n'a été trouvé
}

// Calcule le point le long du rayon à la distance t
// Cela se fait en multipliant la direction du rayon par t et en ajoutant le résultat à l'origine du rayon
// t_tuple position(t_ray ray, double t) {

//     t_tuple movement = multiply_tuple(ray.direction, t);
//     t_tuple pos = add_tuples(ray.origin, movement);
//     return pos;
// }


bool intersect_ray_sphere(t_ray *ray, t_sphere *sphere, double *t) {
    t_tuple sphere_to_ray = subtract_tuples(ray->origin, sphere->center);
    double a = dot(ray->direction, ray->direction);
    double b = 2 * dot(ray->direction, sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - pow(sphere->diameter / 2, 2.0); // Correction ici
    double discriminant = b*b - 4*a*c;

    if (discriminant < 0) {
        return false; // Pas d'intersection
    }

    double t0 = (-b - sqrt(discriminant)) / (2*a);
    double t1 = (-b + sqrt(discriminant)) / (2*a);

    double t_near = t0 < t1 ? t0 : t1;
    if (t_near < 0) t_near = t0 < t1 ? t1 : t0; // Prend l'autre t si t_near est négatif
    if (t_near < 0) return false; // Si t_near est toujours négatif, pas de hit

    *t = t_near;
    return true;
}



#include "../include/matrix.h"

t_ray transform_ray(Matrice4x4 mat, t_ray ray) {
    t_ray transformed_ray;
    transformed_ray.origin = multiplyMatrixByTuple(mat, ray.origin); // Transforme l'origine
    transformed_ray.direction = multiplyMatrixByTuple(mat, ray.direction); // Transforme la direction

    return transformed_ray;
}

#define KEY_RIGHT 65363
#define KEY_LEFT 65361

int handle_key(int keycode, void *param) {
    t_scene2 *scene = (t_scene2 *)param;
    Matrice4x4 translation;

    if (keycode == KEY_RIGHT) {
        translation = translation_matrix(1, 0, 0); // Crée une translation vers la droite
    } else if (keycode == KEY_LEFT) {
        translation = translation_matrix(-1, 0, 0); // Crée une translation vers la gauche
    }

    // Applique la translation et met à jour la transformation de la sphère
    scene->sphere->transform = multiplyMatrices(translation, scene->sphere->transform);
    redraw_scene(scene);

    return 0;
}


void throw_ray(t_sphere *sphere, void *mlx, void *mlx_win) {
    int width = 860;
    int height = 600;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Créer un rayon pour le pixel actuel
            t_tuple origin = point(0, 0, 0); // Supposons que la caméra est à l'origine
            t_tuple direction = normalize_tuple(vector(x - width / 2, y - height / 2, 100)); // Direction simplifiée
            t_ray ray = {origin, direction};

            double t = 0;
            Matrice4x4 inverse_transform =  (sphere->transform); // Inverse de la transformation de la sphère
            t_ray transformed_ray = transform_ray(inverse_transform, ray);
            if (intersect_ray_sphere(&transformed_ray, sphere, &t)) {
                // Si le rayon intersecte la sphère, colorier le pixel en rouge
                mlx_pixel_put(mlx, mlx_win, x, y, 0xFF0000);
            } else {
                // Sinon, le pixel reste noir ou la couleur de fond
                mlx_pixel_put(mlx, mlx_win, x, y, 0x000000);
            }
        }
    }
}

void redraw_scene(t_scene2 *scene) {
    // Effacer l'image précédente si elle existe
    if (scene->mlx->img) {
        mlx_destroy_image(scene->mlx->ptr, scene->mlx->img);
    }

    // Créer une nouvelle image
    if (!mlx_create_image(scene->mlx)) {
        return; // Gestion de l'erreur en cas de problème à la création de l'image
    }
    throw_ray(scene->sphere, scene->mlx->ptr, scene->mlx->win); 
    mlx_put_image_to_window(scene->mlx->ptr, scene->mlx->win, scene->mlx->img, 0, 0);
}




int main(int ac, char **av) {
    (void)ac;
    (void)av;

    // Initialisation de MLX et création de la fenêtre
    t_mlx *mlx = mlx_init_and_create_window(860, 600, "miniRT");
    if (!mlx)
        return (1);

    t_sphere sp = {
        .center = {0, 0, 20, 1.0},
        .diameter = 20,
        .color = {255, 0, 0},
        .transform = initMatriceIdentite()
    };

    t_scene2 scene = {
        .sphere = &sp,
        .mlx = mlx
    };
    
    redraw_scene(&scene); // Utiliser redraw_scene pour dessiner initialement
    mlx_hook(mlx->win, 17, 0L, close_window, &scene);
    mlx_hook(mlx->win, 2, 1L<<0, handle_key, &scene);
    mlx_loop(mlx->ptr);

    // // Libération des ressources à la fin
    // mlx_destroy_image(mlx->ptr, mlx->img);
    // mlx_destroy_window(mlx->ptr, mlx->win);
    // free(mlx);

    return (0);
}



/*
for y from 0 to height:
    for x from 0 to width:
        // Convertir (x, y) en coordonnées 3D sur le plan de projection
        Point3D pointSurPlan = convertirEn3D(x, y, d, caméra);
        Vecteur3D direction = normaliser(pointSurPlan - positionCaméra);
        
        // Vérifier l'intersection avec la sphère
        if (intersectionRayonSphère(positionCaméra, direction, sphère)):
            color = couleur de la sphère;
        else:
            color = couleur de fond;
        
        // Dessiner le pixel
        mlx_pixel_put(mlx, mlx_win, x, y, color);
*/