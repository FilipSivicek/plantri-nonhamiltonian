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

//somewhere here is mistake
int generate_fixed_print(int pos, int fixedUpTo, unsigned long long *vertices, unsigned long long *fixed,
    unsigned long long *newFixed){
    
    EDGE *e = firstedge[pos];
    unsigned long long helper = *vertices&(1<<pos);
    int posColour = helper > 0;
    printf("vertices, pos, posColour: %llu, %d, %d\n", *vertices, pos, posColour);
    //printf("vertices: %llu\n", *vertices);
    //printf("fixed: %llu\n", *fixed);
    for (int i = 0; i < degree[pos]; i++){
        printf("%d ",e->end);
        e = e->next;
    }
    printf("\n");
    for (int i = 0; i < degree[pos]; i++){
        helper = *vertices&(1<<e->end);
        int endColour = helper > 0;
        if(e->end < fixedUpTo && (endColour == posColour)){
            
            int nextEnd = e->next->end;
            int prevEnd = e->prev->end;
            helper = *vertices&(1<<nextEnd);
            int nextColour = helper > 0;
            //printf("helper: %llu\n", helper);
            //printf("nextColour: %d\n", nextColour);
            helper = *vertices&(1<<prevEnd);
            int prevColour = helper > 0;
            printf("e->end, nextEnd, nextColour, prevEnd, prevColour: %d, %d, %d, %d, %d\n", e->end, nextEnd, nextColour, prevEnd, prevColour);
            if((nextEnd < fixedUpTo) && (nextColour == posColour)){
                printf("invalid 1\n\n");
                return 0;
            }
            //printf("prevColour: %d\n", prevColour);
            if((prevEnd < fixedUpTo) && (prevColour == posColour)){
                printf("invalid 2\n\n");
                return 0;
            }

            *vertices |= (1-posColour)<<nextEnd;
            if (!(*fixed&(1<<nextEnd))){
                *newFixed |= 1<<nextEnd;
            }

            *vertices |= (1-posColour)<<prevEnd;
            if (!(*fixed&(1<<prevEnd))){
                *newFixed |= 1<<prevEnd;
            }
        }
        e = e->next;
    }
    printf("correct 1\n\n");
    return 1;
}

int generate_fixed(int pos, int fixedUpTo, unsigned long long *vertices, unsigned long long *fixed,
    unsigned long long *newFixed){
    
    EDGE *e = firstedge[pos];
    unsigned long long helper = *vertices&(1<<pos);
    int posColour = helper > 0;
    //printf("vertices, pos, posColour: %llu, %d, %d\n", *vertices, pos, posColour);
    //printf("vertices: %llu\n", *vertices);
    //printf("fixed: %llu\n", *fixed);
    for (int i = 0; i < degree[pos]; i++){
        //printf("%d ",e->end);
        e = e->next;
    }
    //printf("\n");
    for (int i = 0; i < degree[pos]; i++){
        helper = *vertices&(1<<e->end);
        int endColour = helper > 0;
        if(e->end < fixedUpTo && (endColour == posColour)){
            
            int nextEnd = e->next->end;
            int prevEnd = e->prev->end;
            helper = *vertices&(1<<nextEnd);
            int nextColour = helper > 0;
            //printf("helper: %llu\n", helper);
            //printf("nextColour: %d\n", nextColour);
            helper = *vertices&(1<<prevEnd);
            int prevColour = helper > 0;
            //printf("e->end, nextEnd, prevEnd: %d, %d, %d\n", e->end, nextEnd, prevEnd);
            if((nextEnd < fixedUpTo) && (nextColour == posColour)){
                //printf("invalid 1\n\n");
                return 0;
            }
            //printf("prevColour: %d\n", prevColour);
            if((prevEnd < fixedUpTo) && (prevColour == posColour)){
                //printf("invalid 2\n\n");
                return 0;
            }

            *vertices |= (1-posColour)<<nextEnd;
            if (!(*fixed&(1<<nextEnd))){
                *newFixed |= 1<<nextEnd;
            }

            *vertices |= (1-posColour)<<prevEnd;
            if (!(*fixed&(1<<prevEnd))){
                *newFixed |= 1<<prevEnd;
            }
        }
        e = e->next;
    }
    //printf("correct 1\n\n");
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

static int generate_vertices_print(int pos, unsigned long long vertices, unsigned long long fixed,
    unsigned long long newFixed, int* UF){
    printf("\npos: %d\n", pos);
    printf("vertices: %llu\n", vertices);
    printf("fixed: %llu\n", fixed);
    printf("new fixed: %llu\n", newFixed);
    if (pos >= nv){
        //check if good
        int comp0 = -1;
        int comp1 = -1;

        for (int i = 0; i < nv; i++){
            if (vertices&(1<<i)){
                if (comp1 < 0){comp1 = FIND(i, UF);}
                else{
                    if (FIND(comp1, UF) != FIND(i, UF)){return 0;}
                }
            }
            else {
                if (comp0 < 0){comp0 = FIND(i, UF);}
                else {
                    if (FIND(comp0, UF) != FIND(i, UF)){return 0;}
                }
            }
        }
        return 1;
    }

    ///*
    if (newFixed){
        fixed |= newFixed;
        int newFixedCopy = 
        newFixed = 0;
        for (int i = 0; i < nv; i++){
            if (fixed&(1<<i)){
                if (!generate_fixed_print(i, pos, &vertices, &fixed, &newFixed)){
                    return 0;
                }
            }
        }
        return generate_vertices_print(pos, vertices, fixed, newFixed, UF);
    }//*/

    ///*
    if (fixed&(1<<pos)){
        if (connect(pos, &vertices, UF)){
            return generate_vertices_print(pos+1, vertices, fixed, newFixed, UF);
        }
        return 0;
    }//*/

    unsigned long long copyVertices = vertices;
    unsigned long long copyFixed = fixed;
    unsigned long long copyNF = newFixed;
    int* copyUF = (int *) malloc(nv * sizeof(int));
    for (int i = 0; i < nv; i++){
        copyUF[i] = UF[i];
    }

    int ans = 0;

    if (connect(pos, &copyVertices, copyUF) && generate_fixed_print(pos, pos, &copyVertices, &copyFixed, &copyNF)/**/){
        ans = generate_vertices_print(pos+1, copyVertices, copyFixed, copyNF, copyUF);
    }
    free(copyUF);
    if (ans){
        return 1;
    }

    ans = 0;
    vertices |= 1<<pos;
    if (connect(pos, &vertices, UF) && generate_fixed_print(pos, pos, &vertices, &fixed, &newFixed)/**/){
        ans = generate_vertices_print(pos+1, vertices, fixed, newFixed, UF);
    }
    return ans;
}


static int generate_vertices(int pos, unsigned long long vertices, unsigned long long fixed,
    unsigned long long newFixed, int* UF){
    //printf("\npos: %d\n", pos);
    //printf("vertices: %llu\n", vertices);
    //printf("fixed: %llu\n", fixed);
    //printf("new fixed: %llu\n", newFixed);
    if (pos >= nv){
        //check if good
        int comp0 = -1;
        int comp1 = -1;

        for (int i = 0; i < nv; i++){
            if (vertices&(1<<i)){
                if (comp1 < 0){comp1 = FIND(i, UF);}
                else{
                    if (FIND(comp1, UF) != FIND(i, UF)){return 0;}
                }
            }
            else {
                if (comp0 < 0){comp0 = FIND(i, UF);}
                else {
                    if (FIND(comp0, UF) != FIND(i, UF)){return 0;}
                }
            }
        }
        return 1;
    }

    ///*
    if (newFixed){
        fixed |= newFixed;
        int newFixedCopy = 
        newFixed = 0;
        for (int i = 0; i < nv; i++){
            if (fixed&(1<<i)){
                if (!generate_fixed(i, pos, &vertices, &fixed, &newFixed)){
                    return 0;
                }
            }
        }
        return generate_vertices(pos, vertices, fixed, newFixed, UF);
    }//*/

    ///*
    if (fixed&(1<<pos)){
        if (connect(pos, &vertices, UF)){
            return generate_vertices(pos+1, vertices, fixed, newFixed, UF);
        }
        return 0;
    }//*/

    unsigned long long copyVertices = vertices;
    unsigned long long copyFixed = fixed;
    unsigned long long copyNF = newFixed;
    int* copyUF = (int *) malloc(nv * sizeof(int));
    for (int i = 0; i < nv; i++){
        copyUF[i] = UF[i];
    }

    int ans = 0;

    if (connect(pos, &copyVertices, copyUF) && generate_fixed(pos, pos, &copyVertices, &copyFixed, &copyNF)/**/){
        ans = generate_vertices(pos+1, copyVertices, copyFixed, copyNF, copyUF);
    }
    free(copyUF);
    if (ans){
        return 1;
    }

    ans = 0;
    vertices |= 1<<pos;
    if (connect(pos, &vertices, UF) && generate_fixed(pos, pos, &vertices, &fixed, &newFixed)/**/){
        ans = generate_vertices(pos+1, vertices, fixed, newFixed, UF);
    }
    return ans;
}

#define FILTER contains_hamilton_UF_3

static int contains_hamilton_UF_3(int nbtot, int nbop, int doflip){
    int *UF = (int *) malloc(nv * sizeof(int));
    for (int i = 0; i < nv; i++){
        UF[i] = i;
    }
    int ans = !generate_vertices(1, 0, 0, 0, UF);
    if(ans){
        for (int i = 0; i < nv; i++){
            UF[i] = i;
        }
    
        generate_vertices_print(1, 0, 0, 0, UF);
        for (int i = 0; i < nv; i++){
            printf("%d: ", i);
            EDGE *e = firstedge[i];
            for (int j = 0; j < degree[i]; j++){
                printf("%d ", e->end);
                e = e->next;
            }
            printf("\n");
        }
        printf("end of cycle\n\n\n\n");
    }
    free(UF);
    return ans;
}