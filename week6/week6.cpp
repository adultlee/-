
#include <iostream>
#include <ctime>
using namespace std;

int arr[1000000]; // test 할 배열

void checkSorted(int list[], int n)
{
    bool isSorted =true;
    for(int i=0; i< n; i++)
    {   
        if(list[i+1] < list[i])
        {    
            if(i != n-1){
            isSorted = false;

            }

            if(list[i+1] ==0)
            {
                isSorted = true;
            }
        }
    }
    if(isSorted == true)
    {
        cout << "정렬되었습니다"<<endl;
    }
    else{
        cout << "정렬되지 않았습니다."<<endl;
    }
}

void checkMinSorted(int list[], int n)
{
    bool isSorted =true;
    for(int i=0; i< n; i++)
    {   
        if(list[i+1] >= list[i])
        {    
        
            if(i != n-1){
            isSorted = false;

            }

            if(list[i+1] ==0)
            {
                isSorted = true;
            }
        }
    }
    if(isSorted == true)
    {
        cout << "정렬되었습니다"<<endl;
    }
    else{
        cout << "정렬되지 않았습니다."<<endl;
    }
}

void init(int list[], int n)
{
    for(int i=0; i<n; i++)
    {
        list[i] = rand()%1000;
    }
}


void swap(int a, int b){
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void MakeMaxHeap(int root, int n){
    int temp = arr[root]; // 해당 부모 노드
    int child = root * 2; // 왼쪽 자식 노드
    while(child <= n){
        // 더 큰 자식 노드 찾기
        if(child<n && arr[child] < arr[child+1])
            child++;
        if(temp < arr[child]){ // 자식 노드가 더 클 경우
            arr[child/2] = arr[child];
            child *=2; // 레벨 낮추기
        }
        else break;
    }
    arr[child/2] = temp;
}

void MaxHeapSort(int n){
    // 최대 힙 구성
    for(int i = n / 2; i > 0; i--){
        MakeMaxHeap(i, n);
    }

    int temp;
    for(int i = n; i > 0; i--){
        swap(1, i);
        MakeMaxHeap(1, i - 1);
    }
}

void MakeMinHeap(int root, int n){
    int temp = arr[root]; // 해당 부모 노드
    int child = root * 2; // 왼쪽 자식 노드
    while(child <= n){
        // 더 작은 자식 노드 찾기
        if(child<n && arr[child] > arr[child+1])
            child++;
        if(temp > arr[child]){ // 자식 노드가 더 작을 경우
            arr[child/2] = arr[child];
            child *=2; // 레벨 낮추기
        }
        else break;
    }
    arr[child/2] = temp;
}
void MinHeapSort(int n){
    // 최소 힙 구성
    for(int i = n / 2; i > 0; i--){
        MakeMinHeap(i, n);
    }

    int temp;
    for(int i = n; i > 0; i--){
        swap(1, i);
        MakeMinHeap(1, i - 1);
    }
}

int main(void){

    time_t start, end;
    int i;
    srand(time(NULL));

    // 실습 1
    cout << "------------실습 1---------------" << endl;

    int num = 10; 
    int data[] = {6,2,8,1,3,9,4,5,10,7};
    arr[1] = 6;
    arr[2] = 2;
    arr[3] = 8;
    arr[4] = 1;
    arr[5] = 3;
    arr[6] = 9;
    arr[7] = 4;
    arr[8] = 5;
    arr[9] = 10;
    arr[10] = 7;
    MaxHeapSort(num);
    cout << "Max heap 정렬 결과" <<endl;
    for(int i =1 ; i<= 10; i++)
    {
        cout << arr[i] << " ";
    } 
    cout << endl;
    arr[1] = 6;
    arr[2] = 2;
    arr[3] = 8;
    arr[4] = 1;
    arr[5] = 3;
    arr[6] = 9;
    arr[7] = 4;
    arr[8] = 5;
    arr[9] = 10;
    arr[10] = 7;
    MinHeapSort(num);
    cout << "Min heap 정렬 결과" <<endl;
    for(int i =1 ; i<= 10; i++)
    {
        cout << arr[i] << " ";
    } 
      cout << endl;
    cout << endl;

    cout << "------------실습 2---------------" << endl;
    cout << "------------N = 10000---------------" << endl;
  
    num = 10000;
    init(arr ,num);
    start = clock() ;
    MaxHeapSort(num);
    end = clock() ;
    cout << "N=10000일때의 Max heap sort 에 걸리는 시간 "<<endl; 
    cout << (float)(end -start)/CLOCKS_PER_SEC <<endl; 
    checkSorted(arr,num);

    init(arr ,num);
    start = clock() ;
    MinHeapSort(num);
    end = clock() ;
    cout << "N=10000일때의 Min heap sort 에 걸리는 시간 "<<endl; 
    cout << (float)(end -start)/CLOCKS_PER_SEC <<endl; 
    checkSorted(arr,num);
    cout << endl;
    
    cout << "------------N = 50000---------------" << endl;

    num = 50000;
    init(arr ,num);
    start = clock() ;
    MaxHeapSort(num);
    end = clock() ;
    cout << "N=50000일때의 Max heap sort 에 걸리는 시간 "<<endl; 
    cout << (float)(end -start)/CLOCKS_PER_SEC <<endl; 
    checkSorted(arr,num);

    init(arr ,num);
    start = clock() ;
    MinHeapSort(num);
    end = clock() ;
    cout << "N=50000일때의 Min heap sort 에 걸리는 시간 "<<endl; 
    cout << (float)(end -start)/CLOCKS_PER_SEC <<endl; 
    checkSorted(arr,num);
    cout << endl;
     
    cout << "------------N = 100000---------------" << endl;

    num = 100000;
    init(arr ,num);
    start = clock() ;
    MaxHeapSort(num);
    end = clock() ;
    cout << "N=100000일때의 Max heap sort 에 걸리는 시간 "<<endl; 
    cout << (float)(end -start)/CLOCKS_PER_SEC <<endl; 
    checkSorted(arr,num);

    init(arr ,num);
    start = clock() ;
    MinHeapSort(num);
    end = clock() ;
    cout << "N=100000일때의 Min heap sort 에 걸리는 시간 "<<endl; 
    cout << (float)(end -start)/CLOCKS_PER_SEC <<endl; 
    checkSorted(arr,num);
    cout << endl;

    cout << "------------N = 500000---------------" << endl;

    num = 500000;
    init(arr ,num);
    start = clock() ;
    MaxHeapSort(num);
    end = clock() ;
    cout << "N=500000일때의 Max heap sort 에 걸리는 시간 "<<endl; 
    cout << (float)(end -start)/CLOCKS_PER_SEC <<endl; 
    checkSorted(arr,num);

    init(arr ,num);
    start = clock() ;
    MinHeapSort(num);
    end = clock() ;
    cout << "N=500000일때의 Min heap sort 에 걸리는 시간 "<<endl; 
    cout << (float)(end -start)/CLOCKS_PER_SEC <<endl; 
    checkSorted(arr,num);
    cout << endl;

    cout << "------------N = 1000000---------------" << endl;

    num = 1000000;
    init(arr ,num);
    start = clock() ;
    MaxHeapSort(num);
    end = clock() ;
    cout << "N=1000000일때의 Max heap sort 에 걸리는 시간 "<<endl; 
    cout << (float)(end -start)/CLOCKS_PER_SEC <<endl; 
    checkSorted(arr,num);

    init(arr ,num);
    start = clock() ;
    MinHeapSort(num);
    end = clock() ;
    cout << "N=1000000일때의 Min heap sort 에 걸리는 시간 "<<endl; 
    cout << (float)(end -start)/CLOCKS_PER_SEC <<endl; 
    checkSorted(arr,num);
    cout << endl;
    return 0;

}
