#pragma once
#include "../plantri.c"

static void testcanon_first_init(EDGE *givenedge, int representation[], int colour[]);
static int testcanon_init(EDGE *givenedge, int representation[], int colour[]);
static int testcanon_mirror_init(EDGE *givenedge, int representation[], int colour[]);
static void write_alpha(FILE *f, int doflip);

static void extend4(EDGE *e, EDGE **list);
static void reduce4(EDGE *e, EDGE **list);

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

static int 
testcanon_init_v2(EDGE *givenedge, int representation[], int colour[])

/* Tests whether starting from a given edge and constructing the code in
   "->next" direction, an automorphism or even a better representation can 
   be found. A better representation will be completely constructed and 
   returned in "representation".  It works pretty similar to testcanon except 
   for obviously necessary changes, so for extensive comments see testcanon */
{
    register EDGE *run;
    register int vertex;
    EDGE *temp;  
    EDGE *startedge[MAXN+1]; 
    int number[MAXN], i; 
    int better = 0; /* is the representation already better ? */
    int last_number, actual_number;

    for (i = 0; i < nv; i++) number[i] = 0;

    number[givenedge->start] = 1; 
    last_number = 1; 

    actual_number = 1;
    temp = givenedge;

    while (last_number < nv)
    {  
        run = temp;
        for (i = 0; i < degree[temp->start]; i++)
          { vertex = run->end;
            if (!number[vertex])
              { startedge[last_number] = run->invers;
                last_number++; number[vertex] = last_number; 
                vertex = colour[vertex]; }
            else vertex=number[vertex];
            if (better) *representation = vertex; 
             else { if (vertex > (*representation)) return 0;
                     else if (vertex < (*representation)) 
                       { better = 1; *representation = vertex; }
                  }
            representation++; 
            run = run->next;
          }
        if ((*representation) != 0) { better = 1; *representation = 0; }
        representation++;
        temp = startedge[actual_number];  actual_number++;
    }

    while (actual_number <= nv) 
    {  
        run = temp;
        for (i = 0; i < degree[temp->start]; i++)
          { vertex = number[run->end]; 
            if (better) *representation = vertex;
            else                  
              {
                if (vertex > (*representation)) return 0;
                if (vertex < (*representation))
                  { better = 1; *representation = vertex; }
              }
            representation++;
            run = run->next;
          }
        if ((*representation) != 0) { better = 1; *representation = 0; }
        representation++;
        temp = startedge[actual_number];  actual_number++;
    }

    if (better) return 2;
    return 1;
}

static int priority_calculator_v3(int code[], int num_v){
    // vertices are index from 1
    int seq[num_v + 1];
    
    int index = 0;
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
    int rep[MAXE];
    int rep2[MAXE];
    int rep3[MAXE + MAXN];
    for (int i = 0; i < MAXE + MAXN; i++) rep3[i] = MAXN + MAXE;
    
    int rcolour[nv];
    for (int i = 0; i < nv; i++) rcolour[i] = MAXN + 1;
    
    int rcolour2[nv];
    for (int i = 0; i < nv; i++) rcolour2[i] = MAXN + degree[i];
    
    int rep4[MAXE + MAXN];
    for (int i = 0; i < MAXE + MAXN; i++) rep4[i] = MAXE + MAXN;
    int rcolour4[nv];
    for (int i = 0; i < nv; i++) rcolour4[i] = MAXN + 2;
    for (int i = 0; i < nv; i++){
        if (degree[i] == 5){
            EDGE *e = firstedge[i];
            for (int j = 0; j < 5; j++){
                if (degree[e->end] == 5){
                    if (degree[e->prev->end] == 4 && degree[e->next->end] == 4){
                        rcolour4[i] = MAXN + 1;
                        if (degree[e->next->next->end] == 5){
                            rcolour4[e->next->next->end] = MAXN + 1;    
                        }
                    }
                }
                e = e->next;
            }
        }
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

    int mindegree = MAXN;

    for (int i = 0; i < nv; i++){
        if (degree[i] == 3){
            return FALSE;
        }
        if (degree[i] < mindegree){
            mindegree = degree[i];
        }
    }

    for (int i = 0; i < nv; i++){
        EDGE *e = firstedge[i];
        for (int j = 0; j < degree[i]; j++){
            testcanon_init_v2(e, rep4, rcolour4);
            e = e->next;
        }
    }

    int res = priority_calculator_v3(rep4, nv);
    if (res >= 0){
        EDGE *list[2];
        fprintf(outfile, "gadget: %d\n", res);
        //printf("testing rep4: ");
        //rep_printer(rep4, nv);
        return TRUE;
    }

    return FALSE;
}