#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/matrix.h"

double calculateDeterminant2x2(double Matrice4x4[2][2]) {
    return Matrice4x4[0][0] * Matrice4x4[1][1] - Matrice4x4[0][1] * Matrice4x4[1][0];
}


// //fonction pour faire des subMatrice4x4

// Matrice4x4 createSubMatrice4x4(Matrice4x4 original, int excludeRow, int excludeCol) 
// {
//     Matrice4x4 sub;
//     sub.rows = original.rows - 1;
//     sub.cols = original.cols - 1;
//     sub.data = malloc(sub.rows * sizeof(double*));

//     for (int i = 0; i < sub.rows; ++i) {
//         sub.data[i] = malloc(sub.cols * sizeof(double));
//     }
//     for (int i = 0, row = 0; i < original.rows; ++i) {
//         if (i == excludeRow) 
//             continue;

//         for (int j = 0, col = 0; j < original.cols; ++j) {
//             if (j == excludeCol) 
//                 continue;
//             sub.data[row][col] = original.data[i][j];
//             ++col;
//         }
//         ++row;
//     }
//     return (sub);
// }


double calculate_minor(Matrice4x4 mat, int row, int col) {
    double minor[3][3];
    for (int i = 0, mi = 0; i < 4; ++i) {
        if (i == row) continue;
        for (int j = 0, mj = 0; j < 4; ++j) {
            if (j == col) continue;
            minor[mi][mj] = mat.m[i][j];
            mj++;
        }
        mi++;
    }
    // Calcul du déterminant du mineur 3x3
    double det = minor[0][0] * (minor[1][1] * minor[2][2] - minor[2][1] * minor[1][2])
               - minor[0][1] * (minor[1][0] * minor[2][2] - minor[1][2] * minor[2][0])
               + minor[0][2] * (minor[1][0] * minor[2][1] - minor[1][1] * minor[2][0]);
    return det;
}

Matrice4x4 calculate_cofactor_Matrice4x4(Matrice4x4 mat) {
    Matrice4x4 cofactor;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            double sign = (i + j) % 2 == 0 ? 1.0 : -1.0;
            cofactor.m[i][j] = sign * calculate_minor(mat, i, j);
        }
    }
    return cofactor;
}


// calcul le determinant d'une Matrice4x4 3x3
double determinant3x3(double matrix[3][3]) {
    // Calcul direct du déterminant d'une matrice 3x3
    double det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
                 matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
                 matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    return det;
}


void getSubMatrice4x4(Matrice4x4 mat, double subMatrice4x4[3][3], int excluding_row, int excluding_col) {
    int di = 0;
    for (int i = 0; i < 4; ++i) {
        if (i == excluding_row) 
            continue;
        int dj = 0;
        for (int j = 0; j < 4; ++j) {
            if (j == excluding_col) 
                continue;
            subMatrice4x4[di][dj] = mat.m[i][j];
            dj++;
        }
        di++;
    }
}

double determinant4x4(Matrice4x4 mat) {
    double det = 0.0;
    for (int col = 0; col < 4; col++) {
        double subMatrice4x4[3][3];
        getSubMatrice4x4(mat, subMatrice4x4, 0, col);
        double minor = determinant3x3(subMatrice4x4);
        double cofactor = (col % 2 == 0 ? 1 : -1) * minor;
        det += mat.m[0][col] * cofactor;
    }
    return det;
}

// int main() {
//     double Matrice4x44x4[4][4] = {
//         {-2, -8, 3, 5},
//         {-3, 1, 7, 3},
//         {1, 2, -9, 6},
//         {-6, 7, 7, -9}
//     };
//     double subMatrice4x4[3][3];
//     getSubMatrice4x4(Matrice4x44x4, subMatrice4x4, 1, 1); // Exemple d'extraction de sous-matrice
//     double det = determinant3x3(subMatrice4x4); // Calcul du déterminant de la sous-matrice
//     printf("Le déterminant de la sous-matrice est: %f\n", det);
//     return 0;
// }


