#include <iostream>
#include <cstring>
#include <vector>
#include <wchar.h>

using namespace std;

    string source;
    string target;
    float costs[3] = { 0.7, 0.5, 0.3 }; 
    void LD(int col, int row);


void LDA(int col, int row)
{
     double path[101][101] = {0.0,};
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
            if( i == 0){
                path[i][j] = 1 * j; 
            }
            else if(j == 0)
            {
                path[i][j] = 1 * i; 
            }
            else{
            double cost = 0.0;
			if (source[j - 1] == target[i - 1]) {
				path[i][j] = path[i - 1][j - 1];
				cost = 0;
			    path[i][j] = min( path[i - 1][j - 1]  , min(path[i][j - 1] + 1, path[i - 1][j] + 1));

			}
			else {
			    path[i][j] = min( path[i - 1][j - 1] + 1 , min(path[i][j - 1] + 1, path[i - 1][j] + 1));

			}
            }
            cout << path[i][j] << "\t";
            
		}
		cout << endl;
	}
	int r = row - 1;
	int c = col - 1;
	vector <double> stack; 
	for(;;){
        if (r == 0 && c == 0) break;

		if (path[r][c] == path[r - 1][c] + 1) {
			stack.push_back(1 + 100);
			r--;
		}
		else if (path[r][c] == path[r - 1][c - 1] + 1) {
			stack.push_back(1 + 101);
			r--; c--;
		}
		else if (path[r][c] == path[r][c - 1] + 1) {
			stack.push_back(1 + 102);
			c--;
		}
		else {
			r--;
			c--;
		}
	}
	while (!stack.empty()) {
		if (stack.back() == 1 + 100) {
			cout << "insert : " << 1;
		}
		else if (stack.back() == 1 + 101) {
			cout << "swap : " << 1;
		}
		else if (stack.back() == 1 + 102) {
			cout << "delete : " << 1;
		}
		cout << " -> ";
		stack.pop_back();

	}
    cout << endl;
	cout << "Levenshtein Distance : " << path[row - 1][col - 1] << endl;


}
int main() {

     // 1번 a
	source = "GUMBO";
    target = "GAMBOL";
	LD(source.length(), target.length());

	cout << endl;

    // 1번 b
	source = "GUMBO";
    target = "GAMBOL";
	LD(source.length()-1, target.length()-1);
	cout << endl;

	// // Levenshtein , Meilenstein
    // source = "Levenshtein";
    // target = "Meilenstein";
	// LD(source.length()-1, target.length()-1);

	// cout << endl;

    // // TACTG , CATGACTG

	// source = "TACTG";
    // target = "CATGACTG";
	// LD(source.length()-1, target.length()-1);

    // // 데이터마이닝 , 데이터베이스설계
	// source = "데이터마이닝";
	// target = "데이터베이스설계";
	// LD(source.length() -1, target.length()-1);

    return 0;
}


void LD( int col, int row) {
	cout<<"source : " << source <<" ->  target : "<< target << endl;



    double path[101][101] = {0.0,}; // 모두 초기화 해줍니다. 

	for (int i = 0; i <= row; i++) {
		for (int j = 0; j <= col; j++) {
            if( i == 0){ // i =0 일때 해당 행을 모두 초기화 해줍니다. 
                path[i][j] = costs[1] * j;  // 증가량의 배수만큼 증가시켜줍니다.
            }
            else if(j == 0) // j ==0 일때 해당 행을 모두 초기화 해줍니다. 
            {
                path[i][j] = costs[0] * i;  // 배수만큼 증가시켜줍니다. 
            }
            else{ // 행과 열 모두 0번째가 아닌 경우 진행합니다.
                double cost = 0.0;
		    	if (source[j - 1] != target[i - 1]) { // 대각선의 값이 서로 다른 경우
                    path[i][j] = min( path[i - 1][j - 1] + costs[2] , min(path[i][j - 1] + costs[1], path[i - 1][j] + costs[0]));
		    	}
		    	else {
                    path[i][j] = path[i - 1][j - 1];
		    		cost = 0;
		    	    path[i][j] = min( path[i - 1][j - 1]  , min(path[i][j - 1] + costs[1], path[i - 1][j] + costs[0]));
    			    }
                 }
             cout << path[i][j] << "    ";
    		}
		cout << endl;
	}

	vector <double> stack; 
    int r = row ;
	int c = col ;
    
	for(;;){
        if (r == 0 && c == 0) break;
        else{
        if (path[r][c] == path[r - 1][c] + costs[0]) {
			stack.push_back(costs[0] * costs[0]);
			r--;
		}
		else if (path[r][c] == path[r][c - 1] + costs[1]) {
			stack.push_back(costs[1] * costs[1]);
			c--;
		}
		else if (path[r][c] == path[r - 1][c - 1] + costs[2]) {
			stack.push_back(costs[2] * costs[2]);
			r--; c--;
		}
		else {
			r--;
			c--;
		}
        }

	}
	while (!stack.empty()) {
		if (stack.back() == costs[0] * costs[0]) {
			cout << "insert price: " << costs[0];
		}
		else if (stack.back() == costs[1] * costs[1]) {
			cout << "delete price : " << costs[1];
		}
		else if (stack.back() == costs[2] * costs[2]) {
			cout << "swap price : " << costs[2];
		}
		stack.pop_back();
        if(!stack.empty()){
            cout << ", ";
        }
        else{
            cout <<" : Levenshtein Distance = " << path[row ][col ] << endl;
        }

	}
    cout << endl;
    cout << "----------------------------------------------------------------------------------------------------------------";
    cout << endl;


}