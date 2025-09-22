#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main(){
    // cout << "Vertices are numbered from 0 \n";
    int n;
    // cout << "Insert number of vertices: ";
    cin >> n;
    vector<vector<int>> neigh(n);

    int m = 0;
    for (int i = 0; i < n; i++){
        // cout << "Insert neighbours of " << i << ". vertex (end with -1, insert them in clockwise order): ";
        int h;
        cin >> h;
        while (h >= 0){
            neigh[i].push_back(h);
            m++;
            cin >> h;
        }
    }
    int cannon_vertex = n + 1;
    int cannon_edge = m + 1;
    vector<int> real_cannon_code(2 * m + n + 1, 2 * n + 1);
    // iterate over all begining verticec

    for (int v = 0; v < n; v++){
        for (int e = 0; e < neigh[v].size(); e++){
            // colour of vertex v
            // if some vertex does not have colour, it was discovered by that edge
            vector<int> colour(n, -1);
            colour[v] = n + 1;

            // label[i] is which vertex whas discovered i-th
            vector<int> label(1);
            label.push_back(v);

            // first edge of i-th vertex
            vector<int> first_edge(n);
            first_edge[v] = e;

            // final canonical code
            vector<int> cannon_code;
            cannon_code.push_back(colour[v]);

            for (int i = 1; i <= n; i++){
                int curr = label[i];
                int size = neigh[curr].size();
                int fe = first_edge[curr];
                for (int j = 0; j < size; j++){
                    int next = neigh[curr][(fe + j)%size];
                    if (colour[next] == -1){
                        colour[next] = n + label.size();
                        label.push_back(next);
                        cannon_code.push_back(colour[next]);
                        for (int k = 0; k < neigh[next].size(); k++){
                            if (neigh[next][k] == curr){
                                first_edge[next] = k;
                                break;
                            }
                        }
                    }
                    else {
                        cannon_code.push_back(colour[next] - n);
                    }
                }
                cannon_code.push_back(0);
            }
            cout << "vertex: " << v << " edge: " << e << " (";
            cout << cannon_code[0];
            for (int i = 1; i < cannon_code.size(); i++){
                cout << "," << cannon_code[i];
            }
            cout << ")\n";
            for (int i = 0; i < cannon_code.size(); i++){
                if (real_cannon_code[i] < cannon_code[i]){
                    break;
                }

                if (cannon_code[i] < real_cannon_code[i]){
                    cannon_vertex = v;
                    cannon_edge = e;
                    real_cannon_code = cannon_code;
                }
            }
        }
    }

    cout << "cannon vertex: " << cannon_vertex << "\n";
    cout << "cannon edge: " << cannon_edge << "\n";

    cout << "cannon code: ";
    cout << "(";
    cout << real_cannon_code[0];
    for (int i = 1; i < real_cannon_code.size(); i++){
        cout << "," << real_cannon_code[i];
    }
    cout << ")\n";
}