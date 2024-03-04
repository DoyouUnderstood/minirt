/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecteur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:48:04 by alletond          #+#    #+#             */
/*   Updated: 2024/02/23 15:41:47 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vecteur.h"
#include <math.h>

t_tuple point(double x, double y, double z) {
    return (t_tuple){x, y, z, 1.0};
}

double dot(t_tuple a, t_tuple b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}


// Fonction pour créer un vecteur
t_tuple vector(double x, double y, double z) {
    return (t_tuple){x, y, z, 0.0};
}

t_tuple add_tuples(t_tuple a1, t_tuple a2) {
    t_tuple result;
    result.x = a1.x + a2.x;
    result.y = a1.y + a2.y;
    result.z = a1.z + a2.z;
    result.w = 1.0;
    return result;
}


double tuple_length(t_tuple a)
{
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

t_tuple subtract_tuples(t_tuple a1, t_tuple a2)
{
    t_tuple result;

    result.x = a1.x - a2.x;
    result.y = a1.y - a2.y;
    result.z = a1.z - a2.z;
    result.w = a1.w - a2.w; // La soustraction de w dépend de la nature des tuples

    return result;
}

// Implémentation de la fonction subtract_vectors
t_tuple subtract_vectors(t_tuple a, t_tuple b) {
    t_tuple result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w; // Gère la composante w, distinction entre points et vecteurs
    return result;
}



t_tuple negate_tuple(t_tuple a)
{
    t_tuple result;

    result.x = -a.x;
    result.y = -a.y;
    result.z = -a.z;
    result.w = a.w; // Habituellement, la négation ne change pas w

    return result;
}

t_tuple multiply_tuple(t_tuple a, double scalar)
{
    t_tuple result;

    result.x = a.x * scalar;
    result.y = a.y * scalar;
    result.z = a.z * scalar;
    result.w = a.w * scalar; // La multiplication de w ajuste la "magnitude" du tuple

    return result;
}

t_tuple normalize_tuple(t_tuple a)
{
    t_tuple result;
    double length = tuple_length(a);
    if (length == 0)
    {
        result.x = result.y = result.z = result.w = 0;
        return result;
    }
    result.x = a.x / length;
    result.y = a.y / length;
    result.z = a.z / length;
    result.w = a.w;
    return (result);
}

// produit scalaire entre 2 vecteurs.
double dot_product(t_tuple a, t_tuple b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_tuple cross_product(t_tuple a, t_tuple b)
{
    t_tuple result;

    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    result.w = 0;

    return result;
}

// int main()
// {
//     t_tuple a1 = {3, -2, 5, 1}; // Exemple de tuple
//     t_tuple a2 = {1, 3, -2, 0}; // Un autre tuple pour la soustraction

//     t_tuple subtracted = subtract_tuples(a1, a2);
//     printf("Soustraction : (%f, %f, %f, %f)\n", subtracted.x, subtracted.y, subtracted.z, subtracted.w);

//     t_tuple negated = negate_tuple(a1);
//     printf("Négation : (%f, %f, %f, %f)\n", negated.x, negated.y, negated.z, negated.w);

//     t_tuple multiplied = multiply_tuple(a1, 2);
//     printf("Multiplication par un scalaire : (%f, %f, %f, %f)\n", multiplied.x, multiplied.y, multiplied.z, multiplied.w);

//     return 0;
// }

