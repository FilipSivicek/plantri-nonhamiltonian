#pragma once
#include "../plantri.c"

#define FILTER max_degree

static int max_degree(int nbtot, int nbop, int doflip){
    for (int i = 0; i < nv; i++){
        if (degree[i] > 6){
            return TRUE;
        }
    }

    return FALSE;
}