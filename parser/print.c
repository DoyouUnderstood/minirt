#include "../include/parse.h"

#include <stdio.h>

void print_amb_light(t_amb_light amb) {
    printf("Ambient Light: Intensity = %f, Color = RGB(%f, %f, %f)\n", amb.intensity, amb.color.r, amb.color.g, amb.color.b);
}

void print_light(t_light light) {
    printf("Light: Position = (%f, %f, %f), Brightness = %f, Color = RGB(%f, %f, %f)\n", light.position.x, light.position.y, light.position.z, light.brightness, light.color.r, light.color.g, light.color.b);
}

void print_camera(t_camera cam) {
    printf("Camera: Position = (%f, %f, %f), Orientation = (%f, %f, %f), FOV = %f\n", cam.pos.x, cam.pos.y, cam.pos.z, cam.orientation.x, cam.orientation.y, cam.orientation.z, cam.fov);
}

void print_object(t_object *obj) {
    switch (obj->type) {
        case SPHERE: {
            t_sphere *sphere = (t_sphere *)obj->obj;
            printf("Sphere: Center = (%f, %f, %f), Diameter = %f, Color = RGB(%f, %f, %f)\n", sphere->center.x, sphere->center.y, sphere->center.z, sphere->diameter, sphere->color.r, sphere->color.g, sphere->color.b);
            break;
        }
        case PLANE: {
            t_plane *plane = (t_plane *)obj->obj;
            printf("Plane: Center = (%f, %f, %f), Orientation = (%f, %f, %f), Color = RGB(%f, %f, %f)\n", plane->center.x, plane->center.y, plane->center.z, plane->orientation.x, plane->orientation.y, plane->orientation.z, plane->color.r, plane->color.g, plane->color.b);
            break;
        }
        case CYLINDER: {
            t_cyl *cyl = (t_cyl *)obj->obj;
            printf("Cylinder: Center = (%f, %f, %f), Orientation = (%f, %f, %f), Diameter = %f, Height = %f, Color = RGB(%f, %f, %f)\n", cyl->center.x, cyl->center.y, cyl->center.z, cyl->orientation.x, cyl->orientation.y, cyl->orientation.z, cyl->diameter, cyl->height, cyl->color.r, cyl->color.g, cyl->color.b);
            break;
        }
        case INVALID_TYPE:
            break ;
    }
}

void    ft_print_double_array(char **arr)
{
   int i;

    if (!arr)
        return;
    i = 0;
    while (arr[i] != NULL)
    {
        printf("%s\n", arr[i]);
        i++;
    }
}

void print_scene(t_scene scene) 
{
    print_amb_light(scene.amb_light);
    printf("\n");
    print_light(scene.spot_light);
    printf("\n");
    print_camera(scene.camera);
    printf("\n");
    t_object *current = scene.objects.head;
    while (current != NULL) {
        print_object(current);
        printf("\n");
        current = current->next;
    }
}