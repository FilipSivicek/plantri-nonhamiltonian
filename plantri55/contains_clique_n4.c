/* PLUGIN file to use with plantri.c 

   To use this, compile plantri.c using 
       cc -o plantri_eulerian -O4 '-DPLUGIN="is_eulerian.c"' plantri.c

   This plug-in filters out those graphs, which are not
   Eulerian.
*/

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

#define FILTER contains_clique_n4

static int contains_clique_n4(int nbtot, int nbop, int doflip){
    int AM[nv+1][nv+1];
    memset(AM, 0, sizeof AM);
    create_AM(AM);
    for (int i = 0; i < nv + (missing_vertex >= 0); i++){
        for (int j = i+1; j < nv + (missing_vertex >= 0); j++){
            for (int k = j+1; k < nv + (missing_vertex >= 0); k++){
                for (int l = k+1; l < nv + (missing_vertex >= 0); l++){
                    if (i != missing_vertex && j != missing_vertex && k != missing_vertex && l != missing_vertex){
                        int arr[4] = {i, j, k, l};
                        int num_edges = 0;
                        for (int m = 0; m < 4; m++){
                            for (int n = m+1; n < 4; n++){
                                num_edges+= AM[arr[m]][arr[n]];
                            }
                        }
                        if (num_edges == 6){
                            return FALSE;
                        }
                    }
                }
            }
        }
    }
    return TRUE;
}