#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/parse.h"
#include "../include/light.h"
#include "../include/raytracing.h"
#include "../include/ray.h"

typedef struct s_world
{
    t_light *light;
    t_object *object;
    int num_objects;
}   t_world;


t_sphere *create_sphere_default(t_color color, float diffuse, float specular) 
{
    t_sphere *sphere = malloc(sizeof(t_sphere));
    sphere->material.color = color;
    sphere->material.diffuse = diffuse;
    sphere->material.specular = specular;
    return (sphere);
}

t_world *create_default_world() {
    t_world *world = malloc(sizeof(t_world));
    if (!world) 
        return (NULL);

    t_light *light = malloc(sizeof(t_light));
    if (!light) 
    {
        free(world);
        return (NULL);
    }
    light->position = (t_tuple){-10, 10, -10, 0};
    light->color = (t_color){1, 1, 1};
    world->light = light;

    world->object = malloc(sizeof(t_object));
    if (!world->object) 
    {
        free(light);
        free(world);
        return (NULL);
    }
    world->object->next = malloc(sizeof(t_object));
    if (!world->object->next) 
    {
        free(world->object);
        free(light);
        free(world);
        return (NULL);
    }

    world->object->obj = create_sphere_default((t_color){0.8, 1.0, 0.6}, 0.7, 0.2);
    world->object->next->obj = create_sphere_default((t_color){0.8, 1.0, 0.6}, 0.7, 0.2);
    world->object->next->next = NULL;
    world->num_objects = 2;
    return (world);
}

t_intersections intersect_world(t_world *world, t_ray ray) 
{
    t_intersections world_intersections = initialize_intersections();
    t_intersections sphere_intersections;
    t_object *current_object = world->object;
    while (current_object != NULL) 
    {
        t_sphere *sphere = (t_sphere *)current_object->obj;
        sphere_intersections = intersect_sphere(*sphere, ray);
        for (int i = 0; i < sphere_intersections.count; i++) 
        {
            world_intersections.intersections = realloc(world_intersections.intersections, sizeof(t_intersection) * (world_intersections.count + 1));
            world_intersections.intersections[world_intersections.count] = sphere_intersections.intersections[i];
            world_intersections.count++;
        }
        current_object = current_object->next;
    }
    sort_intersections(&world_intersections);
    return (world_intersections);
}




#include <stdio.h>

int main() 
{
    t_world *world = create_default_world();
    t_ray ray;
    ray.origin = (t_tuple){0, 0, -5, 1};
    ray.direction = (t_tuple){0, 0, 1, 1};
    t_intersections intersections = intersect_world(world, ray);
    printf("Nombre d'intersections trouvées: %d\n", intersections.count);
    for (int i = 0; i < intersections.count; i++) {
        printf("Intersection %d: t = %f\n", i + 1, intersections.intersections[i].t);
    }
    if (intersections.intersections != NULL) {
        free(intersections.intersections);
    }    
    return 0;
}



// t_intersections intersect_world(t_world *world, t_ray *ray) 
// {
//     t_intersections intersections = initialize_intersections();
//     if (world->object != NULL) {
//         intersect_sphere_with_ray(world->object, ray, &intersections);
//     }
//     if (world->object->next != NULL) {
//         intersect_sphere_with_ray(world->object->next, ray, &intersections);
//     }
//     sort_intersections(&intersections);
//     return intersections;
// }

// void throw_ray(t_scene *scene) 
// {
//     for (int y = 0; y < scene->mlx->height; ++y) 
//     {
//         for (int x = 0; x < scene->mlx->width; ++x) 
//         {
//             t_ray ray = 
//             {
//                 .origin = point(0, 0, 0),
//                 .direction = normalize_tuple(vector(x - scene->mlx->width / 2, y - scene->mlx->height / 2, -scene->camera->focal_length))
//             };

//             t_intersections intersections = intersect_world(scene->world, ray);

//             if (intersections.count > 0) {
//                 // Supposez que vous avez une fonction pour trouver l'intersection la plus proche
//                 t_intersection closest_intersection = find_closest_intersection(intersections);

//                 // Ici, vous calculeriez la couleur en fonction de l'intersection la plus proche
//                 t_sphere *sphere = (t_sphere *)closest_intersection.object; // Cela suppose que l'objet est une sphère
//                 t_tuple point = position(ray, closest_intersection.t);
//                 t_tuple normal = calculate_normal_at_point(sphere, &ray, closest_intersection.t);
//                 t_tuple eye = negate_tuple(ray.direction);
//                 t_color color = lighting(sphere->material, scene->spot_light, point, eye, normal, scene->ambient_light);
//                 put_pixel_to_img(scene->mlx, x, y, color_to_hex(color));
//             } else {
//                 put_pixel_to_img(scene->mlx, x, y, 0x000033); // Aucune intersection : couleur de fond
//             }

//             // Libération de la mémoire des intersections si nécessaire
//             free_intersections(&intersections);
//         }
//     }
// }