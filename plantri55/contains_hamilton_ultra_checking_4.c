/* PLUGIN file to use with plantri.c 

   This plug-in filters out those graphs, which does
   not contain clique of size 4.
*/

/*
Checks, if division is good and if it can be good.
Returns 1, if division is good, 0 if it is not good but can still be good
and -1 if it cannot be good.
*/

static int check_if_good(register unsigned long long vertices){
    int v1 = -1;
    int v2 = -1;
    for (int i = 0; i < nv; i++){
        if (vertices&(1<<i)){
            v1 = i;
        }
        else {
            v2 = i;
        }
        if (v1 >= 0 && v2>= 0){
            break;
        }
    }
    
    if (v1 < 0 || v2 < 0){ return 0;}
    int active_vertices[nv];
    active_vertices[0] = v1;
    active_vertices[1] = v2;
    int pos_front = 0;
    int pos_back = 2;
    
    int parent[nv];
    memset(parent, -1, sizeof parent);
    parent[v1] = v1;
    parent[v2] = v2;
    
    int is_tree[] = {1, 1};
    int is_connected[] = {1, 1};
    EDGE *e;
    
    while (pos_front < pos_back){
        int mom = active_vertices[pos_front];
        e = firstedge[mom];
        int momColour = vertices&(1<<mom);
        for (int i = 0; i < degree[mom]; i++){
            int endColour = vertices&1<<e->end;
            if (((momColour > 0) == (endColour > 0))){
                if((parent[e->end] == -1)){
                    active_vertices[pos_back] = e->end;
                    pos_back++;
                    parent[e->end] = mom;
                }
                else {
                    if (parent[mom] != e->end){
                        is_tree[momColour > 0] = 0;
                        if(!is_tree[1]){
                            return -1;
                        }
                    }
                }
            }
            e = e->next;
        }
        pos_front++;
    }
    for (int i = 0; i < nv; i++){
        if (parent[i] == -1){
            int iColour = vertices&(1<<i);
            is_connected[iColour > 0] = 0;
            if(!is_connected[0]){
                return -1;
            }
        }
    }
    if (is_tree[0] && is_tree[1] && is_connected[0] && is_connected[1]){
        return 1;
    }
    return 0;
}

static int generate_vertices(register int pos, register unsigned long long vertices){
    if (pos >= nv){
        return 0;
    }
    int is_good = check_if_good(vertices);
    if (is_good == 1){
        return 1;
    }
    if (is_good < 0){
        return 0;
    }
    int ans = generate_vertices(pos+1, vertices);
    if(ans){
        return 1;
    }
    vertices += 1<<pos;
    ans = generate_vertices(pos+1, vertices);
    return ans;
}

#define FILTER contains_hamilton

static int contains_hamilton(int nbtot, int nbop, int doflip){
    return !generate_vertices(0, 0);
}