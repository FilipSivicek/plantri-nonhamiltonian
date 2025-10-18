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

static void edge_printer(EDGE *e){
    printf("start = %d, end = %d\n", e->start, e->end);
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

    nv = 4;
    ne = 12;
    return;
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
          { vertex = run->end;
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
    unsigned char code[MAXN+MAXE+1];

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
    startedge[1] = givenedge->invers;

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
    startedge[1] = givenedge->invers;

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

static void my_scan_simple(){
    if (nv == input_n){
        write_graph6(stdout, 0);
        total_graphs++;
        return;
    }

    int num_ext3, num_ext4, num_ext5;
    EDGE *ext3[MAXN], *ext4[MAXN], *ext5[MAXN];
    // find_extentions(ext3,&num_ext3,ext4,&num_ext4,ext5,&num_ext5)

    for (int i = 0; i < num_ext3; i++){
        /*
        my_ext3(ext3[i]);
        if (is_canon()){
            my_scan_simple();
        }
        my_reduce3(ext[i]);
        */
    }

    for (int i = 0; i < num_ext4; i++){
        /*
        EDGE *list[2];
        my_ext4(ext4[i], list);
        if (is_canon()){
            my_scan_simple();
        }
        my_reduce4(ext[i], list);
        */
    }

    for (int i = 0; i < num_ext5; i++){
        /*
        EDGE *list[4];
        my_ext5(ext5[i], list);
        if (is_canon()){
            my_scan_simple();
        }
        my_reduce5(ext[i], list);
        */
    }
}

int main(int argc, char* argv[]){
    input_n = getswitchvalue(argv[1]);
    printf("%d\n", input_n);

    if (input_n > MAXN || input_n < 4){
        printf("Invalid number of vertices");
        return -1;
    }

    init_k4();

    my_scan_simple();

    printf("Total graphs foud: %d\n", total_graphs);
}