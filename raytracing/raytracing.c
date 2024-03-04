/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:40:30 by alletond          #+#    #+#             */
/*   Updated: 2024/03/04 14:49:12 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raytracing.h"
#include "../include/matrix.h"


// cet fonction retourne un pointeur vers l'object trouvé
void* find_first_object_of_type(t_obj_list *obj_list, t_obj_type type) {
    t_object *current = obj_list->head;
    while (current != NULL) {
        if (current->type == type) {
            return current->obj;
        }
        current = current->next;
    }
    return NULL;
}


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

t_ray transform_ray(Matrice4x4 mat, t_ray ray) {
    t_ray transformed_ray;
    transformed_ray.origin = multiplyMatrixByTuple(mat, ray.origin); // Transforme l'origine
    transformed_ray.direction = multiplyMatrixByTuple(mat, ray.direction); // Transforme la direction

    return transformed_ray;
}

void throw_ray(t_sphere *sphere, t_mlx *mlx) 
{
    int width = mlx->width;
    int height = mlx->height;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            t_tuple origin = point(0, 0, 0);
            t_tuple direction = normalize_tuple(vector(x - width / 2, y - height / 2, 100));
            t_ray ray = {origin, direction};

            double t = 0;
            t_ray transformed_ray = transform_ray(sphere->transform, ray);
            if (intersect_ray_sphere(&transformed_ray, sphere, &t)) {
                put_pixel_to_img(mlx, x, y, 0xFF0000);
            } else {
                put_pixel_to_img(mlx, x, y, 0x000000);
            }
        }
    }
}

void redraw_scene(t_scene2 *scene) {
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

    throw_ray(scene->sphere, scene->mlx);
    mlx_put_image_to_window(scene->mlx->ptr, scene->mlx->win, scene->mlx->img, 0, 0);
}

int main(int ac, char **av) {
    (void)ac;
    (void)av;

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
    
    redraw_scene(&scene);
    mlx_hook(mlx->win, 17, 0L, close_window, &scene);
    mlx_hook(mlx->win, 2, 1L<<0, handle_key, &scene);
    mlx_loop(mlx->ptr);

    // // Libération des ressources à la fin
    // mlx_destroy_image(mlx->ptr, mlx->img);
    // mlx_destroy_window(mlx->ptr, mlx->win);
    // free(mlx);

    return (0);
}