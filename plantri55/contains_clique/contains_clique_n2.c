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

static int exists_last(int v1, int v2, int v3, int AM[][nv+1]){
    if (v1 == v2 || v2 == v3 || v1 == v3){
        return FALSE;
    }
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
            if (e->end != v1 && e->end != v2 && e->end != v3){
                return TRUE;
            }
        }
        e = e->next;
    }
    return FALSE;
}

#define FILTER contains_clique_n2

static int contains_clique_n2(int nbtot, int nbop, int doflip){
    int AM[nv+1][nv+1];
    memset(AM, 0, sizeof AM);
    create_AM(&AM);
    int connected[nv+1]; 
    for (int i = 0; i < nv + (missing_vertex >= 0); i++){
        if (i != missing_vertex){
            memset(connected, 0, sizeof connected);
            int potential[degree[i]];
            EDGE *e = firstedge[i];
            for (int j = 0; j < degree[i]; j++){
                potential[j] = e->end;
                connected[e->end] = 1;
                e = e->next;
            }
            for (int j = 0; j < degree[i]; j++){
                e = firstedge[potential[j]];
                for (int k = 0; k < degree[potential[j]]; k++){
                    if (e->end != i && connected[e->end]){
                        if (i < potential[j] && potential[j] < e->end){
                            if (exists_last(i, potential[j], e->end, &AM)){
                                return FALSE;
                            }
                        }
                    }
                    e = e->next;
                }
            }
        }
    }
    return TRUE;
}