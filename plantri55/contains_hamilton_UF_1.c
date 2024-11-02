/* PLUGIN file to use with plantri.c */

int FIND(int p, int* UF){
    if (UF[p] == p){
        return p;
    }
    UF[p] = FIND(UF[p], UF);
    return UF[p];
}
 
void UNION(int p1, int p2, int* UF){
    int f1 = FIND(p1, UF);
    int f2 = FIND(p2, UF);
    UF[f2] = f1;
}

static int generate_vertices(register int pos, register unsigned long long vertices, register int* UF){
    if (pos >= nv){
        //check if good
        int comp0 = 0;
        int comp1 = -1;
        for (int i = 0; i < nv; i++){
            if (vertices&(1<<i)){
                if (comp1 < 0){
                    comp1 = FIND(i, UF);
                }
                else{
                    if (FIND(comp1, UF) != FIND(i, UF)){
                        return 0;
                    }
                }
            }
            else {
                if (FIND(comp0, UF) != FIND(i, UF)){
                    return 0;
                }
            
            }
        }
        return 1;
    }

    int* copyUF1 = (int *) malloc(nv * sizeof(int));
    memcpy(copyUF1, UF, nv * sizeof(int));

    EDGE *e = firstedge[pos];
    
    int canColour = 1;
    for (int i = 0; i < degree[pos]; i++){
        if (e->end < pos){
            if (!(vertices&(1<<e->end))){
                if (FIND(e->end, copyUF1) == FIND(pos, copyUF1)){
                    canColour = 0;
                    break;
                }
                else {
                    UNION(e->end, pos, copyUF1);
                }
            }
        }
        e = e->next;
    }
    
    int ans = 0;
    if (canColour){
        ans = generate_vertices(pos+1, vertices, copyUF1);
    }
    free(copyUF1);

    if (ans){return 1;}
    
    vertices += 1<<pos;
    canColour = 1;
    for (int i = 0; i < degree[pos]; i++){
        if (e->end < pos){
            if ((vertices&(1<<e->end))){
                if (FIND(e->end, UF) == FIND(pos, UF)){
                    canColour--;
                    break;
                }
                else{
                    UNION(e->end, pos, UF);
                }
            }
        }
        e = e->next;
    }

    if (canColour){
        ans = generate_vertices(pos+1, vertices, UF);
    }
    return ans;
}

#define FILTER contains_hamilton_UF_1

static int contains_hamilton_UF_1(int nbtot, int nbop, int doflip){
    int *UF = (int *) malloc(nv * sizeof(int));
    for (int i = 0; i < nv; i++){
        UF[i] = i;
    }    
    int ans = !generate_vertices(1, 0, UF);
    free(UF);
    return ans;
}