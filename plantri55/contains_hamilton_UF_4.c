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

int generate_fixed(int pos, int *vertices){
    
    EDGE *e = firstedge[pos];
    int posColour = vertices[pos];
    for (int i = 0; i < degree[pos]; i++){
        int endColour = vertices[e->end];
        if (endColour > 1){
            vertices[e->end] -= 2;
            endColour -= 2;
        }
        if((endColour == posColour)){

            int nextColour = vertices[e->next->end];
            int prevColour = vertices[e->prev->end];
            
            if(nextColour == posColour || nextColour-2 == posColour){
                return 0;
            }
            if(prevColour == posColour || prevColour-2 == posColour){
                return 0;
            }

            if (vertices[e->next->end] < 0){
                vertices[e->next->end] = (1-posColour)+2;
            }
            if (vertices[e->prev->end] < 0){
                vertices[e->prev->end] = (1-posColour)+2;
            }
        }
        e = e->next;
    }
    return 1;
}


//connect vertex pos to all surrounding vertices with same colour
int connect(int pos, int *vertices, int *UF){
    EDGE *e = firstedge[pos];
    int posColour = vertices[pos]; 
    for (int i = 0; i < degree[pos]; i++){
        if (e->end < pos){
            if (vertices[e->end] == posColour){
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

int generate_vertices(int pos, int *vertices, int *UF){
    if (pos >= nv){
        //check if generated division is good.
        int comp0 = FIND(0, UF);
        int comp1 = -1;

        for (int i = 1; i < nv; i++){
            if (vertices[i]){
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


    for (int i = 1; i < nv; i++){
        if(vertices[i] > 1){
            vertices[i] -= 2;
            if(!generate_fixed(i, vertices)){
                return 0;
            }
        }
    }

    if (vertices[pos] >= 0){
        if(vertices[pos] > 1){
            vertices[pos] -= 2;
        }
        if (connect(pos, vertices, UF)){
            return generate_vertices(pos+1, vertices, UF);
        }
        return 0;
    }//*/


    vertices[pos] = 0;
    int* copyUF = (int *) malloc(nv * sizeof(int));
    memcpy(copyUF, UF, nv * sizeof(int));

    int* copyVertices = (int *) malloc(nv * sizeof(int));
    memcpy(copyVertices, vertices, nv * sizeof(int));

    int ans = 0;

    if (connect(pos, copyVertices, copyUF) && generate_fixed(pos, copyVertices)/**/){
        ans = generate_vertices(pos+1, copyVertices, copyUF);
    }
    free(copyUF);
    free(copyVertices);
    if (ans){
        return 1;
    }

    ans = 0;
    vertices[pos] = 1;
    if (connect(pos, vertices, UF) && generate_fixed(pos, vertices)/**/){
        ans = generate_vertices(pos+1, vertices, UF);
    }
    vertices[pos] = -1;
    return ans;
}

#define FILTER contains_hamilton_UF_3

static int contains_hamilton_UF_3(int nbtot, int nbop, int doflip){
    int *UF = (int *) malloc(nv * sizeof(int));
    int *vertices = (int *) malloc(nv * sizeof(int)); 
    // 1, 0 - colour, -1 - not coloured nor fixed, 2 - next to be coloured 0, 3 - next to be coloured 1 
    for (int i = 0; i < nv; i++){
        UF[i] = i;
        vertices[i] = -1;
    }
    vertices[0] = 0;
    int ans = !generate_vertices(1, vertices, UF);
    free(UF);
    return ans;
}