#include "../sharedLibrary/adjacentList.h"
#include "a_star.h"
//#include "dijkstra_heap.h"

char graph_folder[60];
char coord_folder[60];
char visited_coordinates_folder[60];
char path_coordinates_folder[60];
char *path_folder;
char data_structure_type[3];

void print_list(t_graph *graph){
    t_graph *p;
    for(p=graph; p!=NULL; p=p->prox){
        printf("%d|%d\t", p->vertex, p->cost);
    }

}

void define_paths(t_graph_info dijkstra_results, int graph_size){
    int maior = 0;
    int medio = 0;
    int menor = 0;
    int diameter_vertex = 0;
    int center_vertex = 0;
    int min_vertex = 0;
    int i;
    for (i=0; i<graph_size; i++){
        if(maior<dijkstra_results.distancia[i]){
            maior = dijkstra_results.distancia[i];
            diameter_vertex = i;
        }
    }
    for (i=0; i<graph_size; i++){
        if(dijkstra_results.distancia[i] >= (maior/2)-100 && dijkstra_results.distancia[i] <= (maior/2)+100){
            //maior = dijkstra_results.distancia[i];
            medio = dijkstra_results.distancia[i];
            center_vertex = i;
        }
    }

    for (i=0; i<graph_size; i++){
        if(dijkstra_results.distancia[i] >= (medio/2)-100 && dijkstra_results.distancia[i] <= (medio/2)+100){
            //maior = dijkstra_results.distancia[i];
            menor = dijkstra_results.distancia[i];
            min_vertex = i;
        }
    }
    printf("Facil: 1 X %d vertex\n", min_vertex+1);
    printf("Medio: 1 X %d vertex\n", center_vertex+1);
    printf("Dificil: 1 X %d vertex\n", diameter_vertex+1);
}

void get_paths(t_path *path, char **argv){
    if(strcmp(argv[1],"-d")==0){
        if(strcmp(argv[2],"-NY")==0){
            path[0].src = 0;
            path[0].dest = 264313;
            path[1].src = 0;
            path[1].dest = 225018;
            path[2].src = 0;
            path[2].dest = 90643;
        }
        else if(strcmp(argv[2],"-COL")==0){
            path[0].src = 0;
            path[0].dest = 402947;
            path[1].src = 0;
            path[1].dest = 382912;
            path[2].src = 0;
            path[2].dest = 316377;
        }
        else if(strcmp(argv[2],"-FLA")==0){
            path[0].src = 0;
            path[0].dest = 279200;
            path[1].src = 0;
            path[1].dest = 1045673;
            path[2].src = 0;
            path[2].dest = 634661;
        }
        else if(strcmp(argv[2],"-BAY")==0){
            path[0].src = 0;
            path[0].dest = 260766;
            path[1].src = 0;
            path[1].dest = 318361;
            path[2].src = 0;
            path[2].dest = 98762;
        }
        else if(strcmp(argv[2],"-RO")==0)
            strcpy(graph_folder,"../../instances/distanceGraphs/rome99.gr");
        else if(strcmp(argv[2],"-TES")==0){
            path[0].src = 0;
            path[0].dest = 15;
            path[1].src = 0;
            path[1].dest = 15;
            path[2].src = 0;
            path[2].dest = 15;
        }
    }

    else if(strcmp(argv[1],"-t")==0){
        if(strcmp(argv[2],"-NY")==0){
            path[0].src = 0;
            path[0].dest = 262760;
            path[1].src = 0;
            path[1].dest = 222032;
            path[2].src = 0;
            path[2].dest = 90643;
        }
        else if(strcmp(argv[2],"-COL")==0){
            path[0].src = 0;
            path[0].dest = 434169;
            path[1].src = 0;
            path[1].dest = 194410;
            path[2].src = 0;
            path[2].dest = 316377;
        }
        else if(strcmp(argv[2],"-FLA")==0){
            path[0].src = 0;
            path[0].dest = 1065119;
            path[1].src = 0;
            path[1].dest = 1039872;
            path[2].src = 0;
            path[2].dest = 593823;
        }
        else if(strcmp(argv[2],"-BAY")==0){
            path[0].src = 0;
            path[0].dest = 258804;
            path[1].src = 0;
            path[1].dest = 320389;
            path[2].src = 0;
            path[2].dest = 98812;
        }
        else if(strcmp(argv[2],"-RO")==0)
            strcpy(graph_folder,"../../instances/distanceGraphs/rome99.gr");
        else if(strcmp(argv[2],"-TES")==0){
            path[0].src = 0;
            path[0].dest = 15;
            path[1].src = 0;
            path[1].dest = 15;
            path[2].src = 0;
            path[2].dest = 15;
        }
    }
}

void save_visited_coordinates_file(t_graph_info a_star_results, t_coords *coords, int graph_size, int path){
    FILE *f;
    if(path == 0)
        strcat(visited_coordinates_folder, ".1");
    else if (path == 1)
        strcat(visited_coordinates_folder, "2");
    else if (path == 2)
        strcat(visited_coordinates_folder, "3");

    f = fopen(visited_coordinates_folder, "w");
    int i;
    for(i=0; i<a_star_results.closed_set_size; i++){
        fprintf(f,"%c %d %d %d\n",coords[a_star_results.closed_set[i]].v, coords[a_star_results.closed_set[i]].vertex, coords[a_star_results.closed_set[i]].x, coords[a_star_results.closed_set[i]].y);
    }
    fclose(f);

}

void save_path_coordinates_file(t_graph_info a_star_results, t_coords *coords, int graph_size, int src, int path){
    FILE *f;
    if(path == 0)
        strcat(path_coordinates_folder, ".1");
    else if (path == 1)
        strcat(path_coordinates_folder, "2");
    else if (path == 2)
        strcat(path_coordinates_folder, "3");

    f = fopen(path_coordinates_folder, "w");
    int i = src;
    int cont= 0;
    while(i != 0){
       // printf("path: %d", i+1); getchar();
        fprintf(f,"%c %d %d %d\n",coords[i].v, coords[i].vertex, coords[i].x, coords[i].y);
        i = a_star_results.anterior[i];
        cont++;
    }
    //printf("path: %d", i+1); getchar();
    fclose(f);
}

int count_path(t_graph_info a_star_results, int src){
    int cont = 0;
    int i = src;
    while(i!=0){
        i = a_star_results.anterior[i];
        cont++;
    }
    return cont;

}

void save_distance_and_anterior_file (int **distancia, int **anterior, int graph_size){
    FILE *f, *f1;
    int i, j;

    f = fopen("rome.anterior.matrix.txt", "w");
    f1 = fopen("rome.distancia.matrix.txt", "w");

    for(i=0; i<graph_size; i++){
        for(j=0; j<graph_size; j++){
            fprintf(f, "%d ", anterior[i][j]);
            fprintf(f1, "%d ", distancia[i][j]);
        }
        fprintf(f, "\n");
        fprintf(f1, "\n");
    }
    fclose(f);
    fclose(f1);
}

t_coords *read_coordinates_from_file(FILE *f, int graph_size){
    t_coords *coords;
    t_coords c;
    coords = (t_coords*)malloc(graph_size*sizeof(t_coords));
    int i = 0;
    while (fscanf(f, "%c %d %d %d\n", &c.v, &c.vertex, &c.x, &c.y) != EOF){
        coords[i] = c;
        i++;
    }
    return coords;
}

int main(int argc, char **argv){

    readParameters(argc, argv);
    int graph_size;

    t_graph **adjacent_list;
    t_path *path;
    path = (t_path*)malloc(3*sizeof(t_path));

    int **anterior_matrix;
    int **distance_matrix;

    t_graph_info a_star_results;
    t_coords *coords;
    //int *distance;
    int i;

    FILE *f,*f1;

    f = fopen (graph_folder, "r");
    if(f==NULL){
        printf("Fail to read file 1!\n");
        exit(0);
    }

    if(strcmp(argv[2], "-RO") != 0){
        f1 = fopen (coord_folder, "r");
        if(f1==NULL){
            printf("Fail to read file 2!\n");
            exit(0);
        }
    }

    graph_size = get_graph_size(f, argv);

    get_paths(path, argv);
    adjacent_list = get_adjacent_list(adjacent_list, graph_size, f, argv);
    if(strcmp(argv[2], "-RO") != 0)
        coords = read_coordinates_from_file(f1,graph_size);


    if(strcmp(data_structure_type, "-v") == 0){
        //printf("aStar List!\n");

        for(i=0;i<3;i++){
            clock_t begin = clock();
            a_star_results = a_star (adjacent_list, coords, graph_size, path[i].src, path[i].dest);
            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("Distance from %d to %d vertex: %d\n", path[i].src+1, path[i].dest+1,a_star_results.g_score[path[i].dest]);
            show_time_spent(time_spent);
            int path_size;
            if(strcmp(argv[2], "-RO") != 0){
                //save_visited_coordinates_file(a_star_results,coords,graph_size, i);
                //save_path_coordinates_file(a_star_results,coords,graph_size, path[i].dest, i);
            }
            path_size = count_path(a_star_results, path[i].dest);
            printf("Path %d\tClosedSet Size: %d, Path Size: %d\n\n", i,a_star_results.closed_set_size, path_size);
        }
    }
}
