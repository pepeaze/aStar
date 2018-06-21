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

t_graph_info add_vertex_to_open_set(t_graph_info r, int vertex_id){
    r.open_set[r.open_set_size] = vertex_id;
    r.open_set_size ++;
    return r;

}

float h_n (int vertex_id, int vertex_end, t_coords *coords){
    return coords[vertex_id].x;//( sqrt ( pow(coords[vertex_end].x-coords[vertex_id].x,2) + pow(coords[vertex_end].y-coords[vertex_id].y,2) ) );
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
    //t_l *open_set = NULL;
    t_o_set o;
    r.path_g_n = 0;
    r.closed_set = NULL;
    int current, i;
    int *is_in_open_set;
    int *g_score;
    float *f_score;
    int menor = INT_MAX;
    int iter = 0;

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
            g_score[i] = INT_MAX/3;
    }

    for(i = 0; i<graph_size; i++){
        f_score[i] = INT_MAX/3;
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
    f_score[vertex_ini] = o.f_score;
    r = add_vertex_to_open_set(r, vertex_ini);
    r.anterior[vertex_ini] = 0;
    //open_set = insere_ordenado(open_set,o); //inserindo no inicial no openSet
    //printf("%d, %f\n", open_set->node.vertex_id, open_set->node.f_score);
    int k;
    while (current != vertex_end){
        /*if(open_set!=NULL){
            r.path_g_n += open_set->node.cost;
            open_set = remove_from_top(open_set, &current);
            r = add_vertex_to_closed_set(r, current);

        }*/
        printf("gscore:\n");
        for(i=0; i<graph_size;i++){
            printf("%d ", g_score[i]);
        }
        printf("\nfscore:\n");
        for(i=0; i<graph_size;i++){
            printf("%.f ", f_score[i]);
            if(menor>=f_score[i] && r.open_set[i] != INT_MAX/2){
                menor = f_score[i];
                current = i;
            }
        }
        printf("\ncurrent: %d\n", current+1);
        r.fechado[current] = 1;
        r.open_set[current] = INT_MAX/2;
        printf("current has now: %d value\n", r.open_set[current]); getchar();
        r = add_vertex_to_closed_set(r, current);
        t_graph* p;
        for(p = adjacent_list[current]; p!=NULL; p = p->prox){

            if(r.fechado[p->vertex]==1)
                continue;

            if(is_in_open_set[p->vertex] != 1){
                    //open_set = insere_ordenado(open_set,o);
                r = add_vertex_to_open_set(r, p->vertex);
                is_in_open_set[p->vertex] = 1;
            }

            int tentative_g_score = 0;
            if (current == 2){
                printf("tentative_g_score = %d + %d = ", g_score[current], p->cost);
            }
            tentative_g_score = g_score[current]+p->cost;
            if (current==2){
                printf("%d\n",tentative_g_score);
            }
            if(tentative_g_score >= g_score[p->vertex])
                continue;

            r.anterior[p->vertex] = current;
            g_score[p->vertex] = tentative_g_score;
            f_score[p->vertex] = g_score[p->vertex] + h_n(p->vertex, vertex_end, coords);
                //o.vertex_id = p->vertex;
                //o.cost = p->cost;
                //o.f_score = g_score[p->vertex] + h_n(o.vertex_id, vertex_end, coords);


        }
        menor = INT_MAX;
    }

    printf("%d %d\n", r.closed_set_size, r.path_g_n);
    return r;

}
