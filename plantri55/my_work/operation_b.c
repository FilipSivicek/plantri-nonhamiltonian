/* PLUGIN file to use with plantri.c */

#pragma once
#include "../plantri.c"


static void extend3(EDGE *e);
static void extend4(EDGE *e, EDGE *list[]);
static void reduce3(EDGE *e);
static void reduce4(EDGE *e, EDGE *list[]);
static int make_colours(int col[], EDGE *e3);
static int canon(int lcolour[], EDGE *can_numberings[][MAXE],
    int *nbtot, int *nbop);
    
static void write_graph6(FILE *f, int doflip);

static void
find_extensions(int numb_total, int numb_pres,
    EDGE *ext3[], int *numext3, 
    EDGE *ext4[], int *numext4,
    EDGE *ext5[], int *numext5);
    
static void extend_b(EDGE *ext, EDGE* list[], int nbtot, int nbop){
    EDGE* list1[2];
    EDGE* list2[2];
    
    EDGE *ext3[MAXE/3],*ext4[MAXE/2],*ext5[MAXE];
    int next3,next4,next5;
    EDGE *save_list[4];
    register int i;
    register EDGE *e1,*e2,**nb,**nblim;
    EDGE *e,*ex;
    int nc,xnbtot,xnbop,v,needed_deg;
    int colour[MAXN];
    EDGE *firstedge_save[MAXE];
    
    find_extensions(nbtot,nbop,ext3,&next3,ext4,&next4,ext5,&next5);
    make_colours(colour, ext);
    
    extend3(ext);
    canon(degree,numbering,&xnbtot,&xnbop);    
    
    find_extensions(nbtot,nbop,ext3,&next3,ext4,&next4,ext5,&next5);
    extend4(ext->next->next, list1);
    
    //find_extensions(nbtot,nbop,ext3,&next3,ext4,&next4,ext5,&next5);
    extend4(ext, list2);
    
    list[0] = list1[0];
    list[1] = list1[1];
    
    list[2] = list2[0];
    list[3] = list2[1];
}
        
static void reduce_b(EDGE *e, EDGE *list[]){
    EDGE *list1[2];
    EDGE *list2[2];
    
    list1[0] = list[0];
    list1[1] = list[1];
    
    list2[0] = list[2];
    list2[1] = list[3];
    
    reduce4(e, list2);
    
    reduce4(e->next->next, list1);
    
    reduce3(e);
}

#define FILTER find_op_b
static int find_op_b(int nbtot, int nbop, int doflip){
    for (int i = 0; i < nv; i++){
        if (degree[i] == 4){
            int higher_5 = 0;
            EDGE *e = firstedge[i];
            for (int j = 0; j < 4; j++){
                if (degree[e->end] >= 5){
                    higher_5++;
                }
                else {
                    break;
                }
                e = e->next;
            }
            if (higher_5 == 4){
                e = firstedge[i];

                EDGE *list[4];
                
                extend_b(e, list, nbtot, nbop);
                write_graph6(outfile, doflip);

                reduce_b(e, list);
                return TRUE;
            }
        }
    }

    return FALSE;
}