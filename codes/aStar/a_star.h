#ifndef A_STAR_H_   /* Include guard */
#define A_STAR_H_
#include "../sharedLibrary/adjacentList.h"
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int* alloc_array (int graph_size);
int **alloc_matrix (int graph_size);
t_graph_info a_star(t_graph** adjacent_list, t_coords *coords, int graph_size, int vertex_ini, int vertex_end);
t_l *remove_from_top (t_l *open_set, int *current);
t_l *insere_ordenado (t_l *open_set, t_o_set o);
float h_n (int vertex_id, int vertex_end, t_coords *coords);
t_graph_info add_vertex_to_closed_set(t_graph_info r, int vertex_id);

#endif
