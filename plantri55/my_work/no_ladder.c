#pragma once
#include "../plantri.c"

static void testcanon_first_init(EDGE *givenedge, int representation[], int colour[]);
static int testcanon_init(EDGE *givenedge, int representation[], int colour[]);
static int testcanon_mirror_init(EDGE *givenedge, int representation[], int colour[]);
static void write_alpha(FILE *f, int doflip);

static void extend4(EDGE *e, EDGE **list);
static void reduce4(EDGE *e, EDGE **list);

static void write_graph6(FILE *f, int doflip);

static void rep_printer(int code[], int num_v){
    int index = 0;
    int num_vert = 0;
    while(num_vert < num_v){
        printf("%d ", code[index]);
        if (code[index] == 0){
            num_vert++;
        }
        index++;
    }
    printf("\n");
}

static int priority_calculator_v2(int code[], int num_v){
    // vertices are index from 1
    int seq[num_v + 1];
    
    int index = 0;
    if (num_v >= 9) num_v = 9;

    for (int curr = 1; curr <= num_v; curr++){
        int edge = 1;
        while (code[index] != 0){
            edge++;
            index++;
        }
        seq[curr] = edge;
        index++;
        // in our class no vertex can have order less than 4
        if (edge == 3) return -1;
    }

    // A, B, C, D, E, F, G
    if (seq[1] == 4){
        // A, B, C, D, E, F
        if (seq[2] == 5 && seq[3] == 5){
            // A, C, D 
            if (seq[4] == 5){
                // A, D
                if (seq[5] >= 6 && seq[6] >= 4){
                    // A
                    if (seq[7] >= 6 && seq[8] == 4 && seq[9] >= 5){
                        return 0;
                    }

                    // D
                    if (seq[7] >= 5 && seq[8] >= 5 && seq[9] >= 4){
                        return 3;
                    }
                }

                // C
                if (seq[5] == 5){
                    if (seq[6] >= 5 && seq[7] >= 5 && seq[8] >= 5 && seq[9] >= 5){
                        return 2;
                    }
                }
            }

            // B, E, F
            if (seq[4] >= 6 && seq[5] >= 6){
                // B
                if (seq[6] >= 6 && seq[7] == 4 && seq[8] >= 6){
                    return 1;
                }

                // E
                if (seq[6] >= 5 && seq[7] == 5 && seq[8] >= 4){
                    return 4;
                }

                // F
                if (seq[6] >= 4 && seq[7] >= 6 && seq[8] >= 4){
                    return 5;
                }
            }
        }

        // G
        if ((seq[2] >= 5 && seq[3] >= 6 && seq[4] >= 5 && seq[5] >= 6) 
        || (seq[2] >= 6 && seq[3] >= 5 && seq[4] >= 6 && seq[5] >= 5)){
            return 6;
        }
    }

    // H
    else if (seq[1] == 5 && seq[2] >= 5 && seq[3] >= 5 && seq[4] >= 5 && seq[5] >= 5 
    && seq[6] >= 5){
        return 7;
    }

    return -1;
}

#define FILTER gadgets_priority

static int gadgets_priority(int nbtot, int nbop, int doflip){
    // create code
    int rep2[MAXE];
    
    int rcolour[nv];
    for (int i = 0; i < nv; i++) rcolour[i] = MAXN + 1;
    
    testcanon_first_init(firstedge[nv - 1], rep2, rcolour);

    int rep4[MAXE + MAXN];
    for (int i = 0; i < MAXE + MAXN; i++) rep4[i] = MAXE + MAXN;
    
    for (int i = 0; i < nv; i++){
        EDGE *e = firstedge[i];
        for (int j = 0; j < degree[i]; j++){
            testcanon_init(e, rep2, rcolour);
            testcanon_mirror_init(e, rep2, rcolour);
        }
    }


    for (int i = 0; i < nv; i++){
        if (degree[i] == 4){
            EDGE *e = firstedge[i];
            for (int j = 0; j < 4; j++){
                if (degree[e->end] == 4){
                    return FALSE;
                }
                e = e->next;
            }
        }
    }

    int res = priority_calculator_v2(rep2, nv);
    if (!res){
        fprintf(outfile, "rep2: ");
        rep_printer(rep2, nv);
        fprintf(outfile, "graph: ");
        write_graph6(outfile, 0);
    }
    return TRUE;
}