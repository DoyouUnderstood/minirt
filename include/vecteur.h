#ifndef VECTEUR_H
#define VECTEUR_H

// #include "parse.h"

typedef struct s_tuple
{
    double x;
    double y;
    double z;
    double w;
} t_tuple;

double dot(t_tuple a, t_tuple b);
t_tuple point(double x, double y, double z);
t_tuple vector(double x, double y, double z);
t_tuple add_tuples(t_tuple a1, t_tuple a2);
double tuple_length(t_tuple a);
t_tuple subtract_tuples(t_tuple a1, t_tuple a2);
t_tuple negate_tuple(t_tuple a);
t_tuple multiply_tuple(t_tuple a, double scalar);
t_tuple normalize_tuple(t_tuple a);
t_tuple cross_product(t_tuple a, t_tuple b);
t_tuple subtract_vectors(t_tuple a, t_tuple b);

#endif