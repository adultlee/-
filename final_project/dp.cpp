#include<iostream>
#include <ctime>

#define MAX 17000000
#define CITY 16

using namespace std;

int n;
int arr[CITY][CITY];
int d[1 << CITY][CITY] = { 0 };

//visit : �̹� �湮�� ���� üũ
//now : �̹��� ���� ���� ��ȣ
int TSP(int visit, int now)
{
	//now�� ���� �湮 �߰�
	visit |= (1 << now);
	
	//��� ���ø� ���� ���
	if (visit == (1 << n) - 1)
	{
		//now -> 0(��ߵ���)�� ���� ��� �־�� ���ư� �� ����
		if (arr[now][0] > 0)
		{
			return arr[now][0];//������ ��ȯ
		}
		return MAX;//�Ұ����� ��� MAX ��ȯ
	}

	int& ret = d[visit][now];
	//memorization
	if (ret > 0)
		return ret;
	ret = MAX;
	for (int i = 0; i < n; i++)
	{
		//now -> ���� �湮���� ���� i�� ���� ���� ��ΰ� �ִ� ��� 
		if (i != now && (visit&(1<<i))==0 && arr[now][i] > 0)
		{
			//�ּ� ��� ����
			int temp = TSP(visit, i) + arr[now][i];
			if (ret > temp)
				ret = temp;
		}
	}
	return ret;
}

int main()
{
	int ans;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> arr[i][j];
		}
	}
	const clock_t begin_time = clock(); // gets time
	
	ans = TSP(0, 0);
	if (ans == MAX) printf("-1\n");
	else printf("%d\n", ans);
    
	cout << "\n\ntotal time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds."; // shows time in seconds
	return 0;
}