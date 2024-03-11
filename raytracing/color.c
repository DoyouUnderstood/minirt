#include "../include/raytracing.h"
#include "../include/matrix.h"

typedef struct s_lighting_info
{
    t_color effective_color;
    t_tuple light_vect;
    double light_dot_normal;
    t_tuple reflect_vect;
    double reflect_dot_eye;
} t_lighting_info;

// Fonction de débogage
void debug_lighting(t_tuple point, t_tuple normalv, t_light light) {
    t_tuple light_vect = normalize_tuple(subtract_vectors(light.position, point));
    double light_dot_normal = dot(light_vect, normalv);

    printf("Debug Lighting Information:\n");
    printf("Point: (%f, %f, %f)\n", point.x, point.y, point.z);
    printf("Normal Vector: (%f, %f, %f)\n", normalv.x, normalv.y, normalv.z);
    printf("Light Position: (%f, %f, %f), Intensity: %f\n", 
           light.position.x, light.position.y, light.position.z, light.brightness);
    printf("Light Vector: (%f, %f, %f)\n", light_vect.x, light_vect.y, light_vect.z);
    printf("Dot Product (Light Vector • Normal Vector): %f\n", light_dot_normal);

    if (light_dot_normal < 0) {
        printf("Light is behind the object.\n");
    } else {
        printf("Light contributes to the illumination.\n");
    }
}

// Assurez-vous d'implémenter ou d'avoir les fonctions normalize_tuple, subtract_vectors, et dot disponibles
// Ces fonctions doivent effectuer les opérations mathématiques de base sur les tuples/vecteurs

void print_lighting_values(t_color color) 
{
    printf("Color: (R: %f, G: %f, B: %f)\n", color.r, color.g, color.b);
}

t_color lighting(t_material material, t_light light, t_tuple point, t_tuple eyev, t_tuple normalv) {

    t_lighting_info info;
    t_color ambient, diffuse, specular;

    info.effective_color = color_multiply(material.color, light.color);
    info.effective_color = color_scale(info.effective_color, light.brightness);
    info.light_vect = normalize_tuple(subtract_vectors(light.position, point));
    info.light_dot_normal = dot(info.light_vect, normalv);
    // debug_lighting(point, normalv, light);
    // printf("\tDot product of light vector and normal: %f\n", info.light_dot_normal);
    ambient = calculate_ambient(info.effective_color, material.ambient);
    if (info.light_dot_normal < 0) {
        // printf("\tLight is behind the object, returning ambient only.\n");
        return ambient; // The light is behind the object
    }
    diffuse = calculate_diffuse(light, info.light_vect, normalv, material.diffuse);
    info.reflect_vect = reflect(vect_scale(info.light_vect, -1), normalv);
    info.reflect_dot_eye = dot(info.reflect_vect, eyev);
    specular = calculate_specular(light, info.reflect_vect, eyev, material.specular, material.shininess);
    t_color final_color = color_add(color_add(ambient, diffuse), specular);
    return final_color;
}


t_color color_add(t_color c1, t_color c2)
{
    t_color result;

    result.r = c1.r + c2.r;
    result.g = c1.g + c2.g;
    result.b = c1.b + c2.b;

    // Clamper les valeurs pour s'assurer qu'elles restent dans l'intervalle [0, 255]
    result.r = result.r > 255 ? 255 : result.r;
    result.g = result.g > 255 ? 255 : result.g;
    result.b = result.b > 255 ? 255 : result.b;

    return result;
}

// Calcule le vecteur réfléchi à partir d'un vecteur incident et d'un vecteur normal
t_tuple reflect(t_tuple incident, t_tuple normal)
{
    double dot_product;
    t_tuple scaled_normal;
    t_tuple reflection;

    // Calcul du produit scalaire entre le vecteur incident et le vecteur normal
    dot_product = dot(incident, normal);

    // Multiplication du vecteur normal par 2 * produit scalaire
    scaled_normal = vect_scale(normal, 2 * dot_product);

    // Soustraction du vecteur normal scalé du vecteur incident pour obtenir le reflet
    reflection = subtract_tuples(incident, scaled_normal);

    return (reflection);
}


// Calcul de la composante ambiante de l'éclairage
t_color calculate_ambient(t_color color, double ambient_intensity)
{
    return (color_scale(color, ambient_intensity));
}

// Calcul de la composante diffuse de l'éclairage
t_color calculate_diffuse(t_light light, t_tuple normal, t_tuple light_vect, double diffuse_intensity)
{
    double  dot_nl;
    t_color result;

    dot_nl = dot(normal, light_vect);
    if (dot_nl > 0)
    {
        result = color_scale(light.color, light.brightness * diffuse_intensity * dot_nl);
        return (result);
    }
    return ((t_color){0, 0, 0});
}

// Calcul de la composante spéculaire de l'éclairage
t_color calculate_specular(t_light light, t_tuple reflect_vect, t_tuple view_vect, double specular_intensity, double shininess)
{
    double reflect_dot_view;
    t_color result;
    reflect_dot_view = dot(reflect_vect, view_vect);
    if (reflect_dot_view > 0)
    {
        double factor = pow(reflect_dot_view, shininess);
        result = color_scale(light.color, light.brightness * specular_intensity * factor);
        return (result);
    }
    return ((t_color){0, 0, 0}); // Retourne une couleur noire si le reflet n'est pas dans la direction de la vue
}


// Multiplication de deux couleurs, avec conversion préalable en [0, 1]
t_color color_multiply(t_color c1, t_color c2) {
    t_color result;
    result.r = (c1.r / 255.0) * (c2.r / 255.0) * 255; // Le résultat est remis à l'échelle [0, 255]
    result.g = (c1.g / 255.0) * (c2.g / 255.0) * 255;
    result.b = (c1.b / 255.0) * (c2.b / 255.0) * 255;
    return result;
}

// Échelonnement d'une couleur par un facteur, sans conversion nécessaire car le facteur n'est pas lié à l'échelle de couleur
t_color color_scale(t_color c, double factor) {
    t_color result;
    result.r = c.r * factor;
    result.g = c.g * factor;
    result.b = c.b * factor;
    // Assurez-vous de clamper les valeurs pour qu'elles restent dans l'intervalle [0, 255]
    result.r = result.r > 255 ? 255 : (result.r < 0 ? 0 : result.r);
    result.g = result.g > 255 ? 255 : (result.g < 0 ? 0 : result.g);
    result.b = result.b > 255 ? 255 : (result.b < 0 ? 0 : result.b);
    return result;
}

