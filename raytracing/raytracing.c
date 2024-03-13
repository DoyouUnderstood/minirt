/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:40:30 by alletond          #+#    #+#             */
/*   Updated: 2024/03/13 19:33:41 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raytracing.h"
#include "../include/matrix.h"
#include "../include/ray.h"
#include "../include/light.h"
#include "../include/dashboard.h"

bool intersect_ray_sphere(t_ray *ray, t_sphere *sphere, double *t) 
{
    t_tuple sphere_to_ray = subtract_tuples(ray->origin, sphere->center);
    double a = dot(ray->direction, ray->direction);
    double b = 2 * dot(ray->direction, sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - pow(sphere->diameter / 2, 2.0);
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;
    double t0 = (-b - sqrt(discriminant)) / (2 * a);
    double t1 = (-b + sqrt(discriminant)) / (2 * a);
    double t_near = fmin(t0, t1);
    if (t_near < 0) {
        t_near = fmax(t0, t1);
    }
    if (t_near < 0) {
        return false;
    }

    *t = t_near;
    return true;
}

t_ray transform_ray(Matrice4x4 mat, t_ray ray) {
    t_ray transformed_ray;
    transformed_ray.origin = multiplyMatrixByTuple(mat, ray.origin); // Transforme l'origine
    transformed_ray.direction = multiplyMatrixByTuple(mat, ray.direction); // Transforme la direction

    return transformed_ray;
}

uint32_t color_to_hex(t_color color) {
    int r = (int)color.r;
    int g = (int)color.g;
    int b = (int)color.b;
    return (r << 16) | (g << 8) | b;
}


void throw_ray(t_scene *scene) {
    t_sphere *sphere = (t_sphere*)scene->objects.head->obj; // Ajustez selon votre structure de données
    t_light light = scene->spot_light; // Utilisez la lumière spot de la scène

    int width = scene->mlx->width;
    int height = scene->mlx->height;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            t_tuple origin = point(0, 0, 0);
            t_tuple direction = normalize_tuple(vector(x - width / 2, y - height / 2, 100));
            t_ray ray = {origin, direction};
            double t = 0;
            if (intersect_ray_sphere(&ray, sphere, &t)) 
            {
                t_tuple point = position(ray, t); // 
                t_tuple normal = calculate_normal_at_point(sphere, &ray, t); //Utilise le rayon et t pour calculer la normale
                t_tuple eye = negate_tuple(ray.direction);
                t_color color = lighting(sphere->material, light, point, eye, normal);
                //printf("color = %f, %f, %f\n", color.r, color.g, color.b);
                uint32_t color_int = color_to_hex(color);
                //printf("color int = %d\n", color_int);
                put_pixel_to_img(scene->mlx, x, y, color_int);
            } else {
                put_pixel_to_img(scene->mlx, x, y, 0x000033);
            }
        }
    }
}

// void throw_ray(t_scene *scene) {
//     t_light light = scene->spot_light; // Supposition pour l'accès à la lumière spot
//     for (int y = 0; y < scene->mlx->height; ++y) {
//         for (int x = 0; x < scene->mlx->width; ++x) {
//             t_ray ray = {
//                 .origin = point(0, 0, 0), // Initialisation du point d'origine du rayon
//                 .direction = normalize_tuple(vector(x - scene->mlx->width / 2, y - scene->mlx->height / 2, -scene->camera.fov)) // Ajustement pour focal length
//             };

//             t_sphere *closest_sphere = NULL;
//             double closest_t = INFINITY;
//             for (t_object *node = scene->objects.head; node != NULL; node = node->next) {
//                 t_sphere *sphere = (t_sphere*)node->obj;
//                 t_intersections intersections = intersect_sphere(*sphere, ray);
//                 for (int i = 0; i < intersections.count; i++) {
//                     double t = intersections.intersections[i].t;
//                     if (t > 0 && t < closest_t) {
//                         closest_t = t;
//                         closest_sphere = sphere;
//                     }
//                 }
//                 if (intersections.intersections != NULL) {
//                     free(intersections.intersections);
//                 }
//             }

//             if (closest_sphere != NULL) {
//                 t_tuple point = position(ray, closest_t);
//                 t_tuple normal = calculate_normal_at_point(closest_sphere, &ray, closest_t);
//                 t_tuple eye = negate_tuple(ray.direction);
//                 t_color color = lighting(closest_sphere->material, light, point, eye, normal);
//                 uint32_t color_int = color_to_hex(color);
//                 put_pixel_to_img(scene->mlx, x, y, color_int);
//             } else {
//                 put_pixel_to_img(scene->mlx, x, y, 0x000033); // Couleur de fond si pas d'intersection
//             }
//         }
//     }
// }





void redraw_scene(t_scene *scene) {
    if (scene == NULL || scene->mlx == NULL || scene->mlx->ptr == NULL) {
        write(1, "Invalid scene or MLX pointer.\n", 30);
        return;
    }
    if (scene->mlx->img != NULL) {
        mlx_destroy_image(scene->mlx->ptr, scene->mlx->img);
    }
    scene->mlx->img = mlx_new_image(scene->mlx->ptr, scene->mlx->width, scene->mlx->height);
    if (scene->mlx->img == NULL) {
        write(1, "Failed to create image.\n", 24);
        return;
    }
    scene->mlx->addr = mlx_get_data_addr(scene->mlx->img, &scene->mlx->bits_per_pixel,
                                         &scene->mlx->line_length, &scene->mlx->endian);
    throw_ray(scene);
    afficher_dashboard(scene);
    mlx_put_image_to_window(scene->mlx->ptr, scene->mlx->win, scene->mlx->img, 0, 0);
}


void process_spheres(t_obj_list *obj_list) 
{
    t_object *current = obj_list->head;

    while (current != NULL) {
        if (current->type == SPHERE) {
            t_sphere *sphere = (t_sphere *)current->obj;
            printf("Sphere at position (%f, %f, %f) with diameter %f\n",
                   sphere->center.x, sphere->center.y, sphere->center.z, sphere->diameter);
        }
        current = current->next;
    }
}


#define RUN_TESTS 0

#if RUN_TESTS
#include "../include/light.h"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/criterion.h>
#include <criterion/options.h>

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    struct criterion_test_set *tests = criterion_initialize();

    // Configurez les options de Criterion si nécessaire. Exemple :
    // criterion_options.always_succeed = true;

    int result = criterion_run_all_tests(tests);
    criterion_finalize(tests);

    return result;
}

#else

#include "../include/light.h"

t_mlx *init_main_scene(t_scene *scene) 
{
    t_object *object = malloc(sizeof(t_object)); // ou comme cela
    t_sphere *sphere = malloc(sizeof(t_sphere));
    t_mlx *mlx = mlx_init_and_create_window(860, 600, "miniRT");
    if (!mlx)
        exit(1);

    // Configuration de l'éclairage ambiant
    scene->amb_light.intensity = 1;
    scene->amb_light.color = (t_color){0, 0, 0};

    // Configuration de la source de lumière
    scene->spot_light.position = (t_tuple){-10, 10, -10, 0};
    scene->spot_light.brightness = 1;
    scene->spot_light.color = (t_color){255, 255, 255};

    // Configuration de la caméra
    scene->camera.pos = (t_tuple){0, 0, 20, 1};
    scene->camera.orientation = (t_tuple){0, 0, 255, 0};
    scene->camera.fov = 70;

    // Initialisation de la liste d'objets
    scene->objects.head = NULL;

    // Ajout d'une sphère
    sphere = malloc(sizeof(t_sphere));
    sphere->center = (t_tuple){0, 0, 20, 1};
    sphere->diameter = 30;
    sphere->color = (t_color){10, 50, 255};
    sphere->material = material();

    // Créer un objet de type SPHERE et l'ajouter à la liste
    object = malloc(sizeof(t_object));
    object->type = SPHERE;
    object->obj = sphere;
    object->next = scene->objects.head; // Ajout en tête de liste
    scene->objects.head = object;
    scene->mlx = mlx;
    redraw_scene(scene);
    return mlx;
}


// int main(void) {
//     t_scene scene;
//     scene.dashboard.material = malloc(sizeof(t_material));
//     *(scene.dashboard.material) = material(); // Assurez-vous que material() retourne une structure correctement initialisée
//     if (!init_main_scene(&scene)) {
//         return (EXIT_FAILURE);
//     }
//     afficher_dashboard(&scene);
//     mlx_hook(scene.mlx->win, 17, 0L, close_window, &scene);
//     mlx_hook(scene.mlx->win, 2, 1L<<0, handle_key, &scene);
//     mlx_loop(scene.mlx->ptr);
//     free(scene.dashboard.material);
//     return (EXIT_SUCCESS);
// }



#endif
/*

int main(int argc, char **argv)
{
    t_mlx *mlx;

    if (argc != 2) {
        printf("Usage: %s <scene->rt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    t_scene scene = check_and_fill(argv); // Supposant que check_and_fill retourne une scène remplie

    // Traitement des sphères dans la scène
    process_spheres(&scene->objects);

    // Initialiser miniLibX et créer une fenêtre.
    mlx = mlx_init_and_create_window(860, 600, "miniRT");
    if (!mlx)
        return (EXIT_FAILURE);
    
    // Assigner le pointeur mlx à votre scène si nécessaire.
    scene->mlx = mlx;

    // Redessiner la scène en utilisant les données remplies depuis le fichier .rt.
    redraw_scene(&scene);

    // Gestion des événements : fermeture de la fenêtre et touches.
    mlx_hook(mlx->win, 17, 0L, close_window, &scene); // Fermeture de la fenêtre.
    mlx_hook(mlx->win, 2, 1L<<0, handle_key, &scene); // Gestion des touches.

    // Démarrer la boucle d'événements de miniLibX.
    mlx_loop(mlx->ptr);
}

*/