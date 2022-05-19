#include <iostream>
#include <cmath>
using namespace std;
 
int main()
{
    int arr[8][9] = {
        {3,4,9,-2,2,51,-23,2,-1},{223,7,8,-11,5,-99,2,3,-4}, {2,51,-23,-23,6,3,2,4,5},{5,-99,2,-1,32,2,5,-99,2},{6,3,3,-4,2,-1,6,3,3},{32,2,4,5,3,-4,2,-1,4},{4,4,23,6,2,-1,3,-4,34},{78,32,1,7,3,-4,-23,-23,6}
    };
    cout << arr << endl;
    int dp[8][9];
    dp[0][0] = 3;
    dp[0][1] = 4;
    dp[0][2] = 9;
    dp[0][3] = -2;
    dp[0][4] = 2;
    dp[0][5] = 51;
    dp[0][6] = -23;
    dp[0][7] = 2;
    dp[0][8] = -1;

    for(int i =1; i < 8;i++) // 행의 이동 (아래로)
    {
        for(int j =0; j < 9; j++) // 열의 이동 ->>
        {
            if(j==0)
            {   
                dp[i][0] = arr[i][0] + max( dp[i-1][0] , dp[i-1][1]);
            }
            else if(j == 8)
            {
                dp[i][8] = arr[i][8] + max( dp[i-1][7] , dp[i-1][8]);
            }
            else{
                dp[i][j] = arr[i][j] + max(dp[i-1][j-1],max(dp[i-1][j],dp[i-1][j+1]));
            }
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    int tempMax =0;
    int maxIndex ;
    for(int i=0; i <10; i++)
    {
        if(tempMax < dp[7][i])
     {
            tempMax = dp[7][i];
            maxIndex = i;
        }

    }
    cout << "가장 큰 값은 마지막줄의" <<maxIndex <<" 번째 index를 가진 " <<dp[7][maxIndex] << endl;

    int tempMaxIndex = maxIndex;
    int answer[8];
    answer[7] = arr[7][maxIndex];
    for(int i = 6 ; i > -1; i--)
    {
        if(tempMaxIndex ==0)
        {
            if(dp[i][0] <= dp[i][1])
            {
                answer[i] = arr[i][1]; // 1이 더 크다
                tempMaxIndex = 1;
            }
            else{
                answer[i] = arr[i][0]; // 0 이 더 크다
                tempMaxIndex = 0;
            }
        }
        else if(tempMaxIndex == 8)
        {
            if(dp[i][7] <= dp[i][8])
            {
                answer[i] = arr[i][8]; // 8이 더 크다
                tempMaxIndex = 8;
            }
            else{
                answer[i] = arr[i][7]; // 7이 더크다
                tempMaxIndex = 7;
            }
        }
        else{
            if(dp[i][tempMaxIndex -1] <= dp[i][tempMaxIndex+1] && dp[i][tempMaxIndex] <= dp[i][tempMaxIndex+1])
            {
                answer[i] = arr[i][tempMaxIndex+1]; // 3번째가 가장 크다
                tempMaxIndex = tempMaxIndex+1;
            }
            else if(dp[i][tempMaxIndex -1] <= dp[i][tempMaxIndex] && dp[i][tempMaxIndex+1] <= dp[i][tempMaxIndex])
            {
                answer[i] = arr[i][tempMaxIndex]; // 2번째가 가장 크다
                tempMaxIndex = tempMaxIndex;
            }
            else if(dp[i][tempMaxIndex] <= dp[i][tempMaxIndex-1] && dp[i][tempMaxIndex+1] <= dp[i][tempMaxIndex-1])
            {
                answer[i] = arr[i][tempMaxIndex-1]; // 1번째가 가장 크다
                tempMaxIndex = tempMaxIndex-1;
            }
        }
    }
    cout << "arr의 최적의 순서 입니다."<<endl;
    for(int i=0; i < 8; i++)
    {
        cout << i<<"번째 행은 : " << answer[i] << endl;
    }
}