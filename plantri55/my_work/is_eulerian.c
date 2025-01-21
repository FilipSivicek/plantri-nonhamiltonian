/* PLUGIN file to use with plantri.c 

   To use this, compile plantri.c using 
       cc -o plantri_eulerian -O4 '-DPLUGIN="is_eulerian.c"' plantri.c

   This plug-in filters out those graphs, which are not
   Eulerian.
*/

#define FILTER is_eulerian

static int is_eulerian(int nbtot, int nbop, int doflip){
    for (int i = 0; i < nv + (missing_vertex >= 0); i++){
        if (i != missing_vertex && degree[i]%2){
            return FALSE;
        }
    }
    return TRUE;
}