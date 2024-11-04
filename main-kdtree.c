#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NODES 100

// Definición de la estructura para una estrella
typedef struct {
    char name[50];
    double coords[3]; // Coordenadas (x, y, z) de la estrella
} Star;

// Definición del nodo del KD-Tree
typedef struct {
    Star star;
    int left;  // Índice del hijo izquierdo en el arreglo de nodos (-1 si no existe)
    int right; // Índice del hijo derecho en el arreglo de nodos (-1 si no existe)
} KDNode;

// Vector para los nodos del KD-Tree y contador de nodos
KDNode kd_nodes[MAX_NODES];
int kd_node_count = 0;

// Función para crear un nuevo nodo del KD-Tree
int createNode(Star star) {
    if (kd_node_count >= MAX_NODES) {
        printf("Error: Excedido el número máximo de nodos.\n");
        exit(1);
    }
    kd_nodes[kd_node_count].star = star;
    kd_nodes[kd_node_count].left = -1;
    kd_nodes[kd_node_count].right = -1;
    return kd_node_count++;
}

// Función para construir el KD-Tree
int buildKDTree(Star stars[], int start, int end, int depth) {
    if (start > end) return -1;

    int axis = depth % 3; // Alterna entre x, y, z
    int mid = (start + end) / 2;

    // Ordena las estrellas en función de la coordenada del eje actual (algoritmo de selección simple)
    for (int i = start; i <= end; i++) {
        int min_idx = i;
        for (int j = i + 1; j <= end; j++) {
            if (stars[j].coords[axis] < stars[min_idx].coords[axis]) {
                min_idx = j;
            }
        }
        // Intercambia stars[i] y stars[min_idx]
        Star temp = stars[i];
        stars[i] = stars[min_idx];
        stars[min_idx] = temp;
    }

    // Crea un nuevo nodo y construye los subárboles
    int node_index = createNode(stars[mid]);
    kd_nodes[node_index].left = buildKDTree(stars, start, mid - 1, depth + 1);
    kd_nodes[node_index].right = buildKDTree(stars, mid + 1, end, depth + 1);

    return node_index;
}

// Calcula la distancia euclidiana entre dos estrellas
double distance(Star s1, Star s2) {
    return sqrt(pow(s1.coords[0] - s2.coords[0], 2) +
                pow(s1.coords[1] - s2.coords[1], 2) +
                pow(s1.coords[2] - s2.coords[2], 2));
}

// Función para buscar la estrella más cercana en el KD-Tree
void nearestStar(int node_index, Star target, int *best_index, double *best_dist, int depth) {
    if (node_index == -1) return;

    KDNode node = kd_nodes[node_index];

    double d = distance(node.star, target);
    if (d < *best_dist) {
        *best_dist = d;
        *best_index = node_index;
    }

    int axis = depth % 3;
    int next_branch = -1;
    int opposite_branch = -1;

    if (target.coords[axis] < node.star.coords[axis]) {
        next_branch = node.left;
        opposite_branch = node.right;
    } else {
        next_branch = node.right;
        opposite_branch = node.left;
    }

    nearestStar(next_branch, target, best_index, best_dist, depth + 1);

    if (fabs(target.coords[axis] - node.star.coords[axis]) < *best_dist) {
        nearestStar(opposite_branch, target, best_index, best_dist, depth + 1);
    }
}

// Función principal para realizar una búsqueda de estrella
int findNearestStar(int root_index, Star target) {
    int best_index = -1;
    double best_dist = INFINITY;
    nearestStar(root_index, target, &best_index, &best_dist, 0);
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

    // Construcción del KD-Tree
    int root_index = buildKDTree(stars, 0, n - 1, 0);

    // Estrella objetivo a buscar
    Star target = {"Target", {7.0, -2.0, 3.0}};
    int nearest_index = findNearestStar(root_index, target);

    if (nearest_index != -1) {
        KDNode nearest_node = kd_nodes[nearest_index];
        printf("Estrella más cercana a %s es %s\n", target.name, nearest_node.star.name);
        printf("Coordenadas: (%.2f, %.2f, %.2f)\n", 
               nearest_node.star.coords[0], 
               nearest_node.star.coords[1], 
               nearest_node.star.coords[2]);
    } else {
        printf("No se encontró una estrella cercana.\n");
    }

    return 0;
}