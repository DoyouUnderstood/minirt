#ifndef OBJECT_H
#define OBJECT_H

#include "parse.h"
#include "matrix.h"
#include "raytracing.h"

typedef struct s_color
{
	double r;
	double g;
	double b;
}					t_color;

typedef struct s_material
{
    t_color color;     
    double ambient;
    double diffuse;  
    double specular; 
    double shininess;
} t_material;


typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	INVALID_TYPE = -1,
}					t_obj_type;

 typedef struct s_object
{
	t_obj_type		type;
	void			*obj;
	struct s_object	*next;
}					t_object;

typedef struct s_obj_list
{
	t_object *head;
}					t_obj_list;

typedef struct s_plane
{
	t_tuple			center;
	t_tuple			orientation;
	t_color			color;
}					t_plane;

typedef struct s_sphere 
{
    t_tuple center;
    double diameter;
    t_color color;
    Matrice4x4 transform; // Ajout d'un champ pour la transformation
	t_material material;
} t_sphere;


typedef struct s_cyl
{
	t_tuple			center;
	t_tuple			orientation;
	double			diameter;
	double			height;
	t_color			color;
}					t_cyl;

#endif 