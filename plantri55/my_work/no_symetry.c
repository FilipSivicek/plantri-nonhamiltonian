/* PLUGIN file to use with plantri.c 

   This plug-in filters out graphs with symetries
*/

static int testcanon(EDGE *givenedge, int representation[], int colour[]);
static void testcanon_first_init(EDGE *givenedge, int representation[], int colour[]);
static int testcanon_mirror(EDGE *givenedge, int representation[], int colour[]);

#define FILTER no_symetry

static int no_symetry(int nbtot, int nbop, int doflip){
    int representation[MAXE];
    int rcolour[nv];
    for (int i = 0; i < nv; i++) rcolour[i] = MAXN + degree[i];
    int degree_1 = degree[firstedge[0]->start];
    int degree_2 = degree[firstedge[0]->end];
    testcanon_first_init(firstedge[0], representation, rcolour);

    int same_representation = -1;
    for (int i = 0; i < nv; i++){
        EDGE *e = firstedge[i];
        if (degree[i] == degree_1){
            for (int j = 0; j < degree[i]; j++){
                if (degree[e->end] == degree_2){
                    if (testcanon(e, representation, rcolour) == 1){
                        same_representation++;
                    }
                    if (testcanon_mirror(e, representation, rcolour) == 1){
                        same_representation++;
                    }
                    if (same_representation > 0){
                        return FALSE;
                    }
                }
                e = e->next;
            }
        }
    }
    return TRUE;
}