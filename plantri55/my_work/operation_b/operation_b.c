/* PLUGIN file to use with plantri.c */

#pragma once
#include "../../plantri.c"

#define FILTER find_op_b

static int find_op_b(int nbtot, int nbop, int doflip){
    for (int i = 0; i < nv; i++){
        if (degree[i] == 4){
            int higher_5 = 0;
            EDGE *e = firstedge[i];
            for (int j = 0; j < 4; j++){
                if (degree[e->end] >= 5){
                    higher_5++;
                }
                else {
                    break;
                }
                e = e->next;
            }
            if (higher_5 == 4){
                return TRUE;
            }
        }
    }

    return FALSE;
}