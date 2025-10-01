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
                write_graph6(outfile, doflip);

                EDGE* e1 = firstedge[i];
                extend3(e1);
                write_graph6(outfile, doflip);

                EDGE* e2;
                EDGE* list2[2];

                EDGE* h = firstedge[i];
                for (int j = 0; j < degree[i]; j++){
                    if(degree[h->end] == 3){
                        e2 = h->next;
                        printf("found e2\n");
                        break;
                    }
                    h = h->next;
                }

                printf("e2 = %d\n", e2);
                if (e2 == NULL){
                    printf("e2 is NULL\n");
                }

                extend4(e2, list2);
                write_graph6(outfile, doflip);

                EDGE* e3;
                EDGE* list3[2];

                for (int j = 0; j < degree[i]; j++){
                    if (degree[h->end] == 4 && degree[h->prev->end] == 4){
                        e3 = h->next;
                        printf("found e3\n");
                        break;
                    }
                    h = h->next;
                }

                printf("e3 = %d\n", e3);
                if (e3 == NULL){
                    printf("e3 is NULL");
                }

                extend4(e3, list3);
                write_graph6(outfile, doflip);

                reduce4(e3, list3);

                reduce4(e2, list2);

                reduce3(e1);
                return TRUE;
            }
        }
    }

    return FALSE;
}