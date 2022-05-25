#include <iostream>

using namespace std;

int main()
{
    int gem[10][2]; // 보석을 담는 배열입니다. 0번째는 무게를, 1번째에는 가치를 담습니다.
    int dp[10][101] = {0,}; // dp[i][j] 라고 할 때 i 번째의 물건을 가지고 j만큼의 무게를 담을 때 가장 큰 값을 저장합니다.
    // 
    // 문제 1
    int bag_weight = 15; //현재 배낭에서 담을 수 있는 최대 무게를 의미합니다.
    //  (5, 5), (10, 7), (7, 10), (3, 6), (4, 8), (11, 20)
    gem[1][0] = 5;     gem[1][1] = 5;
    gem[2][0] = 10;    gem[2][1] = 7;
    gem[3][0] = 7;     gem[3][1] = 10;
    gem[4][0] = 3;     gem[4][1] = 6;
    gem[5][0] = 4;     gem[5][1] = 8;
    gem[6][0] = 11;    gem[6][1] = 20;

    for (int i = 1 ; i <= 6 ; i++){ // 물건의 개수를 늘려가면서 1개의 물건, 6개의 물건까지를 다룰때까지 증가 시킴니다.
        for (int weight = 0 ; weight <= bag_weight ; weight++){ // 현재 담을수 있는 무게 인 w 를 키웁니다.
            if (gem[i][0] <= weight){  // 현재 담을 수 있는 weight 를 평가 할때 보석의 무게를 확인합니다. true 라면 추가 할 수 있습니다.
                // 추가 할 수 있는 경우 보석을 더해줘서 가지는 value(이 경우 이전의 합을 제거합니다.) 와 보석을 넣지 않은 상태의  value 를 비교합니다. 
                dp[i][weight] = max(  dp[i-1][weight-gem[i][0]]  + gem[i][1], dp[i-1][weight]);
            }
            else{ // dp[i][weight]는 이전값을 그대로 가져옵니다. 추가할 수 없는 경우
                dp[i][weight] = dp[i-1][weight];
            }
        }
    }
    cout << endl;
    cout << "입력1 에 대하여 가방에 담은 보석의 최대 가치: " << dp[6][15] << endl;

    // 문제 2

    gem[10][101] = {0 , };
    dp[10][101] = {0,};
    
    bag_weight = 30;
    //  (3, 5), (7, 7), (8, 10), (5, 6), (6, 8), (13, 20), (11, 18), (2, 5)
    gem[1][0] = 3;     gem[1][1] = 5;
    gem[2][0] = 7;     gem[2][1] = 7;
    gem[3][0] = 8;     gem[3][1] = 10;
    gem[4][0] = 5;     gem[4][1] = 6;
    gem[5][0] = 6;     gem[5][1] = 8;
    gem[6][0] = 13;    gem[6][1] = 20;
    gem[7][0] = 11;    gem[7][1] = 18;
    gem[8][0] = 2;     gem[8][1] = 5;

    for (int i = 1 ; i <= 8 ; i++){
        for (int weight = 0 ; weight <= bag_weight ; weight++){
            if (gem[i][0] <= weight){ 
                dp[i][weight] = max(  dp[i-1][weight-gem[i][0]]  + gem[i][1], dp[i-1][weight]);
            }
            else{
                dp[i][weight] = dp[i-1][weight];
            }
        }
    }
    cout << "입력2 에 대하여 가방에 담은 보석의 최대 가치: " << dp[8][30] << endl;

}