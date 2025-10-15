#pragma once
#include "../plantri.c"

static void testcanon_first_init(EDGE *givenedge, int representation[], int colour[]);
static int testcanon_init(EDGE *givenedge, int representation[], int colour[]);
static int testcanon_mirror_init(EDGE *givenedge, int representation[], int colour[]);

static void write_alpha(FILE *f, int doflip);
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

static int my_testcanon_init_v3(EDGE *givenedge, int representation[], int colour[]){
    if (colour[givenedge->start] > (*representation)){
        return 0;
    }
    
    register EDGE *run;
    register int vertex;
    EDGE *temp;  
    EDGE *startedge[MAXN+1]; 
    int number[MAXN], i, j; 
    int better = 0; /* is the representation already better? */
    int last_number;

    for (i = 0; i < nv; i++) number[i] = 0;

    number[givenedge->start] = 1; 
    last_number = 1;
    startedge[1] = givenedge->invers;

    if (colour[givenedge->start] < (*representation)){
        better = 1;
        *representation = colour[givenedge->start];
    }
    representation++;
    
    temp = givenedge;
    for(i = 0; i < nv; i++){
        run = temp;
        for (j = 0; j < degree[temp->start]; j++){
            vertex = number[run->end];
            if (!vertex){
                startedge[last_number] = run->invers;
                last_number++;
                number[run->end] = last_number;
                vertex = colour[run->end];
            }

            if (vertex < *representation){
                better = 1;
            }

            if (vertex > *representation && !better){
                return 0;
            }

            if (better){
                *representation = vertex;
            }
            representation++;

            if (i == 0 && j == 1 && degree[givenedge->start] == 4 
            && degree[run->prev->end] == 5 && degree[run->end] == 5){
                if (degree[run->invers->next->next->end] == 4){
                    startedge[last_number] = run->invers->next->next->invers;
                    last_number++;
                    number[run->invers->next->next->end] = last_number;

                    vertex = colour[run->invers->next->next->end];
                    if (vertex < *representation){
                        better = 1;
                    }

                    if (vertex > *representation && !better){
                        return 0;
                    }

                    if (better){
                        *representation = vertex;
                    }
                    representation++;
                }
            }

            run = run->next;
        }

        if (0 < *representation){
            better = 1;
        }

        if (better){
            *representation = 0;
        }

        representation++;
        temp = startedge[i + 1];
    }

    if (better){
        return 2;
    }

    return 1;
}

static int my_testcanon_init_mirror_v3(EDGE *givenedge, int representation[], int colour[]){
    if (colour[givenedge->start] > (*representation)){
        return 0;
    }
    
    register EDGE *run;
    register int vertex;
    EDGE *temp;  
    EDGE *startedge[MAXN+1]; 
    int number[MAXN], i, j; 
    int better = 0; /* is the representation already better? */
    int last_number;

    for (i = 0; i < nv; i++) number[i] = 0;

    number[givenedge->start] = 1; 
    last_number = 1;
    startedge[1] = givenedge->invers;

    if (colour[givenedge->start] < (*representation)){
        better = 1;
        *representation = colour[givenedge->start];
    }
    representation++;
    
    temp = givenedge;
    for(i = 0; i < nv; i++){
        run = temp;
        for (j = 0; j < degree[temp->start]; j++){
            vertex = number[run->end];
            if (!vertex){
                startedge[last_number] = run->invers;
                last_number++;
                number[run->end] = last_number;
                vertex = colour[run->end];
            }

            if (vertex < *representation){
                better = 1;
            }

            if (vertex > *representation && !better){
                return 0;
            }

            if (better){
                *representation = vertex;
            }
            representation++;

            if (i == 0 && j == 1 && degree[givenedge->start] == 4 
            && degree[run->next->end] == 5 && degree[run->end] == 5){
                if (degree[run->invers->prev->prev->end] == 4){
                    startedge[last_number] = run->invers->prev->prev->invers;
                    last_number++;
                    number[run->invers->prev->prev->end] = last_number;

                    vertex = colour[run->invers->prev->prev->end];
                    if (vertex < *representation){
                        better = 1;
                    }

                    if (vertex > *representation && !better){
                        return 0;
                    }

                    if (better){
                        *representation = vertex;
                    }
                    representation++;
                }
            }

            run = run->prev;
        }

        if (0 < *representation){
            better = 1;
        }

        if (better){
            *representation = 0;
        }

        representation++;
        temp = startedge[i + 1];
    }

    if (better){
        return 2;
    }

    return 1;
}

static int priority_calculator_v3(int code[], int num_v){
    // vertices are index from 1
    int seq[num_v + 1];
    
    int index = 1;
    if (num_v >= 9) num_v = 9;

    for (int curr = 1; curr <= num_v; curr++){
        int edge = 0;
        while (code[index] != 0){
            edge++;
            index++;
        }
        seq[curr] = edge;
        index++;
        // in our class no vertex can have order less than 4
        if (edge == 3) return -1;
    }

    if (seq[1] == 5 && seq[2] == 5 && seq[3] == 5 && seq[4] == 4){
        seq[1] = 4;
    }

    for (int i = 1; i <= num_v; i++){
        printf("%d ", seq[i]);
    }
    printf("\n");

    // A, B, C, D, E, F, G
    if (seq[1] == 4){
        // A, B, C, D, E, F
        if (seq[2] == 5 && seq[3] == 5){
            // A, B
            if (seq[4] == 4){
                // A
                if (seq[5] == 5 && seq[6] >= 6 && seq[7] >= 5 && seq[8] >= 6 && seq[9] >= 4){
                    return 0;
                }
                // B
                if (seq[5] >= 6 && seq[6] >= 6 && seq[7] >= 6 && seq[8] >= 6){
                    return 1;
                }
            }

            // C, D 
            if (seq[4] == 5){
                // D
                if (seq[5] >= 6 && seq[6] >= 4){
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

            // E, F
            if (seq[4] >= 6 && seq[5] >= 6){
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

    // create code
    int rep2[MAXE + MAXN];
    
    for (int i = 0; i < MAXE + MAXN; i++){
        rep2[i] = MAXE + MAXN;
    }

    int rcolour[nv];
    for (int i = 0; i < nv; i++) rcolour[i] = 100 + degree[i];
    
    my_testcanon_init_v3(firstedge[0], rep2, rcolour);

    int rep4[MAXE + MAXN];
    for (int i = 0; i < MAXE + MAXN; i++) rep4[i] = MAXE + MAXN;
    
    for (int i = 0; i < nv; i++){
        EDGE *e = firstedge[i];
        for (int j = 0; j < degree[i]; j++){
            my_testcanon_init_v3(e, rep2, rcolour);
            my_testcanon_init_mirror_v3(e, rep2, rcolour);
            e = e->next;
        }
    }

    int res = priority_calculator_v3(rep2, nv);
    if (res == -1){
        fprintf(outfile, "rep2: ");
        rep_printer(rep2, nv);
        fprintf(outfile, "graph: ");
        write_graph6(outfile, 0);
        return TRUE;
    }
    
    return FALSE;
}