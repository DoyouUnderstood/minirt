#include "criterion/criterion.h"

// #include "../include/object.h"
// #include "../include/parse.h"
// #include "../include/vecteur.h"
#include "../include/light.h"

// Fonction pour créer une nouvelle lumière ponctuelle
t_light *create_light(t_tuple position, t_color color, double brightness) {
    t_light *new_light = (t_light *)malloc(sizeof(t_light));
    if (!new_light) {
        return NULL;
    }

    new_light->position = position;
    new_light->color = color;
    new_light->brightness = brightness;

    return new_light;
}


// Fonction pour créer un matériau avec des valeurs par défaut
t_material material() 
{
    t_material m;

    m.color.r = 255.0; // Rouge intense
    m.color.g = 20.0;  // Vert plus faible
    m.color.b = 255.0; // Bleu intense

    // Ces valeurs doivent être entre 0 et 1 pour représenter une fraction de la lumière réfléchie
    m.ambient = 0.2;
    m.diffuse = 0.2;
    m.specular = 0.2;
    m.shininess = 200.0;

    return m;
}


#include <criterion/criterion.h>

// Test de la création d'une lumière ponctuelle et de son utilisation dans la fonction d'éclairage
Test(matériaux, Eclairer_avec_oeil_entre_lumiere_et_surface) {
    // Configuration partagée
    t_material m = material();
    t_tuple position = (t_tuple){0, 0, 0, 1}; // Position de la surface éclairée

    // Configuration spécifique au scénario
    t_tuple eyev = (t_tuple){0, 0, -1, 0}; // Direction de l'œil
    t_tuple normalv = (t_tuple){0, 0, -1, 0}; // Vecteur normal de la surface
    //t_color light_color = (t_color){1, 1, 1}; // Couleur de la lumière (blanc, pleine intensité)
    //double brightness = 1.0; // Luminosité de la lumière
    //t_light *light = create_light((t_tuple){0, 0, -10, 1}, light_color, brightness); // Création de la lumière ponctuelle

    t_light light;
    light.position = (t_tuple){0, 0, -10, 0};
    light.brightness = 1.0;
    light.color = (t_color){1, 1, 1};

    // Appel de la fonction d'éclairage
    t_color result = lighting(m, light, position, eyev, normalv);

    // Vérification que le résultat est comme attendu
    // Note : Assurez-vous que la fonction `lighting` retourne une couleur où chaque composante est ajustée par la luminosité de la lumière.
    t_color expected = (t_color){1.9, 1.9, 1.9}; // Couleur attendue résultant de l'éclairage
    cr_expect_float_eq(result.r, expected.r, 0.0001, "La composante Rouge de l'éclairage est incorrecte.");
    cr_expect_float_eq(result.g, expected.g, 0.0001, "La composante Vert de l'éclairage est incorrecte.");
    cr_expect_float_eq(result.b, expected.b, 0.0001, "La composante Bleu de l'éclairage est incorrecte.");

    //free(light); // N'oubliez pas de libérer la lumière à la fin du test pour éviter les fuites de mémoire.
}
 Test(lighting_tests, eclairage_avec_oeil_entre_lumiere_et_surface) {
    t_tuple eyev = vector(0, 0, -1);
    t_tuple normalv = vector(0, 0, -1);
    t_light light;
    light.position = (t_tuple){0, 0, -10, 1};
    light.brightness = 1.0;
    light.color = (t_color){1, 1, 1};
    t_material m = material();

    t_color result = lighting(m, light, vector(0, 0, 0), eyev, normalv);
    cr_expect_float_eq(result.r, 1.9, 0.001);
    cr_expect_float_eq(result.g, 1.9, 0.001);
    cr_expect_float_eq(result.b, 1.9, 0.001);
}

// Test 2: Éclairage avec l'œil entre lumière et surface, œil décalé de 45°
Test(lighting_tests, eclairage_avec_oeil_decale_45) {
    t_tuple eyev = vector(0, sqrt(2)/2, -sqrt(2)/2);
    t_tuple normalv = vector(0, 0, -1);
    t_light light;
    light.position = (t_tuple){0, 0, -10, 1};
    light.brightness = 1.0;
    light.color = (t_color){1, 1, 1};
    t_material m = material();

    t_color result = lighting(m, light, vector(0, 0, 0), eyev, normalv);
    cr_expect_float_eq(result.r, 1.0, 0.001);
    cr_expect_float_eq(result.g, 1.0, 0.001);
    cr_expect_float_eq(result.b, 1.0, 0.001);
}

// Test 3: Éclairage avec œil face à la surface, lumière décalée de 45°
Test(lighting_tests, eclairage_avec_lumiere_decalee_45) {
    t_tuple eyev = vector(0, 0, -1);
    t_tuple normalv = vector(0, 0, -1);
     t_light light;
    light.position = (t_tuple){0, 10, -10, 1};
    light.brightness = 1.0;
    light.color = (t_color){1, 1, 1};
    t_material m = material();

    t_color result = lighting(m, light, vector(0, 0, 0), eyev, normalv);
    cr_expect_float_eq(result.r, 0.7364, 0.001);
    cr_expect_float_eq(result.g, 0.7364, 0.001);
    cr_expect_float_eq(result.b, 0.7364, 0.001);
}

// Test 4: Éclairage avec l'œil dans le trajet du vecteur réflexion
Test(lighting_tests, eclairage_avec_oeil_dans_vecteur_reflexion) {
    t_tuple eyev = vector(0, -sqrt(2)/2, -sqrt(2)/2);
    t_tuple normalv = vector(0, 0, -1);
     t_light light;
    light.position = (t_tuple){0, 10, -10, 1};
    light.brightness = 1.0;
    light.color = (t_color){1, 1, 1};
    t_material m = material();

    t_color result = lighting(m, light, vector(0, 0, 0), eyev, normalv);
    cr_expect_float_eq(result.r, 1.6364, 0.001);
    cr_expect_float_eq(result.g, 1.6364, 0.001);
    cr_expect_float_eq(result.b, 1.6364, 0.001);
}
