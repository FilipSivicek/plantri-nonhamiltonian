/* PLUGIN file to use with plantri.c 

   This plug-in filters out those graphs, which does
   not contain clique of size 4.
*/

static int exists_last(int v1, int v2, int v3, int AM[][nv+1]){
    int min_ver = v3;
    if (degree[v2] < degree[min_ver]){
        min_ver = v2;
    }
    if (degree[v1] < degree[min_ver]){
        min_ver = v1;
    }
    EDGE *e = firstedge[min_ver];
    for (int i = 0; i < degree[min_ver]; i++){
        if ((e->end != missing_vertex) && AM[v1][e->end] && AM[v2][e->end] && AM[v3][e->end]){
            return TRUE;
        }
        e = e->next;
    }
    return FALSE;
}

static void create_AM(int AM[][nv+1]){
    for (int i = 0; i < nv + (missing_vertex >= 0); i++){
        EDGE* e = firstedge[i];
        while(TRUE){
            AM[i][e->end] = 1;
            e = e->next;
            if (e == firstedge[i]){
                break;
            }
        }
    }
}

#define FILTER contains_clique_n

static int contains_clique_n(int nbtot, int nbop, int doflip){
    int AM[nv+1][nv+1];
    memset(AM, 0, sizeof AM);
    create_AM(&AM);
    for (int i = 0; i < nv + (missing_vertex >= 0); i++){
        EDGE *e = firstedge[i];
        for (int j = 0; j < degree[i]; j++){
            if (exists_last(i, e->end, e->next->end, &AM)){
                return FALSE;
            }
            e = e->next;
        }
    }
    return TRUE;
}