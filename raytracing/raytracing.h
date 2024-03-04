/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:42:19 by alletond          #+#    #+#             */
/*   Updated: 2024/02/15 17:24:19 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACING_H
# define RAY_TRACING_H

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
#include "../include/mlxinit.h"


typedef struct s_ray {
    t_tuple origin;
    t_tuple direction;
} t_ray;

typedef struct {
    t_sphere *sphere;
    t_mlx *mlx;
} t_scene2;

t_scene check_and_fill(char **argv);
void print_scene(t_scene scene);
void redraw_scene(t_scene2 *scene);

#endif