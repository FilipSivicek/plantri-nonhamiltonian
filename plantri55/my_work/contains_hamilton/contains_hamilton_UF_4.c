/* PLUGIN file to use with plantri.c */

int FIND(int p, int* UF){
    if (UF[p] == p){
        return p;
    }
    UF[p] = FIND(UF[p], UF);
    return UF[p];
}
 
void UNION(int p1, int p2, int* UF){
    UF[FIND(p2, UF)] = FIND(p1, UF);
}

int generate_vertices(register int pos, register unsigned long long vertices, register int* UF){
    if (pos >= nv){
        //check if good
        int comp0 = FIND(0, UF);
        int comp1 = -1;

        for (int i = 1; i < nv; i++){
            if (vertices&(1<<i)){
                if (comp1 < 0){
                    comp1 = FIND(i, UF);
                }
                else{
                    if (comp1 != FIND(i, UF)){return 0;}
                }
            }
            else {
                if (comp0 != FIND(i, UF)){return 0;}
            }
        }
        return 1;
    }

    int* copyUF = (int *) malloc(nv * sizeof(int));
    memcpy(copyUF, UF, nv * sizeof(int));

    if(5*pos >= 4*nv){
        for (int i = 1; i < nv; i++){
            if(!vertices&(1<<i)){
                EDGE *e = firstedge[i];
                for (int j = 0; j < degree[i]; j++){
                    if(!vertices&(1<<e->end)){
                        UNION(e->end, i, copyUF);
                    }
                } 
            }
        }
        int comp0 = FIND(0, copyUF);
        for (int i = 0; i < nv; i++){
            if(!vertices&(1<<i)){
                if (FIND(i, UF) != comp0){
                    return 0;
                }
            }
        }
        memcpy(copyUF, UF, nv * sizeof(int));
    }

    EDGE *e = firstedge[pos];
    
    int canColour = 1;
    for (int i = 0; i < degree[pos]; i++){
        if (e->end < pos){
            int endColour = vertices&(1<<e->end); 
            if (endColour == 0){
                if (FIND(e->end, copyUF) == FIND(pos, copyUF)){
                    canColour = 0;
                    break;
                }
                else {
                    UNION(e->end, pos, copyUF);
                }
            }
        }
        e = e->next;
    }
    
    int ans = 0;
    if (canColour){
        ans = generate_vertices(pos+1, vertices, copyUF);
    }
    free(copyUF);

    if (ans){return 1;}
    
    vertices += 1<<pos;
    canColour = 1;
    for (int i = 0; i < degree[pos]; i++){
        if (e->end < pos){
            int endColour = vertices&(1<<e->end); 
            if (endColour > 0){
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
    for (int i = 0; i < nv; i++){
        if (degree[i] == 4){
            EDGE *e = firstedge[i];
            for (int j = 0; j < 4; j++){
                if(degree[e->end] == 4){
                    return 0;
                }
                e = e->next;
            }
        }
    }



    int *UF = (int *) malloc(nv * sizeof(int));
    for (int i = 0; i < nv; i++){
        UF[i] = i;
    }

    int ans = !generate_vertices(1, 0, UF);
    free(UF);
    return ans;
}