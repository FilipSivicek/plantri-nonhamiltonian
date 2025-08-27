/* PLUGIN file to use with plantri.c */

#pragma once
#include "../plantri.c"


static void extend3(EDGE *e);
static void extend4(EDGE *e, EDGE *list[]);
static void reduce3(EDGE *e);
static void reduce4(EDGE *e, EDGE *list[]);
    
static void write_graph6(FILE *f, int doflip);

void printer(int POUT){
    printf("Printing\n");
    for (int i = 0; i < POUT; i++){
        EDGE *e = firstedge[i];
        if (e == NULL);
        for (int j = 0; j < degree[i]; j++){
            printf("%d ", e->end);
            e = e->next;
        }
        printf("\n");
    }
}

void edge_printer(FILE* f){
    fprintf(f, "Printing edges\n");
    for (int i = 0; i < NUMEDGES; i++){
        EDGE e = edges[i];
        if (&e == NULL) break;
        fprintf(f,"start: %d, end: %d\n", e.start, e.end);  
    }
}

static void
find_extensions(int numb_total, int numb_pres,
    EDGE *ext3[], int *numext3, 
    EDGE *ext4[], int *numext4,
    EDGE *ext5[], int *numext5);
    
static void extend_b(EDGE *ext, EDGE* list[], int nbtot, int nbop, int doflip){
    EDGE* list1[2];
    EDGE* list2[2];
    

    FILE *f1 = fopen("edges1.txt", "w");
    FILE *f2 = fopen("edges2.txt", "w");
    FILE *f3 = fopen("edges3.txt", "w");
    FILE *f4 = fopen("edges4.txt", "w");
    int POUT = 20;

    edge_printer(f1);

    extend3(ext);
    write_graph6(outfile, doflip);
    printer(POUT);

    edge_printer(f2);
    
    extend4(ext->next->next, list1);
    write_graph6(outfile, doflip);
    printer(POUT);

    edge_printer(f3);
    
    extend4(ext, list2);
    write_graph6(outfile, doflip);
    printf("Printing\n");
    printer(POUT);

    edge_printer(f4);

    list[0] = list1[0];
    list[1] = list1[1];
    
    list[2] = list2[0];
    list[3] = list2[1];
}
        
static void reduce_b(EDGE *e, EDGE *list[]){
    EDGE *list1[2];
    EDGE *list2[2];

    FILE *f1 = fopen("reducing1.txt", "w");
    FILE *f2 = fopen("reducing2.txt", "w");
    FILE *f3 = fopen("reducing3.txt", "w");
    FILE *f4 = fopen("reducing4.txt", "w");
    
    list1[0] = list[0];
    list1[1] = list[1];
    
    list2[0] = list[2];
    list2[1] = list[3];
    
    edge_printer(f1);

    reduce4(e, list2);
    
    edge_printer(f2);

    reduce4(e->next->next, list1);

    edge_printer(f3);
    
    reduce3(e);

    edge_printer(f4);
}

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

                EDGE *list[4];
                
                write_graph6(outfile, doflip);

                extend_b(e, list, nbtot, nbop, doflip);
                write_graph6(outfile, doflip);

                reduce_b(e, list);
                write_graph6(outfile, doflip);

                return TRUE;
            }
        }
    }

    return FALSE;
}