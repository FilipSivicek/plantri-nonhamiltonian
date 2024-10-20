/* PLUGIN file to use with plantri.c 

   This plug-in filters out those graphs, which does
   not contain clique of size 4.
*/

/*
Checks, if division is good and if it can be good.
Returns 1, if division is good, 0 if it is not good but can still be good
and -1 if it cannot be good.
*/

static int check_if_good(int v1, int v2, int vertices[]){
    if (v1 >= nv || v2 >= nv){
        v1 = -1;
        v2 = -1;
        for (int i = 0; i < nv; i++){
            if (vertices[i]){
                v1 = i;
            }
            else {
                v2 = i;
            }
        }
    }
    if (v1 == -1 || v2 == -1){ return 0;}
    
    int active_vertices[nv+1];
    active_vertices[0] = v1;
    active_vertices[1] = v2;
    int pos_front = 0;
    int pos_back = 2;
    
    int parent[nv+1];
    memset(parent, -1, sizeof parent);
    parent[v1] = v1;
    parent[v2] = v2;
    
    int is_tree[] = {1, 1};
    int is_connected[] = {1, 1};
    EDGE *e;
    
    while (pos_front < pos_back){
        int mom = active_vertices[pos_front];
        e = firstedge[mom];
        for (int i = 0; i < degree[mom]; i++){
            if (parent[e->end] == -1 && vertices[mom] == vertices[e->end]){
                active_vertices[pos_back] = e->end;
                pos_back++;
                parent[e->end] = mom;
            }
            else if (parent[e->end] != -1 && vertices[mom] == vertices[e->end]){
                if (parent[mom] != e->end){
                    is_tree[vertices[mom]] = 0;
                }
            }
            e = e->next;
        }
        pos_front++;
    }
    for (int i = 0; i < nv; i++){
        if (parent[i] == -1){
            is_connected[vertices[i]] = 0;
        }
    }
    if (!is_tree[1] || !is_connected[0]){
        return -1;
    }
    else if (is_tree[0] && is_tree[1] && is_connected[0] && is_connected[1]){
        return 1;
    }
    return 0;
}

static int generate_vertices(int pos, int v1, int v2, int vertices[]){
    if (pos >= nv + (missing_vertex >= 0)){
        return 0;
    }
    int is_good = check_if_good(v1, v2, vertices);
    if (is_good == 1){
        return 1;
    }
    if (is_good == -1){
        return 0;
    }
    int h1 = generate_vertices(pos+1, v1, v2, vertices);
    vertices[pos] = 1;
    v1 = pos;
    if (vertices[v2] == 1){
        v2 = pos+1;
    }
    int h2 = generate_vertices(pos+1, v1, v2, vertices);
    vertices[pos] = 0;
    return h1 || h2;
}

#define FILTER contains_hamilton

static int contains_hamilton(int nbtot, int nbop, int doflip){
    int vertices[nv+1];
    memset(vertices, 0, sizeof vertices);
    return !generate_vertices(0, -1, 0, &vertices);
}

    /*printf("vertices\n");
    for (int i = 0; i < nv; i++){
        printf("%d ", vertices[i]);
    }
    printf("\n");

    printf("parent\n");
    for (int i = 0; i < nv; i++){
        printf("%d ", parent[i]);
    }
    printf("\n");
    
    printf("is_tree: %d, %d\n", is_tree[0], is_tree[1]);
    printf("is_connected: %d, %d\n", is_connected[0], is_connected[1]);
    */
    