#include <stdio.h>
#include <math.h>

// Structure pour représenter un vecteur 3D
typedef struct {
    float x;
    float y;
    float z;
} Vector3;

// Structure pour représenter une sphère
typedef struct {
    Vector3 center;
    float radius;
} Sphere;

// Fonction pour calculer la normale d'une sphère à un point donné
Vector3 normal_at(Sphere sphere, Vector3 point) {
    // La normale est simplement la différence entre le point donné et le centre de la sphère
    Vector3 normal;
    normal.x = point.x - sphere.center.x;
    normal.y = point.y - sphere.center.y;
    normal.z = point.z - sphere.center.z;

    // Normalisation du vecteur
    float length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    normal.x /= length;
    normal.y /= length;
    normal.z /= length;

    return normal;
}

int main() {
    // Définition d'une sphère
    Sphere s = {{0, 0, 0}, 1};

    // Tests de la fonction normal_at pour les scénarios donnés
    Vector3 n;

    n = normal_at(s, (Vector3){1, 0, 0});
    printf("Normale pour un point sur l'axe des x: (%f, %f, %f)\n", n.x, n.y, n.z);

    n = normal_at(s, (Vector3){0, 1, 0});
    printf("Normale pour un point sur l'axe des y: (%f, %f, %f)\n", n.x, n.y, n.z);

    n = normal_at(s, (Vector3){0, 0, 1});
    printf("Normale pour un point sur l'axe des z: (%f, %f, %f)\n", n.x, n.y, n.z);

    n = normal_at(s, (Vector3){sqrt(3.0)/3, sqrt(3.0)/3, sqrt(3.0)/3});
    printf("Normale pour un point non axial: (%f, %f, %f)\n", n.x, n.y, n.z);

    return 0;
}


/*


Résumé les étapes essentielles pour recalculer la normale à un point d'intersection entre un vecteur (rayon)
et une sphère, surtout en tenant compte des transformations appliquées à l'objet

Pour recalculer la normale a un point d'intersection entre un vecteur et une sphere,
c'est simple(mais comment faire ?)
Le plus dur reside dans le fait de calculer la nornmale lors de d'une transformation d'un object.
Il faut d'abord convertir le point d'intersection rayon sphere qui est en espace monde en epsace object
(espace monde = cadre de reference global de la scene) // (espace object = cadre de reference local d'un object)
pour cela il faut multiplier le point par l'inverse de la matrice de la transformation applique a l'object
une fois le point convertit, la normale est calcule comme si l'object n'a subit aucune transformation.
pour une sphere on doit soustraire le centre de la sphere du point de surface pour obtenir le vecteru normale ce vecteur et ensuite normalise
Ensuite il faut reconvertir la normale en espace monde cela implique de multiplier la normale par la matrice de transposition inverse de la matrice originale

*/