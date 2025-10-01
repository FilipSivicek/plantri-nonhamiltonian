/* PLUGIN file to use with plantri.c */

#pragma once
#include "../../plantri.c"


static void extend3(EDGE *e);
static void extend4(EDGE *e, EDGE *list[]);
static void reduce3(EDGE *e);
static void reduce4(EDGE *e, EDGE *list[]);
static int make_colours(int col[], EDGE *e3);
static int canon(int lcolour[], EDGE *can_numberings[][MAXE],
    int *nbtot, int *nbop);
    
static void write_graph6(FILE *f, int doflip);

static void
find_extensions(int numb_total, int numb_pres,
    EDGE *ext3[], int *numext3, 
    EDGE *ext4[], int *numext4,
    EDGE *ext5[], int *numext5);
    
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
                e = firstedge[i];
                EDGE *list1[4];
                EDGE *list2[4];
                EDGE *list3[4];

                write_graph6(outfile, doflip);
                extend4(e->next, list1);
                write_graph6(outfile, doflip);

                extend4(e->next->invers->next, list2);
                write_graph6(outfile, doflip);

                extend4(e->prev->prev, list3);
                write_graph6(outfile, doflip);

                reduce4(e->prev->prev, list3);
                reduce4(e->next->invers->next, list2);
                reduce4(e->next, list1);
                return TRUE;
            }
        }
    }

    return FALSE;
}