#include "a_star.h"

int* alloc_array (int graph_size){
    int *a;
    a = (int*)calloc(graph_size,sizeof(int));
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
   /* if(r.closed_set == NULL){
        r.closed_set = (int *) malloc (sizeof(int));
        r.closed_set[0] = vertex_id;
        r.closed_set_size = 1;
    }
    else{
        r.closed_set = (int*) realloc(r.closed_set, r.closed_set_size+1*sizeof(int));
        r.closed_set[r.closed_set_size] = vertex_id;
        r.closed_set_size ++;
    }*/
    r.closed_set[r.closed_set_size] = vertex_id;
    r.closed_set_size ++;
    return r;

}

float h_n (int vertex_id, int vertex_end, t_coords *coords){
    return ( sqrt ( pow(coords[vertex_end].x-coords[vertex_id].x,2) + pow(coords[vertex_end].y-coords[vertex_id].y,2) ) );
}

t_l *insere_ordenado (t_l *open_set, t_o_set o){
    t_l *novo;
    t_l *a = NULL;
    t_l *p = open_set;

    while (p!=NULL && p->node.f_score < o.f_score){
        a = p;
        p = p->prox;
    }

    novo = (t_l*)malloc (sizeof(t_l));
    novo->node = o;
    if (a == NULL){
        novo->prox = open_set;
        open_set = novo;
    }
    else{
        novo->prox = a->prox;
        a->prox = novo;
    }

    return open_set;

}

t_l *remove_from_top (t_l *open_set, int *current){

    t_l *p = open_set;
    *current = p->node.vertex_id;
    open_set = p->prox;

    return open_set;
}


t_graph_info a_star(t_graph** adjacent_list, t_coords *coords, int graph_size, int vertex_ini, int vertex_end){
    t_graph_info r;
    t_l *open_set = NULL;
    t_o_set o;
    r.path_g_n = 0;
    r.closed_set = NULL;
    int current, i;
    int *is_in_open_set;
    int *g_score;
    int menor = INT_MAX;
    int iter = 0;

    r.fechado = alloc_array(graph_size);
    r.anterior = alloc_array(graph_size);
    g_score = alloc_array(graph_size);
    r.closed_set = alloc_array(graph_size);
    r.closed_set_size = 0;
    is_in_open_set = alloc_array(graph_size);
    for(i = 0; i<graph_size; i++){
        if(i == vertex_ini)
            g_score[i] = 0;
        else
            g_score[i] = INT_MAX/2;
    }

    for(i = 0; i<graph_size; i++){
        if(i == vertex_ini)
            r.fechado[i] = 1;
        else
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


    o.vertex_id = vertex_ini;
    o.cost = 0;
    o.f_score = o.cost + h_n(o.vertex_id, vertex_end, coords);
    open_set = insere_ordenado(open_set,o);
    //printf("%d, %f\n", open_set->node.vertex_id, open_set->node.f_score);
    int k;
    while (current != vertex_end){
        if(open_set!=NULL){
            r.path_g_n += open_set->node.cost;
            open_set = remove_from_top(open_set, &current);
            r = add_vertex_to_closed_set(r, current);

        }
        printf("%d\n", current);getchar();

        t_graph* p;
        for(p = adjacent_list[current]; p!=NULL; p = p->prox){
            if(r.fechado[p->vertex]==1)
                continue;
            int tentative_g_score = 0;
            tentative_g_score = g_score[current]+(g_score[current]+p->cost);

            if(tentative_g_score < g_score[p->vertex]){
                r.anterior[p->vertex] = current;
                g_score[p->vertex] = tentative_g_score;
                o.vertex_id = p->vertex;
                o.cost = p->cost;
                o.f_score = g_score[p->vertex] + h_n(o.vertex_id, vertex_end, coords);
                if(is_in_open_set[p->vertex] != 1){
                    open_set = insere_ordenado(open_set,o);
                    is_in_open_set[p->vertex] = 1;
                }
            }
        }
    }

    printf("%d %d\n", r.closed_set_size, r.path_g_n);
    return r;

}
