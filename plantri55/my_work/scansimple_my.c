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
    
static void
scansimple_my(int nbtot, int nbop, EDGE *list[3], int next_edge, int doflip)
{
    
    write_graph6(outfile, doflip);
    if (next_edge >= 3){
        // write_graph6(outfile, doflip);
        return;
    }
    
    
    EDGE *ext3[MAXE/3],*ext4[MAXE/2],*ext5[MAXE];
    int next3,next4,next5;
    EDGE *save_list[4];
    register int i;
    register EDGE *e1,*e2,**nb,**nblim;
    EDGE *e,*ex;
    int nc,xnbtot,xnbop,v,needed_deg;
    int colour[MAXN];
    EDGE *firstedge_save[MAXE];
    

        if (nv == splitlevel)
    {
#ifdef SPLITTEST
        ++splitcases;
        return;
#endif
        if (splitcount-- != 0) return;
        splitcount = mod - 1;
    
        for (i = 0; i < nv; ++i) firstedge_save[i] = firstedge[i];
    }

    /* The following could be improved significantly by avoiding
    extensions that can't lead to success here. */
    if (polygonsize >= 9)
    {
        needed_deg = polygonsize + nv - maxnv;
        for (i = 0; i < nv; ++i)
        if (degree[i] >= needed_deg) break;
        if (i == nv) return;
    }
    
    #ifdef PRE_FILTER_SIMPLE
    if (!(PRE_FILTER_SIMPLE)) return;
    #endif
    
    #ifndef FIND_EXTENSIONS_SIMPLE
    #define FIND_EXTENSIONS_SIMPLE find_extensions
    #endif
    
    FIND_EXTENSIONS_SIMPLE(nbtot,nbop,ext3,&next3,ext4,&next4,ext5,&next5);
    
    next3 = 0;
    next4 = 0;
    next5 = 0;
    if (next_edge == 0){
        next3 = 1;
        ext3[0] = list[0];
    }
    
    if (next_edge == 1){
        next4 = 1;
        ext4[0] = list[1];
    }
    
    if (next_edge == 2){
        next4 = 1;
        ext4[0] = list[2];
    }
    
    for (i = 0; i < next3; ++i)
    {
        nc = make_colours(colour,ext3[i]);
        if (nc)
        {
            extend3(ext3[i]);
            #ifdef FAST_FILTER_SIMPLE
            if (FAST_FILTER_SIMPLE)
            #endif 
            {
                canon(colour,numbering,&xnbtot,&xnbop);
                scansimple_my(xnbtot,xnbop, list, next_edge + 1, doflip);
            }
            reduce3(ext3[i]);
        }
    }
    
    for (i = 0; i < next4; ++i)
    {
        extend4(ext4[i],save_list);
        #ifdef FAST_FILTER_SIMPLE
        if (FAST_FILTER_SIMPLE)
        #endif
        { 
            canon(degree,numbering,&xnbtot,&xnbop);
            {
                e = numbering[0][0];
                v = e->next->next->end;
                ex = e->invers;
                for (e = ex->next; e != ex; e = e->next) if (e->end == v) break;
                
                e1 = ext4[i]->next->invers;
                if (e != ex) e1 = e1->next;
                
                e2 = e1->next->next;
                nblim = (EDGE**)numbering[xnbtot];
                for (nb = (EDGE**)numbering[0]; nb < nblim; nb += MAXE)
                if (*nb == e1 || *nb == e2) break;
                
                scansimple_my(xnbtot,xnbop, list, next_edge + 1, doflip); 
            }
        }
        reduce4(ext4[i],save_list); 
    }

    if (nv == splitlevel)
        for (i = 0; i < nv; ++i) firstedge[i] = firstedge_save[i];
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

                EDGE *list[3];
                list[0] = e;
                list[1] = e->next->next;
                list[2] = e;

                scansimple_my(nbtot, nbop, list, 0, doflip);
                return TRUE;
            }
        }
    }

    return FALSE;
}