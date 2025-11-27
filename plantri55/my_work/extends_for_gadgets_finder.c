#pragma once
#include "../plantri.c"

static void
write_graph6(FILE *f, int doflip);

static void extend_a(EDGE *e, EDGE *list[]);
static void reduce_a(EDGE *e, EDGE *list[]);

static void extend_b(EDGE *e, EDGE *list[]);
static void reduce_b(EDGE *e, EDGE *list[]);

static void extend_c(EDGE *e, EDGE *list[]);
static void reduce_c(EDGE *e, EDGE *list[]);

static void extend_d(EDGE *e, EDGE *list[]);
static void reduce_d(EDGE *e, EDGE *list[]);

static void extend_e(EDGE *e, EDGE *list[]);
static void reduce_e(EDGE *e, EDGE *list[]);

static void extend_e_mirror(EDGE *e, EDGE *list[]);
static void reduce_e_mirror(EDGE *e, EDGE *list[]);

static void extend_f(EDGE *e, EDGE *list[]);
static void reduce_f(EDGE *e, EDGE *list[]);

static void extend_g(EDGE *e, EDGE *list[]);
static void reduce_g(EDGE *e, EDGE *list[]);

static void extend_h(EDGE *e, EDGE *list[]);
static void reduce_h(EDGE *e, EDGE *list[]);

static void rep_printer(int code[], int num_v){
    int index = 0;
    int num_vert = 0;
    while(num_vert < num_v){
        fprintf(outfile, "%d ", code[index]);
        if (code[index] == 0){
            num_vert++;
        }
        index++;
    }
    fprintf(outfile, "\n");
}
// some of the check can be skipped in real use
int is_valid_extend_a(EDGE *e){
    int is_good = 1;
    if (degree[e->start] != 4){
        is_good = 0;
    }
    if (degree[e->end] != 5){
        is_good = 0;
    }
    if (degree[e->next->end] != 5){
        is_good = 0;
    }
    if (degree[e->next->next->end] < 5){
        is_good = 0;
    }
    if (degree[e->prev->end] < 5){
        is_good = 0;
    }
    if (degree[e->invers->prev->prev->end] != 4){
        is_good = 0;
    }

    EDGE *helper = e->invers->prev->prev->invers;
    if (degree[helper->next->end] < 5){
        is_good = 0;
    }
    if (degree[helper->next->next->end] < 5){
        is_good = 0;
    }

    return is_good;
}

// some of the check can be skipped in real use
int is_valid_extend_b(EDGE *e){
    int is_good = 1;
    if (degree[e->start] != 4){
        is_good = 0;
    }
    if (degree[e->end] < 5){
        is_good = 0;
    }
    if (degree[e->next->end] < 5){
        is_good = 0;
    }
    if (degree[e->next->next->end] < 5){
        is_good = 0;
    }
    if (degree[e->prev->end] < 5){
        is_good = 0;
    }
    
    return is_good;
}

// some of the check can be skipped in real use
int is_valid_extend_c(EDGE *e){
    int is_good = 1;
    if (degree[e->start] != 5){
        is_good = 0;
    }
    if (degree[e->end] != 4){
        is_good = 0;
    }
    if (degree[e->next->end] != 5){
        is_good = 0;
    }
    if (degree[e->next->next->end] != 4){
        is_good = 0;
    }
    if (degree[e->prev->end] < 5){
        is_good = 0;
    }
    if (degree[e->prev->prev->end] < 5){
        is_good = 0;
    }

    EDGE *helper = e->next->invers->next->next;
    if (degree[helper->end] < 5){
        is_good = 0;
    }
    if (degree[helper->next->end] < 5){
        is_good = 0;
    }
    
    return is_good;
}

// some of the check can be skipped in real use
int is_valid_extend_d(EDGE *e){
    int is_good = 1;
    if (degree[e->start] != 4){
        is_good = 0;
    }
    if (degree[e->end] != 5){
        is_good = 0;
    }
    if (degree[e->next->end] != 5){
        is_good = 0;
    }
    if (degree[e->next->next->end] < 5){
        is_good = 0;
    }
    if (degree[e->prev->end] < 5){
        is_good = 0;
    }

    EDGE *helper = e->invers->next->next;
    if (degree[helper->end] < 4){
        is_good = 0;
    }
    if(degree[helper->next->end] < 5){
        is_good = 0;
    }
    if(degree[helper->next->invers->prev->prev->end] < 4){
        is_good = 0;
    }
    
    return is_good;
}

// some of the check can be skipped in real use
int is_valid_extend_e(EDGE *e){
    int is_good = 1;
    if (degree[e->start] != 4){
        is_good = 0;
    }
    if (degree[e->end] != 5){
        is_good = 0;
    }
    if (degree[e->next->end] != 5){
        is_good = 0;
    }
    if (degree[e->next->next->end] < 6){
        is_good = 0;
    }
    if (degree[e->prev->end] < 5){
        is_good = 0;
    }

    EDGE *helper = e->invers->next->next;
    if (degree[helper->end] < 4){
        is_good = 0;
    }
    if (degree[helper->next->end] < 4){
        is_good = 0;
    }
    if (degree[helper->end] == 4 && degree[helper->next->end] == 4){
        is_good = 0;
    }

    if (degree[e->next->invers->prev->prev->end] < 5){
        is_good = 0;
    }

    return is_good;
}

int is_valid_extend_e_mirror(EDGE *e){
    int is_good = 1;
    if (degree[e->start] != 4){
        is_good = 0;
    }
    if (degree[e->end] != 5){
        is_good = 0;
    }
    if (degree[e->prev->end] != 5){
        is_good = 0;
    }
    if (degree[e->prev->prev->end] < 6){
        is_good = 0;
    }
    if (degree[e->next->end] < 5){
        is_good = 0;
    }

    EDGE *helper = e->invers->prev->prev;
    if (degree[helper->end] < 4){
        is_good = 0;
    }
    if (degree[helper->prev->end] < 4){
        is_good = 0;
    }
    if (degree[helper->end] == 4 && degree[helper->prev->end] == 4){
        is_good = 0;
    }

    if (degree[e->prev->invers->next->next->end] < 5){
        is_good = 0;
    }

    return is_good;
}

// some of the check can be skipped in real use
int is_valid_extend_f(EDGE *e){
    int is_good = 1;
    if (degree[e->start] != 5){
        is_good = 0;
    }
    if (degree[e->end] < 5){
        is_good = 0;
    }
    if (degree[e->next->end] < 4){
        is_good = 0;
    }
    if (degree[e->next->next->end] < 5){
        is_good = 0;
    }
    if (degree[e->prev->end] < 4){
        is_good = 0;
    }
    if (degree[e->prev->prev->end] < 5){
        is_good = 0;
    }

    return is_good;
}

// some of the check can be skipped in real use
int is_valid_extend_g(EDGE *e){
    int is_good = 1;
    if (degree[e->start] < 5){
        is_good = 0;
    }
    if (degree[e->end] < 5){
        is_good = 0;
    }
    if (degree[e->next->end] < 5){
        is_good = 0;
    }
    if (degree[e->next->next->end] < 5){
        is_good = 0;
    }
    
    return is_good;
}

// some of the check can be skipped in real use
int is_valid_extend_h(EDGE *e){
    int is_good = 1;
    if (degree[e->start] < 6){
        is_good = 0;
    }
    if (degree[e->end] < 4){
        is_good = 0;
    }
    if (degree[e->next->end] < 5){
        is_good = 0;
    }
    if (degree[e->next->next->end] < 5){
        is_good = 0;
    }
    if (degree[e->next->next->next->end] < 4){
        is_good = 0;
    }

    return is_good;
}

static void find_gadgets_extensions(
    EDGE *ext_a[], int* numexta,
    EDGE *ext_b[], int* numextb,
    EDGE *ext_c[], int* numextc,
    EDGE *ext_d[], int* numextd,
    EDGE *ext_e[], int* numexte,
    EDGE *ext_em[], int *numextem,
    EDGE *ext_f[], int* numextf,
    EDGE *ext_g[], int* numextg,
    EDGE *ext_h[], int* numexth
){
    int ka = 0;
    int kb = 0;
    int kc = 0;
    int kd = 0;
    int ke = 0;
    int kem = 0;
    int kf = 0;
    int kg = 0;
    int kh = 0;
    EDGE *helper;
    for (int i = 0; i < nv; i++){
        helper = firstedge[i];
        for (int j = 0; j < degree[i]; j++){
            if (is_valid_extend_a(helper)){
                ext_a[ka] = helper;
                ka++;
            }

            if (is_valid_extend_b(helper)){
                ext_b[kb] = helper;
                kb++;
            }

            if (is_valid_extend_c(helper)){
                ext_c[kc] = helper;
                kc++;
            }

            if (is_valid_extend_d(helper)){
                ext_d[kd] = helper;
                kd++;
            }

            if (is_valid_extend_e(helper)){
                ext_e[ke] = helper;
                ke++;
            }

            if (is_valid_extend_e_mirror(helper)){
                ext_em[kem] = helper;
                kem++;
            }

            if (is_valid_extend_f(helper)){
                ext_f[kf] = helper;
                kf++;
            }
            
            if (is_valid_extend_g(helper)){
                ext_g[kg] = helper;
                kg++;
            }

            if (is_valid_extend_h(helper)){
                ext_h[kh] = helper;
                kh++;
            }
            helper = helper->next;
        }
    }

    *numexta = ka;
    *numextb = kb;
    *numextc = kc;
    *numextd = kd;
    *numexte = ke;
    *numextem = kem;
    *numextf = kf;
    *numextg = kg;
    *numexth = kh;
}

#define FILTER extends_for_gadgets_finder

static int extends_for_gadgets_finder(int nbtot, int nbop, int doflip){
    EDGE *ext_a[ne];
    EDGE *ext_b[ne];
    EDGE *ext_c[ne];
    EDGE *ext_d[ne];
    EDGE *ext_e[ne];
    EDGE *ext_em[ne];
    EDGE *ext_f[ne];
    EDGE *ext_g[ne];
    EDGE *ext_h[ne];
    
    int numexta, numextb, numextc, numextd, numexte, numextem, numextf, numextg, numexth;
    find_gadgets_extensions(
        ext_a, &numexta,
        ext_b, &numextb,
        ext_c, &numextc,
        ext_d, &numextd,
        ext_e, &numexte,
        ext_em, &numextem,
        ext_f, &numextf,
        ext_g, &numextg,
        ext_h, &numexth
    );

    EDGE *list[4];
    
    /*
    fprintf(outfile, "extend_a: \n");
    for (int i = 0; i < numexta; i++){
        write_graph6(outfile, 0);
        extend_a(ext_a[i], list);
        write_graph6(outfile, 0);

        reduce_a(ext_a[i], list);
        write_graph6(outfile, 0);
    }

    fprintf(outfile, "extend_b: \n");
    for (int i = 0; i < numextb; i++){
        write_graph6(outfile, 0);
        extend_b(ext_b[i], list);
        write_graph6(outfile, 0);

        reduce_b(ext_b[i], list);
        write_graph6(outfile, 0);
    }
    */

    /*
    fprintf(outfile, "extend_c: \n");
    for (int i = 0; i < numextc; i++){
        write_graph6(outfile, 0);
        extend_c(ext_c[i], list);
        write_graph6(outfile, 0);

        reduce_c(ext_c[i], list);
        write_graph6(outfile, 0);
    }

    fprintf(outfile, "extend_d: \n");
    for (int i = 0; i < numextd; i++){
        write_graph6(outfile, 0);
        extend_d(ext_d[i], list);
        write_graph6(outfile, 0);

        reduce_d(ext_d[i], list);
        write_graph6(outfile, 0);
    }*/

    fprintf(outfile, "extend_e: \n");
    for (int i = 0; i < numexte; i++){
        write_graph6(outfile, 0);
        extend_e(ext_e[i], list);
        write_graph6(outfile, 0);

        reduce_e(ext_e[i], list);
        write_graph6(outfile, 0);
    }

    fprintf(outfile, "extend_em: \n");
    for (int i = 0; i < numextem; i++){
        write_graph6(outfile, 0);
        extend_e_mirror(ext_em[i], list);
        write_graph6(outfile, 0);

        reduce_e_mirror(ext_em[i], list);
        write_graph6(outfile, 0);
    }

    /*
    fprintf(outfile, "extend_f: \n");
    for (int i = 0; i < numextf; i++){
        write_graph6(outfile, 0);
        extend_f(ext_f[i], list);
        write_graph6(outfile, 0);

        reduce_f(ext_f[i], list);
        write_graph6(outfile, 0);
    }

    fprintf(outfile, "extend_g: \n");
    for (int i = 0; i < numextg; i++){
        write_graph6(outfile, 0);
        extend_g(ext_g[i], list);
        write_graph6(outfile, 0);

        reduce_g(ext_g[i], list);
        write_graph6(outfile, 0);
    }

    fprintf(outfile, "extend_h: \n");
    for (int i = 0; i < numexth; i++){
        write_graph6(outfile, 0);
        extend_h(ext_h[i], list);
        write_graph6(outfile, 0);

        reduce_h(ext_h[i], list);
        write_graph6(outfile, 0);
    }
    //*/

    return (numexte + numextem) > 0;
}