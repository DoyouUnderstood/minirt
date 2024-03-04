#include "../include/parse.h"

void parse_cylinder(char **parts, t_cyl *cyl) 
{
    if (!parse_vec3(parts[1], &cyl->center))
        error_exit("error with parsing\n");
    if (!parse_vec3(parts[2], &cyl->orientation))
        error_exit("error with parsing\n");
    if (!ft_atod(parts[3], &cyl->diameter))
        error_exit("error with parsing\n");
    if (!ft_atod(parts[4], &cyl->height))
        error_exit("error with parsing\n");
    rgb(parts[5], &cyl->color);
}

void parse_camera(char **parts, t_camera *camera)
{

    double fov;
    t_tuple orientation;
    if (!parse_vec3(parts[1], &camera->pos))
        error_exit("error with parsing\n");
    if (!parse_vec3(parts[2], &orientation))
       error_exit("error with parsing\n");
    else
        camera->orientation = orientation;
    if (!ft_atod(parts[3], &fov))
        error_exit("error with parsing\n");
    if (!in_range(0, 70, fov))
        error_exit("error with parsing\n");
    else
        camera->fov = fov;
}

int parse_point(char *str, t_tuple *vec) 
{
    int count = 0;
    char *next;

    vec->x = ft_strtod(str);
    next = advance_to_next_component(&str);
    if (!next) 
        return (0);
    count++;
    vec->y = ft_strtod(str);
    next = advance_to_next_component(&str);
    if (!next) 
        return (0);
    count++;
    vec->z = ft_strtod(str);
    count++;
    vec->w = 1;
    return (count == 3);
}

int parse_vec3(char *str, t_tuple *vec) 
{
    int count = 0;
    char *next;

    vec->x = ft_strtod(str);
    next = advance_to_next_component(&str);
    if (!next) 
        return (0);
    count++;
    vec->y = ft_strtod(str);
    next = advance_to_next_component(&str);
    if (!next) 
        return (0);
    count++;
    vec->z = ft_strtod(str);
    count++;
    vec->w = 0;
    return (count == 3);
}

void parse_plane(char **parts, t_plane *plane)
{
    if (!parse_vec3(parts[1], &plane->center) ||
        !parse_vec3(parts[2], &plane->orientation)) {
        error_exit("error with parsing\n");
    } else {
        rgb(parts[3], &plane->color);
    }
}


void parse_sphere(char **parts, t_sphere *sphere)
{
    if (!parse_vec3(parts[1], &sphere->center))
        error_exit("error with parsing\n");
    if (!ft_atod(parts[2], &sphere->diameter))
        error_exit("error with parsing\n");
    rgb(parts[3], &sphere->color);
}

void parse_light(char **parts, t_light *light)
{
    if (!parse_vec3(parts[1], &light->position))
        error_exit("error with parsing\n");
    if (!ft_atod(parts[2], &light->brightness))
        error_exit("error with parsing\n");
    if (!valid_bright(light->brightness))
        error_exit("error with parsing\n");
    rgb(parts[3], &light->color);
}
