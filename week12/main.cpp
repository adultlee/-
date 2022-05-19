#include <iostream>    

using namespace std;

void path(int P[6][6], int q, int r) {
    if (P[q][r] != 0) {
        path(P, q, P[q][r]);
        cout << "v" << P[q][r] << " -> ";
        path(P, P[q][r], r);
    }
}

void floyd2(int W[6][6], int D[6][6], int P[6][6], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            P[i][j] = 0;
            D[i][j] = W[i][j];
        }
    }

    for (int k = 1; k < n; k++) {
        for (int i = 1; i < n; i++) { 
            for (int j = 1; j < n; j++) {
                if (D[i][j] > (D[i][k] + D[k][j])) { // D의 의미는 현재 i -> j까지 이동하며 발생하는 최소 비용을 의미합니다.
                    P[i][j] = k;                     // 현 시점에서 가장 큰 교차하는 인덱스를 의미합니다. 
                    D[i][j] = D[i][k] + D[k][j];     // 현재 보다 더 적은 최소비용을 확인해서 초기화해줍니다.   
                }
            }
        }
    }
}

int main() {

    int W[6][6] = {0,};
    int D[6][6] = {0,};
    int P[6][6] = {0,};

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            W[i][j] = 10000;
        }
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (i == j)
            {
                W[i][j] = 0;
            } 

        }
    }

    W[1][2] = 1;
    W[1][4] = 1;    
    W[1][5] = 5;   
    W[2][1] = 9;    
    W[2][3] = 3;     
    W[2][4] = 2;    
    W[3][4] = 4;   
    W[4][3] = 2;    
    W[4][5] = 3;    
    W[5][1] = 3;

    cout << "W[i][j] is " << endl;;
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) cout <<  W[i][j] << " ";
        cout <<endl;
    }
    floyd2(W, D, P, 6);
    cout << endl;

    cout << "D[i][j] is "<< endl;;
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) cout << D[i][j] << " ";
          cout <<endl;
    }
    cout << endl;

    cout << "P[i][j] is "<< endl;;
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) cout << P[i][j] << " ";
          cout <<endl;
    }
    cout <<endl;

    cout << "The shortest path(5,3) is v5 -> ";
    path(P, 5, 3);
    cout << "v3"<< endl;

    cout << "The shortest path(2,5) is v2 -> ";
    path(P, 2, 5);
    cout << "v5"<< endl;

    cout << "The shortest path(1,3) is v1 -> ";
    path(P, 1, 3);
    cout << "v3" << endl;
    

    return 0;
}