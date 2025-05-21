#include <iostream>
#include <string>

using namespace std;

int main(){
    int num;
    cin >> num;
    int matrix[num][num];
    for (int i = 0; i < num; i++){
        for (int j = 0; j < num; j++){
            matrix[i][j] = 0;
        }
    }

    string str;
    cin >> str;
    int vert = 0;
    for (char c: str){
        if (c == ','){
            vert++;
        }
        else {
            matrix[vert][c - 'a'] = 1;
        }
    }

    for (int i = 0; i < num; i++){
        for (int j = 0; j < num; j++){
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}