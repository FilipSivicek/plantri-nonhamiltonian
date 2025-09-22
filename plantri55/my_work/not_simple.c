/* PLUGIN file to use with plantri.c */

#pragma once
#include "../plantri.c"

static void create_AM(int** AM){
    for (int i = 0; i < nv + (missing_vertex >= 0); i++){
        EDGE* e = firstedge[i];
        for (int j = 0; j < degree[i]; j++){
            AM[i][e->end] += 1;
            e = e->next;
        }
    }
}

#define FILTER not_simple

static int not_simple(int nbtot, int nbop, int doflip){
    int **AM = (int **)malloc((nv+1) * sizeof(int*));
    for(int i = 0; i < nv+1; i++) AM[i] = (int *)malloc((nv+1) * sizeof(int));
    for (int i = 0; i < nv; i++){
        for (int j = 0; j < nv; j++){
            AM[i][j] = 0;
        }
    }
    create_AM(AM);
    int n_s = 0;
    for (int i = 0; i < nv+(missing_vertex >= 0); i++){
        n_s += AM[i][i];
        for (int j = i; j < nv+(missing_vertex >= 0); j++){
            if (AM[i][j] > 1){
                n_s++;
            }
        }
    }
    for (int i = 0; i < nv+1; i++){
        free(AM[i]);
    }
    free(AM);
    AM = NULL;
    return n_s > 0;
}