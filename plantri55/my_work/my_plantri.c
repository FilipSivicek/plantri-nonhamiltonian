#include <stdio.h> 
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

#define MAXN 64
#define MAXE (6 * MAXN - 12)
#define MAXF (2*MAXN-4)    /* the maximum number of faces */

typedef struct e{
    int start;
    int end;
    struct e *next;
    struct e *prev;
    struct e* invers;

} EDGE;

static int degree[MAXN];
static int nv;
static int ne;
static int input_n;
static int total_graphs = 0;
static EDGE *first_edge[MAXN];

static int all_repr[MAXE][MAXN + MAXE];
static int repr_found;

static EDGE prepared_edges3[6 * MAXN];
static EDGE prepared_edges4[8 * MAXN];
static EDGE prepared_edges5[10 * MAXN];

static void rep_printer(int code[], int num_v){
    int index = 0;
    int num_vert = 0;
    while(num_vert < num_v){
        printf("%d ", code[index]);
        if (code[index] == 0){
            num_vert++;
        }
        index++;
    }
    printf("\n");
}

static void edge_printer(EDGE *e){
    printf("start = %d, end = %d\n", e->start, e->end);
}

static void print_graph(){
    for (int i = 0; i < nv; i++){
        printf("degree[%d] = %d\n", i, degree[i]);
        EDGE *e = first_edge[i];
        for (int j = 0; j < degree[i]; j++){
            printf("e: ");
            edge_printer(e);
            printf("e->invers: ");
            edge_printer(e->invers);
            e = e->next;
        }
    }
}

static void
compute_code(unsigned char code[])
 
/* computes a code by numbering the vertices in a breadth first manner and
   then listing them in code. Code is a sequence of numbers of length ne+nv+1.
   The first entry is the number of vertices.
   Then the numbers of the vertices adjacent to the vertex numbered 1 are
   given -- ended by a 0, and listed in clockwise orientation.
   Then those adjacent to 2, ended by a 0, etc. . In case of no
   double edges, the identification of the corresponding "half edges" leaving 
   each vertex is unique. Nevertheless also for this case the following rules
   apply (not in the definition of the code, but in this routine):

   In case of double edges, the first time a new vertex
   b occurs in the list, say it is in the list of vertex a, must be matched
   with the first occurence of vertex a in the list of b. In this routine
   it will always be the first position in the list of b.

   This spanning tree
   gives a unique matching for the other "half edges" -- provided the fact
   that the ordering comes from an embedding on the sphere. 

   In case of a given starting edge in code_edge, the start of this
   edge is numbered 1 and the end 2.
*/
{
    register EDGE *run;
    register int vertex;
    EDGE *temp;  
    EDGE *startedge[MAXN+1]; 
    int number[MAXN+1], i; 
    int last_number, actual_number;
    EDGE *givenedge;

    for (i = 0; i < nv; i++) number[i] = 0;
 
    *code=nv; code++;
    givenedge=first_edge[0]; 
    number[givenedge->start] = 1; 
    if (givenedge->start != givenedge->end)
      {
        number[givenedge->end] = 2;
        last_number = 2;
        startedge[1] = givenedge->invers;
      }
    else  last_number = 1;  

    actual_number = 1;
    temp = givenedge;

    while (last_number < nv)
    {   *code=number[temp->end]; code++;
        for (run = temp->next; run != temp; run = run->next)
          {
            vertex = run->end;
            if (!number[vertex])
              { startedge[last_number] = run->invers;
                last_number++; number[vertex] = last_number; 
                *code = last_number; }
            else *code = number[vertex];
            code++;
          }
        *code = 0;  code++;
        temp = startedge[actual_number];  actual_number++;
    }

    while (actual_number <= nv) 
    {   *code=number[temp->end]; code++;
        for (run = temp->next; run != temp; run = run->next)
          { 
            *code = number[run->end]; code++;
          }
        *code = 0;
        code++;
        temp = startedge[actual_number];  actual_number++;
    }
}

static void
write_code_as_graph6(FILE *f, unsigned char code[])

/* Write a graph represented in planar_code to a file in graph6 format.
   The imbedding is lost, loops are lost, and multiple edges are changed
   to one edge.  The vertex numbering is the same.  This does not use any
   global variables and works to 255 vertices. */

{
    unsigned char g6[20+MAXF*(MAXF-1)/12];
    register unsigned char *pin,*pout;
    int n,nlen,bodylen,i,j,org;
    static unsigned char g6bit[] = {32,16,8,4,2,1};

    pin = code;
    n = *pin++;

    if (n <= 62)
    {
        g6[0] = 63 + n;
        nlen = 1;
    }
    else
    {
        g6[0] = 63 + 63;
        g6[1] = 63 + 0;
        g6[2] = 63 + (n >> 6);
        g6[3] = 63 + (n & 0x3F);
        nlen = 4;
    }

    pout = g6 + nlen;
    bodylen = ((n * (n-1)) / 2 + 5) / 6;
    for (i = 0; i < bodylen; ++i) pout[i] = 0;
    pout[bodylen] = '\n';

    for (i = 0, org = -1; i < n; org += i, ++i)
    {
        while ((j = *pin++) != 0)
        {
            if (j <= i)
            {
                j += org;
                pout[j/6] |= g6bit[j%6];
            }
        }
    }

    for (i = 0; i < bodylen; ++i) pout[i] += 63;

    j = nlen + bodylen + 1;
    if (fwrite(g6,sizeof(unsigned char),(size_t)j,f) != j)
    {
        perror(">E ");
        exit(1);
    }
}

static void
write_alpha(FILE *f, int doflip)

/* Write in alphabetic format.  Always write in next direction,
   and if doflip != 0 also write in prev direction. */
{
    int i, j, start;
    unsigned char code[MAXN+MAXE+4];
    unsigned char precode[MAXN+MAXE+1];
    size_t length;

    length=nv+ne;

    compute_code(precode);

    if (nv >= 10) 
    {
        code[0] = '0' + nv/10;
        code[1] = '0' + nv%10;
        code[2] = ' ';
        length += 3;
        start=3;
    }
    else
    {
        code[0] = '0' + nv;
        code[1] = ' ';
        length += 2;
        start=2;
    }

    for (i = 1, j=start; j < length; ++i, ++j)
        if (precode[i]==0) code[j]=',';
        else code[j]=precode[i]-1+'a';

    code[j-1]='\n';
    if (fwrite(code,sizeof(unsigned char),length,f) != length)
    {
        perror(">E ");
        exit(1);
    }
}

static void
write_graph6(FILE *f, int doflip)

/* Write in graph6 format.  doflip is ignored. */
{
    unsigned char code[MAXN+MAXE+10];

    compute_code(code);
    write_code_as_graph6(f,code);
}

static int 
getswitchvalue(char *arg)
 
/* Find integer value for switch. 
   arg is a pointer to a command-line argument.
   pj is an index into arg, which is updated.
   The value of the switch is the function return value.
   For example, if arg="-xyz1432q" and *pj=3 (pointing at "z"),
       the value 1432 is returned and *pj=7 (pointing at "2").
   An absent value is equivalent to 0.
*/

{
    int i, ans;
 
    ans = 0;
    for (i = 0; arg[i] >= '0' && arg[i] <= '9'; ++i)
        ans = ans * 10 + (arg[i] - '0');
    
    return ans;
}

// fixed colouring. colour[i] = degree[i] + MAXN
static int my_testcanon_init_v3(EDGE *givenedge, int representation[]){
    if (degree[givenedge->start] + MAXN > (*representation)){
        return 0;
    }
    
    register EDGE *run;
    register int vertex;
    EDGE *startedge[MAXN + 1]; 
    int number[MAXN], i, j, dgr; 
    int better = 0; /* is the representation already better? */
    int last_number = 1;

    for (i = 0; i < nv; i++) number[i] = 0;

    number[givenedge->start] = 1; 
    startedge[0] = givenedge;

    if (degree[givenedge->start] + MAXN < (*representation)){
        better = 1;
        *representation = degree[givenedge->start] + MAXN;
    }
    representation++;
    
    for(i = 0; i < nv; i++){
        run = startedge[i];
        dgr = degree[run->start];
        for (j = 0; j < dgr; j++){
            vertex = number[run->end];
            if (!vertex){
                startedge[last_number] = run->invers;
                last_number++;
                number[run->end] = last_number;
                vertex = degree[run->end] + MAXN;
            }

            if (vertex < *representation){
                better = 1;
            }

            if (vertex > *representation && !better){
                return 0;
            }

            if (better){
                *representation = vertex;
            }
            representation++;
            run = run->next;
        }

        if (0 < *representation){
            better = 1;
        }

        if (better){
            *representation = 0;
        }

        representation++;
    }

    if (better){
        return 2;
    }

    return 1;
}

static int my_testcanon_init_mirror_v3(EDGE *givenedge, int representation[]){
    if (degree[givenedge->start] + MAXN > (*representation)){
        return 0;
    }
    
    register EDGE *run;
    register int vertex;
    EDGE *startedge[MAXN+1]; 
    int number[MAXN], i, j, dgr; 
    int better = 0; /* is the representation already better? */
    int last_number = 1;

    for (i = 0; i < nv; i++) number[i] = 0;

    number[givenedge->start] = 1; 
    startedge[0] = givenedge;

    if (degree[givenedge->start] + MAXN < (*representation)){
        better = 1;
        *representation = degree[givenedge->start] + MAXN;
    }
    representation++;
    
    for(i = 0; i < nv; i++){
        run = startedge[i];
        dgr = degree[run->start];
        for (j = 0; j < dgr; j++){
            vertex = number[run->end];
            if (!vertex){
                startedge[last_number] = run->invers;
                last_number++;
                number[run->end] = last_number;
                vertex = degree[run->end] + MAXN;
            }

            if (vertex < *representation){
                better = 1;
            }

            if (vertex > *representation && !better){
                return 0;
            }

            if (better){
                *representation = vertex;
            }
            representation++;
            run = run->prev;
        }

        if (0 < *representation){
            better = 1;
        }

        if (better){
            *representation = 0;
        }

        representation++;
    }

    if (better){
        return 2;
    }

    return 1;
}

static void init_k4(){
    static EDGE init_e[4][3];
    for (int i = 0; i < 4; i++){
        for (int j = 0 ; j < 3; j++){
            init_e[i][j] = (EDGE){i, j + (j >= i), NULL, NULL, NULL};
        }
    }

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 3; j++){
            if (i%2 == 0){
                init_e[i][j].next = &init_e[i][(j+1)%3];
                init_e[i][j].prev = &init_e[i][(j+2)%3];
            }
            else {
                init_e[i][j].prev = &init_e[i][(j+1)%3];
                init_e[i][j].next = &init_e[i][(j+2)%3];
            }
        }
    }

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 3; j++){
            init_e[i][j].invers = &init_e[init_e[i][j].end][init_e[i][j].start - (j < i)];
        }
    }

    for (int i = 0; i < 4; i++){
        first_edge[i] = &init_e[i][0];
        degree[i] = 3;
    }

    // init prepared_edges
    for (int i = 0; i < 6 * input_n; i++){
        prepared_edges3[i] = (EDGE){0, 0, NULL, NULL, NULL};
    }

    for (int i = 0; i < 8 * input_n; i++){
        prepared_edges4[i] = (EDGE){0, 0, NULL, NULL, NULL};
    }

    for (int i = 0; i < 10 * input_n; i++){
        prepared_edges5[i] = (EDGE){0, 0, NULL, NULL, NULL};
    }

    nv = 4;
    ne = 12;
    return;
}

static void my_ext3(EDGE *e){
    int incident_v[3] = {e->start, e->next->end, e->end};
    for (int i = 0; i < 3; i++){
        prepared_edges3[6 * nv + i].start = nv;
        prepared_edges3[6 * nv + i].end = incident_v[i];
        prepared_edges3[6 * nv + i].next = &prepared_edges3[6 * nv + (i + 2) % 3];
        prepared_edges3[6 * nv + i].prev = &prepared_edges3[6 * nv + (i + 1) % 3];
        prepared_edges3[6 * nv + i].invers = &prepared_edges3[6 * nv + i + 3];
    }

    for (int i = 0; i < 3; i++){
        first_edge[e->start] = e;
        degree[e->start]++;
        prepared_edges3[6 * nv + i + 3].start = e->start;
        prepared_edges3[6 * nv + i + 3].end = nv;
        prepared_edges3[6 * nv + i + 3].next = e->next;
        prepared_edges3[6 * nv + i + 3].prev = e;
        prepared_edges3[6 * nv + i + 3].invers = &prepared_edges3[6 * nv + i];

        e->next->prev = &prepared_edges3[6 * nv + i + 3];
        e->next = &prepared_edges3[6 * nv + i + 3];
        e = e->next->next->invers;
    }
    
    first_edge[nv] = &prepared_edges3[6 * nv];
    degree[nv] = 3;
    nv++;
    ne += 6;
}

static void my_reduce3(EDGE *e){
    EDGE *run = e;
    for (int i = 0; i < 3; i++){
        first_edge[e->start] = e;
        degree[e->start]--;
        run = e->next->next->invers;
        e->next->next->prev = e;
        e->next = e->next->next;
        e = run;
    }

    nv--;
    ne -= 6;
}

static void my_ext4(EDGE* e, EDGE* list[]){
    list[0] = e->next;
    list[1] = e->next->invers;
    int incident_v[4] = {e->start,e->next->next->end, e->next->end, e->end};
    for (int i = 0; i < 4; i++){
        prepared_edges4[8 * nv + i].start = nv;
        prepared_edges4[8 * nv + i].end = incident_v[i];
        prepared_edges4[8 * nv + i].next = &prepared_edges4[8 * nv + (i + 3) % 4];
        prepared_edges4[8 * nv + i].prev = &prepared_edges4[8 * nv + (i + 1) % 4];
        prepared_edges4[8 * nv + i].invers = &prepared_edges4[8 * nv + i + 4];
    }

    degree[e->end]++;
    degree[e->next->next->end]++;
    EDGE *helper = e->next->invers->prev;

    e->next->next->prev = e;
    e->next = e->next->next;

    helper->next->next->prev = helper;
    helper->next = helper->next->next;

    for (int i = 0; i < 4; i++){
        first_edge[e->start] = e;
        prepared_edges4[8 * nv + i + 4].start = e->start;
        prepared_edges4[8 * nv + i + 4].end = nv;
        prepared_edges4[8 * nv + i + 4].next = e->next;
        prepared_edges4[8 * nv + i + 4].prev = e;
        prepared_edges4[8 * nv + i + 4].invers = &prepared_edges4[8 * nv + i];

        e->next->prev = &prepared_edges4[8 * nv + i + 4];
        e->next = &prepared_edges4[8 * nv + i + 4];
        e = e->next->next->invers;
    }
    first_edge[nv] = &prepared_edges4[8 * nv];
    
    degree[nv] = 4;
    nv++;
    ne += 8;
}

static void my_reduce4(EDGE* e, EDGE* list[]){
    EDGE *run = e;
    for (int i = 0; i < 4; i++){
        first_edge[e->start] = e;
        run = e->next->next->invers;
        e->next->next->prev = e;
        e->next = e->next->next;
        e = run;
    }
    
    EDGE *helper = e->next->invers->next->invers;
    e->next->prev = list[0];
    e->next = list[0];

    helper->next->prev = list[1];
    helper->next = list[1];

    degree[e->end]--;
    degree[e->next->next->end]--;
    nv--;
    ne -= 8;
}

void my_ext5(EDGE *e, EDGE* list[]){
    list[0] = e->next;
    list[1] = e->next->invers;
    list[2] = e->next->next;
    list[3] = e->next->next->invers;

    int incident_v[5] = {e->start,e->next->next->next->end, e->next->next->end, e->next->end, e->end};
    for (int i = 0; i < 5; i++){
        prepared_edges5[10 * nv + i].start = nv;
        prepared_edges5[10 * nv + i].end = incident_v[i];
        prepared_edges5[10 * nv + i].next = &prepared_edges5[10 * nv + (i + 4) % 5];
        prepared_edges5[10 * nv + i].prev = &prepared_edges5[10 * nv + (i + 1) % 5];
        prepared_edges5[10 * nv + i].invers = &prepared_edges5[10 * nv + i + 5];
    }

    degree[e->end]++;
    degree[e->next->next->next->end]++;
    degree[e->start]--;

    e->next->next->next->prev = e;
    e->next = e->next->next->next;
    
    EDGE *helper = e->invers->prev->invers;
    helper->prev->prev->next = helper;
    helper->prev = helper->prev->prev;
    helper = helper->prev->invers;

    helper->prev->prev->next = helper;
    helper->prev = helper->prev->prev;

    for (int i = 0; i < 5; i++){
        first_edge[e->start] = e;
        prepared_edges5[10 * nv + i + 5].start = e->start;
        prepared_edges5[10 * nv + i + 5].end = nv;
        prepared_edges5[10 * nv + i + 5].next = e->next;
        prepared_edges5[10 * nv + i + 5].prev = e;
        prepared_edges5[10 * nv + i + 5].invers = &prepared_edges5[10 * nv + i];

        e->next->prev = &prepared_edges5[10 * nv + i + 5];
        e->next = &prepared_edges5[10 * nv + i + 5];
        e = e->next->next->invers;
    }
    first_edge[nv] = &prepared_edges5[10 * nv];
    
    degree[nv] = 5;
    nv++;
    ne += 10;
}

void my_reduce5(EDGE *e, EDGE *list[]){
    EDGE *run = e;
    for (int i = 0; i < 5; i++){
        first_edge[e->start] = e;
        run = e->next->next->invers;
        e->next->next->prev = e;
        e->next = e->next->next;
        e = run;
    }
    
    EDGE *helper = e->invers->prev->invers;
    e->next->prev = list[2];
    e->next = list[0];

    helper->prev->next = list[1];
    helper->prev = list[1];

    helper = helper->prev->prev->invers;
    helper->prev->next = list[3];
    helper->prev = list[3];

    degree[e->end]--;
    degree[e->next->next->next->end]--;
    degree[e->start]++;
    nv--;
    ne -= 10;
}

static int same_repr(int repr1[], int repr2[]){
    for (int i = 0; i < MAXE + MAXN; i++){
        if (repr1[i] != repr2[i]){
            return 0;
        }
    }
    return 1;
}

static int is_new_repr(int repr[]){
    for (int i = 0; i < repr_found; i++){
        if (same_repr(repr, all_repr[i])){
            return 0;
        }
    }
    return 1;
}

static void save_repr(int repr[]){
    for (int i = 0; i < MAXN + MAXE; i++){
        all_repr[repr_found][i] = repr[i];
    }
    repr_found++;
}

static int is_vert_canon(){
    int repr[MAXN + MAXE];
    for (int i = 0; i < MAXN + MAXE; i++){
        repr[i] = MAXN + MAXE;
    }

    for (int i = 0; i < nv - 1; i++){
        if (degree[i] < degree[nv - 1]){
            return 0;
        }
    }

    EDGE *e = first_edge[nv - 1];
    for (int i = 0; i < degree[nv - 1]; i++){
        my_testcanon_init_v3(e, repr);
        my_testcanon_init_mirror_v3(e, repr);
        e = e->next;
    }

    if (is_new_repr(repr)){
        save_repr(repr);
        return 1;
    }

    return 0;
}

static void my_find_extentions(EDGE *ext3[MAXN], int *num_ext3, EDGE* ext4[MAXN], int *num_ext4, EDGE* ext5[MAXN], int *num_ext5){
    repr_found = 0;
    // finding threes
    int k = 0;
    for (int i = 0; i < nv; i++){
        EDGE *e = first_edge[i];
        int last_degree = degree[i];
        for (int j = 0; j < last_degree; j++){
            my_ext3(e);
            if (is_vert_canon()){
                ext3[k] = e;
                k++;
            }
            my_reduce3(e);
            e = e->next;
        }
    }
    *num_ext3 = k;

    int repr[MAXN + MAXE];
    for (int i = 0; i < MAXN + MAXE; i++){
        repr[i] = MAXN + MAXE;
    }

    // finding fours
    k = 0;
    static EDGE* list[4];
    static EDGE* list2[4];
    for (int i = 0; i < nv; i++){
        EDGE *e = first_edge[i];
        int last_degree = degree[i];
        for (int j = 0; j < last_degree; j++){
            my_ext4(e, list);
            
            repr[0] = MAXN + MAXE;
            my_testcanon_init_v3(first_edge[nv - 1], repr);
            my_testcanon_init_mirror_v3(first_edge[nv - 1], repr);
            my_testcanon_init_v3(first_edge[nv - 1]->next->next, repr);
            my_testcanon_init_mirror_v3(first_edge[nv - 1]->next->next, repr);
            
            int is_bad = 0;
            if (my_testcanon_init_v3(first_edge[nv-1]->next, repr) == 2){
                is_bad++;
            }
            else if (my_testcanon_init_mirror_v3(first_edge[nv-1]->next, repr) == 2){
                is_bad++;
            }
            else if (my_testcanon_init_v3(first_edge[nv-1]->prev, repr) == 2){
                is_bad++;
            }
            else if (my_testcanon_init_mirror_v3(first_edge[nv-1]->prev, repr) == 2){
                is_bad++;
            }

            if (!is_bad && is_vert_canon()){
                ext4[k] = e;
                k++;
            }
            my_reduce4(e, list);
            e = e->next;
        }
    }
    *num_ext4 = k;

    // finding fives
    k = 0;
    for (int i = 0; i < nv; i++){
        if (degree[i] > 3){
            EDGE *e = first_edge[i];
            int last_degree = degree[i];
            for (int j = 0; j < last_degree; j++){
                my_ext5(e, list);
                repr[0] = MAXN + MAXE;

                my_testcanon_init_v3(first_edge[nv - 1], repr);
                my_testcanon_init_mirror_v3(first_edge[nv - 1], repr);
                int is_bad = 0;
                EDGE *e2 = first_edge[nv - 1];

                for (int l = 0; l < 5; l++){
                    if (my_testcanon_init_v3(e2, repr) == 2){
                        is_bad++;
                    }
                    if (my_testcanon_init_mirror_v3(e2, repr) == 2){
                        is_bad++;
                    }
                    if (is_bad){
                        break;
                    }
                    e2 = e2->next;
                }

                if (!is_bad && is_vert_canon()){
                    ext5[k] = e;
                    k++;
                }
                my_reduce5(e, list);
                e = e->next;
            }
        }
    }
    *num_ext5 = k;
}

static int is_canon(){
    int repr[MAXN + MAXE];
    for (int i = 0; i < MAXN + MAXE; i++) repr[i] = MAXN + MAXE;

    EDGE *e = first_edge[nv - 1];
    for (int i = 0; i < degree[nv - 1]; i++){
        my_testcanon_init_v3(e, repr);
        my_testcanon_init_mirror_v3(e, repr);
        e = e->next;
    }

    for (int i = 0; i < nv; i++){
        e = first_edge[i];
        for (int j = 0; j < degree[i]; j++){
            int tc = my_testcanon_init_v3(e, repr);
            int tcm = my_testcanon_init_mirror_v3(e, repr);
            if (tcm > tc){
                tc = tcm;
            }
            if (tc){
                if (tc == 2){
                    return 0;
                }
            }
            e = e->next;
        }
    }

    return 1;
}

static void my_scan_simple(){
    if (nv >= input_n){
        write_graph6(stdout, 0);
        total_graphs++;
        return;
    }

    int num_ext3, num_ext4, num_ext5;
    EDGE *ext3[MAXN], *ext4[MAXN], *ext5[MAXN];
    my_find_extentions(ext3,&num_ext3,ext4,&num_ext4,ext5,&num_ext5);

    int i = 0;
    for (; i < num_ext3; i++){
        my_ext3(ext3[i]);
        if (is_canon())
            my_scan_simple();
        my_reduce3(ext3[i]);
        //*/
    }

    for (i = 0; i < num_ext4; i++){
        EDGE *list[2];
        my_ext4(ext4[i], list);
        if (is_canon())
            my_scan_simple();
        my_reduce4(ext4[i], list);
        //*/
    }

    for (i = 0; i < num_ext5; i++){
        EDGE *list[4];
        my_ext5(ext5[i], list);
        if (is_canon())
            my_scan_simple();
        my_reduce5(ext5[i], list);
        //*/
    }
}

int main(int argc, char* argv[]){
    input_n = getswitchvalue(argv[1]);
    
    if (input_n > MAXN || input_n < 4){
        printf("Invalid number of vertices");
        return -1;
    }

    init_k4();
    // testing my_ext5
    //my_ext3(first_edge[0]);

    my_scan_simple();

    printf("Total graphs foud: %d\n", total_graphs);
}