#include <iostream>
#include <vector>
#include <ctime>

#define INF 9999999
using namespace std;
int N, tmp;
//각 도시간 이동하는데 드는 비용
int costs[15][15];

//인자 : 방문여부, 현재까지 든 비용, 이전 위치(도시), 이동한 도시 수, 시작한 도시
int shortest(vector<bool>& visited, int cost, int prev, int size, int first) { 
	if(size == N) return min(INF, cost+costs[prev][first]);
	int ret = INF;
	for(int i = 0; i < N; i++) {
		if(visited[i]) continue;
		visited[i] = true;
		ret = min(shortest(visited, cost+costs[prev][i], i, size+1, first), ret); // 가장 최소를 확인하여 저장합니다.
		visited[i] = false;
	}
	return ret;
}

int main() {
	srand(time(NULL)); // 랜덤 숫자

	int cmp = INF;
	cin.sync_with_stdio(false);
	cin >> N;
	vector<bool> visited(N, false);
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			cin >> tmp;
			if(tmp == 0){
				costs[i][j] = INF;
			}
			else {
				costs[i][j] = tmp;
			}
		}
	}
	const clock_t begin_time = clock(); // gets time

	for (int i = 0; i < N; i++) {
		visited[i] = true; // 모든 노드를 확인합니다
		cmp = min(cmp, shortest(visited, 0, i, 1, i)); // i 번째 노드가 가지는 모든 최소값들을 의미합니다.
		visited[i] = false; // 종료후 순회를 완료한것으로 확인합니다
	}
    cout << "\n\nTime for to run the genetic algorithm: " 
	<< float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds." <<endl<< endl; // shows time in seconds
	cout << cmp;
}