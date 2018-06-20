#ifndef ADJACENTLIST_H_   /* Include guard */
#define ADJACENTLIST_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#define new_node (t_graph*)malloc(sizeof(t_graph))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

extern char graph_folder[60];
extern char coord_folder[60];
extern char visited_coordinates_folder[60];
extern char path_coordinates_folder[60];
extern char data_structure_type[3];

struct type_graph{
    int vertex;
    int cost;
    struct type_graph *prox;
};

struct type_path{
    int src;
    int dest;
};

struct t_open_set{
    int vertex_id;
    int cost;
    float f_score;
};

typedef struct t_open_set t_o_set;

struct t_lista{
    t_o_set node;
    struct t_lista *prox;
};

typedef struct t_lista t_l;

typedef struct{
    int *distancia;
    int *anterior;
    int *closed_set;
    int *open_set;
    int *fechado;
    int path_g_n;
    int closed_set_size;
    int open_set_size;
}t_graph_info;

typedef struct{
    char v;
    int vertex;
    int x;
    int y;
}t_coords;

typedef struct type_graph t_graph;
typedef struct type_path t_path;

int get_graph_size(FILE *f, char **argv);
t_graph **get_adjacent_list(t_graph ** adjacent_list, int graph_size, FILE *f, char **argv);
t_graph** add_to_list_undir(t_graph **adjacent_list, int u, int v, int w);
void readParameters (int argc, char **argv);
void show_time_spent (double time_spent);

#endif // ADJACENTLIST_H_
