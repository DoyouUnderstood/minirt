#ifndef PARSE_H
#define PARSE_H

#include "../lib/GNL/get_next_line.h"
#include "../lib/libft/libft.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../lib/mlx2/mlx.h"
#include <math.h>
#include "vecteur.h"
#include "object.h"
#include "mlxinit.h"
#include "dashboard.h"

typedef struct s_amb_light
{
	double			intensity;
	t_color			color;
}					t_amb_light;

typedef struct s_light
{
	t_tuple			position;
	double			brightness;
	t_color			color;
}					t_light;

typedef struct s_camera
{
	t_tuple			pos;
	t_tuple			orientation;
	double			fov;
}					t_camera;

typedef struct s_scene
{
	t_amb_light		amb_light;
	t_light			spot_light;
	t_camera		camera;
	t_obj_list		objects;
	t_mlx			*mlx;
	t_dashboard   	dashboard;
}					t_scene;

/* =========== Parseur ========== */

void				parse_cylinder(char **str, t_cyl *cyl);
void				parse_camera(char **line, t_camera *camera);
void				parse_plane(char **str, t_plane *plane);
void				parse_sphere(char **str, t_sphere *sphere);
void				parse_light(char **str, t_light *light);
void				parse_ambient_lightning(char **str, t_amb_light *light);
t_scene				parse(char **str);
void parse_object(char **ptr, t_obj_list *objects);

/* =========== Parseur utils ========== */

char *read_file_into_str(const char *str);
t_scene 			check_and_fill(char **argv);
void				error_exit(const char *error);
bool				in_range(double start, double end, double value);
double				ft_strtod(char *s);
bool				valid_bright(double bright);
int					ft_atod(const char *str, double *nbr);
void				ft_free_split(char **array);
int					parse_vec3(char *str, t_tuple *vec);
int					validate_orientation(const t_tuple *orientation);
double				parse_fov(char *str);
char				**ft_split(char const *s, char c);
double				ft_pow(double base, int exp);
void				rgb(char *str, t_color *color);
char				*advance_to_next_component(char **str);

/* =========== FREE ========== */

void				free_split(char **parts);
void				free_scene(t_scene *scene);

/* =========== Print ============ */

void				print_scene(t_scene scene);
void				ft_print_double_array(char **arr);
void 				print_object(t_object *obj);

#endif