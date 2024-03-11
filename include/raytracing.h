/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:42:19 by alletond          #+#    #+#             */
/*   Updated: 2024/03/04 14:46:07 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
#define RAYTRACING_H

#include "../lib/GNL/get_next_line.h"
#include "../lib/libft/libft.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../lib/mlx/mlx.h"
#include "mlxinit.h"
#include "parse.h"
#include "object.h"


typedef struct s_ray {
    t_tuple origin;
    t_tuple direction;
} t_ray;

typedef struct {
    t_sphere *sphere;
    t_mlx *mlx;
    t_material material;
} t_scene2;


t_color lighting(t_material material, t_light light, t_tuple point, t_tuple eyev, t_tuple normalv);
t_tuple calculate_transformed_normal(t_ray *ray, t_sphere *sphere, double t, Matrice4x4 transformation_matrix);
t_tuple calculate_normal_at_point(t_sphere *sphere, t_ray *ray, double t);
t_scene check_and_fill(char **argv);
void print_scene(t_scene scene);
void redraw_scene(t_scene *scene);
t_tuple reflect(t_tuple incident, t_tuple normal);

// =========== COLOR ==========
t_color lighting(t_material material, t_light light, t_tuple point, t_tuple eyev, t_tuple normalv);
t_color color_add(t_color c1, t_color c2);
t_tuple reflect(t_tuple incident, t_tuple normal);
t_color calculate_ambient(t_color color, double ambient_intensity);
t_color calculate_diffuse(t_light light, t_tuple normal, t_tuple light_vect, double diffuse_intensity);
t_color calculate_specular(t_light light, t_tuple reflect_vect, t_tuple view_vect, double specular_intensity, double shininess);
t_color color_multiply(t_color c1, t_color c2);
t_color color_scale(t_color c, double factor);

#endif