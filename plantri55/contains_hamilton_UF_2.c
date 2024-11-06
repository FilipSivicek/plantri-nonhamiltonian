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

//connect vertex pos to all surrounding vertices with same colour
int connect(int pos, unsigned long long *vertices, unsigned long long *fixed, int *UF){
    EDGE *e = firstedge[pos];
    unsigned long long helper = *vertices&(1<<pos);
    int posColour = helper > 0; 
    for (int i = 0; i < degree[pos]; i++){
        if (e->end < pos){
            helper = *vertices&(1<<e->end);
            int endColour = helper > 0;
            if (endColour == posColour){
                if (FIND(e->end, UF) == FIND(pos, UF)){
                    return 0;
                }
                else{
                    UNION(e->end, pos, UF);
                    helper = *vertices&(1<<e->next->end);
                    int nextColour = helper > 0;
                    if (*fixed&(1<<e->next->end) && (nextColour == posColour)){
                        return 0;
                    }

                    helper = *vertices&(1<<e->prev->end);
                    int prevColour = helper > 0;
                    if (*fixed&(1<<e->prev->end) && (prevColour == posColour)){
                        return 0;
                    }

                    *vertices |= (1-posColour)<<e->next->end;
                    *fixed |= 1<<e->next->end;
                    *vertices |= (1-posColour)<<e->prev->end;
                    *fixed |= 1<<e->prev->end;
                }
            }
        }
        e = e->next;
    }
    return 1;
}

static int generate_vertices(int pos, unsigned long long vertices, unsigned long long fixed, int* UF){
    if (pos >= nv){
        int comp0 = 0;
        int comp1 = -1;

        for (int i = 1; i < nv; i++){
            if (vertices&(1<<i)){
                if (comp1 < 0){comp1 = FIND(i, UF);}
                else{
                    if (FIND(comp1, UF) != FIND(i, UF)){return 0;}
                }
            }
            else {
                if (FIND(comp0, UF) != FIND(i, UF)){return 0;}
            }
        }
        return 1;
    }

    if(fixed&(1<<pos)){
        if(connect(pos, &vertices, &fixed, UF)){
            return generate_vertices(pos+1, vertices, fixed, UF);
        }
        return 0;
    }

    fixed |= 1<<pos;
    unsigned long long copyVertices = vertices;
    unsigned long long copyFixed = fixed;
    int* copyUF = (int *) malloc(nv * sizeof(int));
    for (int i = 0; i < nv; i++){
        copyUF[i] = UF[i];
    }

    int ans = 0;

    if (connect(pos, &copyVertices, &copyFixed, copyUF)){
        ans = generate_vertices(pos+1, copyVertices, copyFixed, copyUF);
    }
    free(copyUF);
    if (ans){
        return 1;
    }

    ans = 0;
    vertices |= 1<<pos;
    if (connect(pos, &vertices, &fixed, UF)){
        ans = generate_vertices(pos+1, vertices, fixed, UF);
    }
    return ans;
}

#define FILTER contains_hamilton_UF_2

static int contains_hamilton_UF_2(int nbtot, int nbop, int doflip){
    int *UF = (int *) malloc(nv * sizeof(int));
    for (int i = 0; i < nv; i++){
        UF[i] = i;
    }
    int ans = !generate_vertices(1, 0, 1, UF);
    free(UF);
    return ans;
}