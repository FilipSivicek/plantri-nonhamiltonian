/* PLUGIN file to use with plantri.c 

   This plug-in filters out those graphs, which does
   not contain clique of size 4.
*/

static void create_AM(int AM[][nv+1]){
    for (int i = 0; i < nv + (missing_vertex >= 0); i++){
        EDGE* e = firstedge[i];
        for (int j = 0; j < degree[i]; j++){
            AM[i][e->end] += 1;
            e = e->next;
        }
    }
}

#define FILTER not_simple_standard

static int not_simple_standard(int nbtot, int nbop, int doflip){
    int AM[nv+1][nv+1];
    memset(AM, 0, sizeof AM);
    create_AM(&AM);
    int n_s = 0;
    for (int i = 0; i < nv+(missing_vertex >= 0); i++){
        n_s += AM[i][i];
        for (int j = i; j < nv+(missing_vertex >= 0); j++){
            if (AM[i][j] > 1){
                n_s++;
            }
        }
    }
    return n_s > 0;
}