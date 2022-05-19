#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;
void BoyerMoore(string txt, string pattern);
// 보이어-무어 알고리즘

int main(void)
{           //12171820 이성인
        string txt="";
        string line;
	    ifstream file("txt.txt"); // txt.txt 파일을 연다. 없으면 생성. 
	    if(file.is_open()){
	    	while(getline(file, line)) {
	    		txt+=line;
	    	}
	    	file.close(); //  파일을 닫는다. 
	    } else {
	    	cout << "Unable to open file";
	    	return 1;
	    }
    //12171820 이성인
        string pattern = "letter \"A\"..\"Z\"";
        BoyerMoore(txt, pattern); 
        
    return 0;
}

void BoyerMoore(string txt, string pattern){//12171820 이성인
    int txtLen = txt.length(); // 길이를 받습니다.
    int patternLen = pattern.length(); // 길이를 받습니다.
    int skip[256] = { -1, }; // 모든 배열을 -1로 초기화한다
    for(int i=0 ; i<patternLen ; i++)
    {
        skip[(int)pattern[i]] = i; // map과 유사하게 사용하는 경우입니다.
        // (int)pattern[i]에 해당하는 값을 받아서 그 문자를 찾으며 동시에 초기화 시킵니다.
        // 초기화 된 값을 skip을 통해서 이동합니다.
    }

    int s = 0, j; // s는 text에 대한 patterntern의 이동값
    //j는 현재 위치에서 이동하는 것을 의미
    //12171820 이성인
    while(txtLen-patternLen >s){
        j = patternLen-1;

        while(pattern[j] == txt[s+j] && j >= 0 )
        j--; // patterntern의 문자와 text가 매칭하면 j를 줄여 틀릴때까지 이동합니다.
             //  문자를 찾는다
        if(j < 0) // 문자열이 일치하였을 때
        {
            cout << "patterntern's index : " << s <<endl;
            s += (s>=txtLen-patternLen)? 1: patternLen-skip[(int)txt[s+patternLen]] ;
        }
        else{ // 문자열이 일치 하지 않았다면 이동합니다.
            s += max(1, j-skip[(int)txt[s+j]]); // 본문의 s 의 이동과 같습니다. if(M-j > k)를 비교하여 이동하는 내용
        }//12171820 이성인
    }
}