#pragma once
#include "../plantri.c"

static void testcanon_first_init(EDGE *givenedge, int representation[], int colour[]);

static int correct_neigh_degrees(int neigh[], int degree[], int dgr, int correct4, int correct5, int correct6){
    int fours = 0;
    int fives = 0;
    int sixes = 0;
    for (int i = 0; i < dgr; i++){
        fours += (degree[neigh[i]] >= 4);
        fives += (degree[neigh[i]] >= 5);
        sixes += (degree[neigh[i]] >= 6);
    }

    return fours >= correct4 && fives >= correct5 && sixes >= correct6;
}

static int priority_calculator(int code[], int num_v){
    // vertices are index from 1
    int al[num_v + 1][num_v-1];
    int dgr[num_v + 1];
    
    al[1][0] = 2;
    al[2][0] = 1;
    int curr = 1;
    int index = 0;
    int vert_disc = 2;
    while (curr <= num_v){
        int edge = 1;
        while (code[index] != 0){
            if (code[index] > num_v){
                vert_disc++;
                al[curr][edge] = vert_disc;
                al[vert_disc][0] = curr;
            }
            else {
                al[curr][edge] = code[index];
            }
            edge++;
            index++;
        }
        dgr[curr] = edge;
        curr++;
        index++;
    }

    for (int i = 1; i <= num_v; i++){
        if (dgr[i] == 4){
            int v1 = al[i][0];
            int v2 = al[i][1];
            int v3 = al[i][2];
            int v4 = al[i][3];

            // C
            if (dgr[v1] == 5 && dgr[v2] == 5 && dgr[v3] == 5 && dgr[v4] == 5){
                int correct = 0;
                for (int j = 0; j < 4; j++){
                    int act = al[i][j];
                    if(correct_neigh_degrees(al[act], dgr, 5, 5, 4, 0)){
                        correct++;
                    }
                    else {
                        break;
                    }
                }

                if (correct == 4){
                    return 2;
                }
            }

            int fives = 0;
            for (int j = 0; j < 4; j++){
                if (dgr[al[i][j]] == 5){
                    fives++;
                }
            }

            // D
            if (fives == 3){
                int neigh_six = -1;
                for (int j = 0; j < dgr[i]; j++){
                    if (dgr[al[i][j]] >= 6){
                        neigh_six = j;
                        break;
                    }
                }
                if (neigh_six != -1){
                    int five1 = al[i][(neigh_six + 1) % dgr[i]];
                    int five2 = al[i][(neigh_six + 2) % dgr[i]];
                    int five3 = al[i][(neigh_six + 3) % dgr[i]];
                    
                    if (correct_neigh_degrees(al[five2], dgr, 5, 5, 4, 0)
                    && correct_neigh_degrees(al[five1], dgr, 5, 5, 3, 1)
                    && correct_neigh_degrees(al[five3], dgr, 5, 5, 3, 1)){
                        return 3;
                    }
                }
            }

            // E & F
            if (fives == 2){
                if (correct_neigh_degrees(al[i], dgr, 4, 4, 4, 2)){
                    int five1 = -1;
                    int five2 = -1;
                    int five3 = -2;
                    for (int j = 0; j < 4; j++){
                        if (dgr[al[i][j]] == 5 && dgr[al[i][(j + 1) % dgr[i]]] == 5){
                            five1 = al[i][j];
                            five2 = al[i][(j + 1) % dgr[i]];
                            break;
                        }
                    }

                    if (five1 != -1){
                        for (int j = 0; j < 5; j++){
                            if (al[five1][j] == five2){
                                five3 = -1;
                                if (dgr[al[five1][(j + 1) % 5]] == 5){
                                    five3 = al[five1][(j + 1) % 5];
                                }
                                else if (dgr[al[five1][(j + 4) % 5]] == 5){
                                    five3 = al[five1][(j + 4) % 5];
                                }
                                break;
                            }
                        }
                    }

                    // E
                    if (five3 >= 0){
                        if (correct_neigh_degrees(al[five3], dgr, 5, 5, 3, 0)){
                            if (correct_neigh_degrees(al[five1], dgr, 5, 5, 4, 1)
                            && correct_neigh_degrees(al[five2], dgr, 5, 5, 3, 1)){
                                return 4;
                            }

                            if (correct_neigh_degrees(al[five2], dgr, 5, 5, 4, 1)
                            && correct_neigh_degrees(al[five1], dgr, 5, 5, 3, 1)){
                                return 4;
                            }
                        }
                    }

                    // F
                    else if (five3 == -1){
                        if (correct_neigh_degrees(al[five1], dgr, 5, 5, 3, 2)
                        && correct_neigh_degrees(al[five2], dgr, 5, 5, 3, 2)){
                            return 5;
                        }
                    }
                }
            }

            // G
            if (dgr[v1] >= 5 && dgr[v3] >= 5 && dgr[v2] >= 6 && dgr[v4] >= 6){
                return 6;
            }
            if (dgr[v2] >= 5 && dgr[v4] >= 5 && dgr[v1] >= 6 && dgr[v3] >= 6){
                return 6;
            }
        }

        if (dgr[i] == 5){
            // A
            if (correct_neigh_degrees(al[i], dgr, 5, 5, 3, 1)){
                int five1 = -1;
                int four1 = -1;
                int four2 = -1;
                for (int j = 0; j < 5; j++){
                    if (dgr[al[i][j]] == 5){
                        if (dgr[al[i][(j + 1) % 5]] == 4){
                            if (dgr[al[i][(j + 4) % 5]] == 4){
                                four1 = al[i][(j + 1) % 5];
                                four2 = al[i][(j + 4) % 5];
                                five1 = al[i][j];
                            }
                        }
                    }
                }
                
                if (five1 != -1){
                    int five2 = -1;
                    for (int j = 0; j < 5; j++){
                        if (dgr[al[i][j]] == 5){
                            if (al[i][j] != five1){
                                five2 = al[i][j];
                            }
                        }
                    }

                    if (five2 != -1){
                        // if five1 is found there must be 2 vertices with degree 4
                        if (correct_neigh_degrees(al[four1], dgr, 4, 4, 4, 1)
                        && correct_neigh_degrees(al[four2], dgr, 4, 4, 4, 1)){
                            if (correct_neigh_degrees(al[five1], dgr, 5, 5, 3, 1)
                            && correct_neigh_degrees(al[five2], dgr, 5, 5, 3, 2)){
                                return 0;
                            }
                        }
                    }
                }
            }

            // B
            if (correct_neigh_degrees(al[i], dgr, 5, 5, 3, 2)){
                int five1 = -1;
                int four1 = -1;
                int four2 = -1;
                for (int j = 0; j < 5; j++){
                    if (dgr[al[i][j]] == 5){
                        if (dgr[al[i][(j + 1) % 5]] == 4){
                            if (dgr[al[i][(j + 4) % 5]] == 4){
                                four1 = al[i][(j + 1) % 5];
                                four2 = al[i][(j + 4) % 5];
                                five1 = al[i][j];
                            }
                        }
                    }
                }
                if (five1 != -1){
                    // if five1 is found there must be 2 vertices with degrees 4
                    if (correct_neigh_degrees(al[four1], dgr, 4, 4, 4, 2)
                    && correct_neigh_degrees(al[four2], dgr, 4, 4, 4, 2)){
                        if (correct_neigh_degrees(al[five1], dgr, 5, 5, 3, 2)){
                            return 1;
                        }
                    }
                }
            }

            // H
            if (correct_neigh_degrees(al[i], dgr, 5, 5, 5, 0)){
                return 7;
            }
        }
    }

    return -1;
}

#define FILTER gadgets_priority

static int gadgets_priority(int nbtot, int nbop, int doflip){
    // create code
    int representation[MAXE];

    int rcolour[nv];
    for (int i = 0; i < nv; i++) rcolour[i] = MAXN + degree[i] + i;

    testcanon_first_init(firstedge[0], representation, rcolour);

    int res = priority_calculator(representation, nv);
    if (res >= 0){
        printf("gadget: %d\n", res);
        return TRUE;
    }

    return FALSE;
}