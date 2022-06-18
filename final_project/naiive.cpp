#include <iostream>
#include <vector>
#include <ctime>

#define INF 9999999
using namespace std;
int N, tmp;
//�� ���ð� �̵��ϴµ� ��� ���
int costs[15][15];

//���� : �湮����, ������� �� ���, ���� ��ġ(����), �̵��� ���� ��, ������ ����
int shortest(vector<bool>& visited, int cost, int prev, int size, int first) { 
	if(size == N) return min(INF, cost+costs[prev][first]);
	int ret = INF;
	for(int i = 0; i < N; i++) {
		if(visited[i]) continue;
		visited[i] = true;
		ret = min(shortest(visited, cost+costs[prev][i], i, size+1, first), ret); // ���� �ּҸ� Ȯ���Ͽ� �����մϴ�.
		visited[i] = false;
	}
	return ret;
}

int main() {
	srand(time(NULL)); // ���� ����

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
		visited[i] = true; // ��� ��带 Ȯ���մϴ�
		cmp = min(cmp, shortest(visited, 0, i, 1, i)); // i ��° ��尡 ������ ��� �ּҰ����� �ǹ��մϴ�.
		visited[i] = false; // ������ ��ȸ�� �Ϸ��Ѱ����� Ȯ���մϴ�
	}
    cout << "\n\nTime for to run the genetic algorithm: " 
	<< float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds." <<endl<< endl; // shows time in seconds
	cout << cmp;
}