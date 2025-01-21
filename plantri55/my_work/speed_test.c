/* PLUGIN file to use with plantri.c 

   To use this, compile plantri.c using 
       cc -o plantri_eulerian -O4 '-DPLUGIN="is_eulerian.c"' plantri.c

   This plug-in filters out those graphs, which are not
   Eulerian.
*/

#define FILTER speed_test

static int speed_test(int nbtot, int nbop, int doflip){
    return 0;
}