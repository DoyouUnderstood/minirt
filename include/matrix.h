#ifndef MATRIX_H
#define MATRIX_H

#include "vecteur.h"
#include "math.h"
typedef struct 
{
    float m[4][4];
} Matrice4x4;


Matrice4x4 transposeMatrix(Matrice4x4 mat);
Matrice4x4 inverse_matrix(Matrice4x4 mat);
Matrice4x4 shearing_matrix(double xy, double xz, double yx, double yz, double zx, double zy);
Matrice4x4 rotation_z(double angle);
Matrice4x4 scaling_matrix(double sx, double sy, double sz);
Matrice4x4 initMatriceIdentite();
t_tuple multiplyMatrixByTuple(Matrice4x4 mat, t_tuple tup);
Matrice4x4 translation_matrix(double dx, double dy, double dz);
Matrice4x4 multiplyMatrices(Matrice4x4 Ma, Matrice4x4 Mb);
Matrice4x4 calculate_cofactor_matrix(Matrice4x4 mat);
double calculate_minor(Matrice4x4 mat, int row, int col);
double determinant4x4(Matrice4x4 mat);
Matrice4x4 calculate_cofactor_Matrice4x4(Matrice4x4 mat);
#endif