#pragma once
#include "../plantri.c"

static void extend3(EDGE *e);
static void extend4(EDGE *e, EDGE *list[]);
static void reduce3(EDGE *e);
static void reduce4(EDGE *e, EDGE *list[]);
static int make_colours(int col[], EDGE *e3);
static int canon(int lcolour[], EDGE *can_numberings[][MAXE],
    int *nbtot, int *nbop);
    
static void write_graph6(FILE *f, int doflip);

#define FILTER  multiple_e3_with_e4

static int multiple_e3_with_e4(int nbtot, int nbop, int doflip){
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
                e = firstedge[i];
                EDGE *list[2];
                write_graph6(outfile, doflip);

                extend4(e->next, list);
                write_graph6(outfile, doflip);

                reduce4(e->next, list);
                return TRUE;
            }
        }
    }

    return FALSE;
}