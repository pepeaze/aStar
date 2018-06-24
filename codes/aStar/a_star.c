#include "a_star.h"

int* alloc_array (int graph_size){
    int *a;
    a = (int*)calloc(graph_size,sizeof(int));
    return a;
}

float* alloc_array_float (int graph_size){
    float *a;
    a = (float*)calloc(graph_size,sizeof(float));
    return a;
}

int **alloc_matrix (int graph_size){
    int **m;
    int i;
    m = (int**)malloc(graph_size*sizeof(int*));
    for (i=0; i<graph_size; i++){
        m[i] = (int*)calloc(graph_size,sizeof(int));
    }
    return m;
}



t_graph_info add_vertex_to_closed_set(t_graph_info r, int vertex_id){
    r.closed_set[r.closed_set_size] = vertex_id;
    r.closed_set_size ++;
    return r;

}

t_graph_info add_vertex_to_open_set(t_graph_info r, int vertex_id){
    r.open_set[r.open_set_size] = vertex_id;
    r.open_set_size ++;
    return r;

}

float h_n_manh (int vertex_id, int vertex_end, t_coords *coords){
    //return coords[vertex_id].x;
    return abs(coords[vertex_end].x-coords[vertex_id].x) + abs(coords[vertex_end].y-coords[vertex_id].y);
}

float h_n_eucl (int vertex_id, int vertex_end, t_coords *coords){
    //return coords[vertex_id].x;
    return( sqrt ( pow(coords[vertex_end].x-coords[vertex_id].x,2) + pow(coords[vertex_end].y-coords[vertex_id].y,2) ) );
}

t_graph_info a_star(t_graph** adjacent_list, t_coords *coords, int graph_size, int vertex_ini, int vertex_end){
    t_graph_info r;
    r.path_g_n = 0;
    r.closed_set = NULL;
    int current, i;
    int *is_in_open_set;
    int *g_score;
    float *f_score;
    int menor = INT_MAX;
    int iter = 0;
    int inf = INT_MAX;
    r.fechado = alloc_array(graph_size);
    r.anterior = alloc_array(graph_size);
    g_score = alloc_array(graph_size);
    f_score = alloc_array_float(graph_size);
    r.closed_set = alloc_array(graph_size);
    r.closed_set_size = 0;
    r.open_set = alloc_array(graph_size);
    r.open_set_size = 0;
    is_in_open_set = alloc_array(graph_size);
    for(i = 0; i<graph_size; i++){
        if(i == vertex_ini)
            g_score[i] = 0;
        else
            g_score[i] = inf;
    }

    for(i = 0; i<graph_size; i++){
        f_score[i] = inf;
    }

    for(i = 0; i<graph_size; i++){
        r.fechado[i] = 0;
    }

    for(i = 0; i<graph_size; i++){
        r.anterior[i] = 0;
    }

    for(i = 0; i<graph_size; i++){
        if(i == vertex_ini)
            is_in_open_set[i] = 1;
        else
            is_in_open_set[i] = 0;
    }
    f_score[vertex_ini] = h_n_eucl(vertex_ini, vertex_end, coords);
    r = add_vertex_to_open_set(r, vertex_ini);
    r.anterior[vertex_ini] = 0;

    while (current != vertex_end){
        for(i=0; i<graph_size;i++){
            if(menor>f_score[i] && r.fechado[i] != 1){
                menor = f_score[i];
                current = i;
            }
        }
        r.fechado[current] = 1;
        r.open_set[current] = inf;
        r = add_vertex_to_closed_set(r, current);
        t_graph* p;
        for(p = adjacent_list[current]; p!=NULL; p = p->prox){

            if(r.fechado[p->vertex]==1)
                continue;

            if(is_in_open_set[p->vertex] != 1){
                r = add_vertex_to_open_set(r, p->vertex);
                is_in_open_set[p->vertex] = 1;
            }

            int tentative_g_score = 0;
            tentative_g_score = g_score[current]+p->cost;
            if(tentative_g_score >= g_score[p->vertex])
                continue;

            r.anterior[p->vertex] = current;
            //printf("anterior: %d", r.anterior[p->vertex]);getchar();
            g_score[p->vertex] = tentative_g_score;
            f_score[p->vertex] = g_score[p->vertex] + h_n_eucl(p->vertex, vertex_end, coords);
        }
        menor = inf;
    }
    return r;

}
