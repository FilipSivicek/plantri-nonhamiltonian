/* PLUGIN file to use with plantri.c
This plugin checks, if graph can be separated into 2 trees.

 */

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


int generate_fixed(int pos, unsigned long long *vertices, unsigned long long *fixed,
    unsigned long long *newFixed){
    
    EDGE *e = firstedge[pos];
    unsigned long long helper = *vertices&(1<<pos);
    int posColour = helper > 0;
    for (int i = 0; i < degree[pos]; i++){
        helper = *vertices&(1<<e->end);
        int endColour = helper > 0;
        
        if(*fixed&(1<<e->end) && (endColour == posColour)){

            helper = *vertices&(1<<e->next->end);
            int nextColour = helper > 0;

            helper = *vertices&(1<<e->prev->end);
            int prevColour = helper > 0;
            
            if((*fixed&(1<<e->next->end)) && (nextColour == posColour)){
                return 0;
            }
            if((*fixed&(1<<e->prev->end)) && (prevColour == posColour)){
                return 0;
            }

            *vertices |= (1-posColour)<<e->next->end;
            if (!(*fixed&(1<<e->next->end))){
                *newFixed |= 1<<e->next->end;
            }

            *vertices |= (1-posColour)<<e->prev->end;
            if (!(*fixed&(1<<e->prev->end))){
                *newFixed |= 1<<e->prev->end;
            }
        }
        e = e->next;
    }
    return 1;
}


//connect vertex pos to all surrounding vertices with same colour
int connect(int pos, unsigned long long *vertices, int *UF){
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
                }
            }
        }
        e = e->next;
    }
    return 1;
}

static int generate_vertices(int pos, unsigned long long vertices, unsigned long long fixed,
    unsigned long long newFixed, int* UF){
    if (pos >= nv){
        //check if generated division is good.
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

    ///*
    if (newFixed){
        fixed |= newFixed;
        unsigned long long nextFixed = 0;

        for (int i = 1; i < nv; i++){
            if (newFixed&(1<<i)){
                if (!generate_fixed(i, &vertices, &fixed, &nextFixed)){
                    return 0;
                }
            }
        }
        return generate_vertices(pos, vertices, fixed, nextFixed, UF);
    }//*/

    ///*
    if (fixed&(1<<pos)){
        if(connect(pos, &vertices, UF)){
            return generate_vertices(pos+1, vertices, fixed, newFixed, UF);
        }
        return 0;
    }//*/

    fixed |= 1<<pos;
    unsigned long long copyVertices = vertices;
    unsigned long long copyFixed = fixed;
    unsigned long long copyNF = newFixed;
    
    int* copyUF = (int *) malloc(nv * sizeof(int));
    memcpy(copyUF, UF, nv * sizeof(int));

    int ans = 0;

    if (connect(pos, &copyVertices, copyUF) && generate_fixed(pos, &copyVertices, &copyFixed, &copyNF)/**/){
        ans = generate_vertices(pos+1, copyVertices, copyFixed, copyNF, copyUF);
    }
    free(copyUF);
    if (ans){
        return 1;
    }

    ans = 0;
    vertices |= 1<<pos;
    if (connect(pos, &vertices, UF) && generate_fixed(pos, &vertices, &fixed, &newFixed)/**/){
        ans = generate_vertices(pos+1, vertices, fixed, newFixed, UF);
    }
    return ans;
}

#define FILTER contains_hamilton_UF_3

static int contains_hamilton_UF_3(int nbtot, int nbop, int doflip){
    
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
    int ans = !generate_vertices(1, 0, 1, 0, UF);
    free(UF);
    return ans;
}