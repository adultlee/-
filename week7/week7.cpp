#include <iostream>

using namespace std;



void initNext(string pattern , int next[])
{
   next[0] = -1;
   int j =-1;
   for(int i =0  ; i< 8; i++ ,j++)
   {    
       next[i] = j;
       while(j>=0 && pattern[i] != pattern[j])
       {
           j = next[j];
       }
       
   }
}

void KPM(string pattern , string text ,int next[])
{   
 
    for(int i=0 ,j =0; i < text.length() && j<pattern.length(); ++i , ++j) // i 와 j 를 하나씩 증가시킨다. 
    { // j 란 현재 찾아야 하는 문자열의 index를 의미한다. 

        while(j>0 && pattern[j] != text[i]) 
        {   
            j = next[j]; // next[j]란 next 배열의 j 번째에서 틀린 경우 본 비교 문자열의 j번째 부터 비교하면 된다. 그전까진 괜춘
            
        }
        if(j == pattern.length()-1)
        {      
            cout <<"패턴이 발생한 위치"<< i - j  <<endl;
            j = next[j];
        }
    }
    cout << "탐색 종료" <<endl;
}

int main()
{
    int next1[8] = {0,};
    string pattern1 ="abababca";
    string text1 ="ababababcababababcaabbabababcaab";
    initNext(pattern1 , next1);

    cout << endl;
    KPM(pattern1,text1, next1);
    int next2[9] ={0,};
    string text2 = "This class is an algorithm design class. Therefore, students will have time to learn about algorithms and implement each algorithm themselves.";
    string pattern2 = "algorithm";
    
    initNext(pattern2 , next2);

    cout << endl;
    KPM(pattern2,text2, next2);
    

}