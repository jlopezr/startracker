#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Definición de la estructura para una estrella
typedef struct {
    char name[50];
    double coords[3]; // Coordenadas (x, y, z) de la estrella
} Star;

// Calcula la distancia euclidiana entre dos estrellas
double distance(Star s1, Star s2) {
    return sqrt(pow(s1.coords[0] - s2.coords[0], 2) +
                pow(s1.coords[1] - s2.coords[1], 2) +
                pow(s1.coords[2] - s2.coords[2], 2));
}

// Función para buscar la estrella más cercana en el vector de estrellas
int findNearestStar(Star stars[], int n, Star target) {
    int best_index = -1;
    double best_dist = INFINITY;

    for (int i = 0; i < n; i++) {
        double d = distance(stars[i], target);
        if (d < best_dist) {
            best_dist = d;
            best_index = i;
        }
    }

    return best_index;
}

int main() {
    // Lista de estrellas (nombre y coordenadas)
    Star stars[] = {
        {"Alpha Centauri", {1.34, 2.67, -0.45}},
        {"Sirius", {8.6, -1.7, 3.4}},
        {"Betelgeuse", {6.5, -8.4, 4.1}},
        {"Proxima Centauri", {2.1, 3.5, -1.0}},
        {"Rigel", {7.8, 1.2, -3.4}}
    };

    int n = sizeof(stars) / sizeof(stars[0]);

    // Estrella objetivo a buscar
    Star target = {"Target", {7.0, -2.0, 3.0}};
    int nearest_index = findNearestStar(stars, n, target);

    if (nearest_index != -1) {
        Star nearest_star = stars[nearest_index];
        printf("Estrella más cercana a %s es %s\n", target.name, nearest_star.name);
        printf("Coordenadas: (%.2f, %.2f, %.2f)\n", 
               nearest_star.coords[0], 
               nearest_star.coords[1], 
               nearest_star.coords[2]);
    } else {
        printf("No se encontró una estrella cercana.\n");
    }

    return 0;
}