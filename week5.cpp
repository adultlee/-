#include <iostream>
#include <ctime>

using namespace std;
  
// A function to sort the algorithm using Odd Even sort

int testArr[100001];

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
}
void checkSorted(int list[], int n)
{
    bool isSorted =true;
    for(int i=0; i< n; i++)
    {
        if(list[i+1] <= list[i])
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
        cout << " 정렬되었습니다"<<endl;
    }
    else{
        cout << " 정렬되지 않았습니다."<<endl;
    }
}
void oddEvenSort(int arr[], int n)
{
    bool isSorted = false; 
    while (!isSorted) {
        isSorted = true;

      
        for (int i = 0; i <= n - 2; i = i + 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
        cout << "odd index"<<endl;
        printArray(arr,n);

          for (int i = 1; i <= n - 2; i = i + 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
        cout << "even index"<<endl;
        printArray(arr,n);
    }
    cout << "최종 정렬 결과"<<endl;
    checkSorted(arr,n);
    printArray(arr,n);

    return;
}

void oddEvenSortNotPrint(int arr[], int n)
{
    bool isSorted = false; 
    while (!isSorted) {
        isSorted = true;

      
        for (int i = 0; i <= n - 2; i = i + 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
          for (int i = 1; i <= n - 2; i = i + 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
    }
    cout << "최종 정렬 결과"<<endl;
    checkSorted(arr,n);


    return;
}


void init(int list[], int n)
{
    for(int i=0; i<n; i++)
    {
        list[i] = rand()%1000;
    }
}


int main()
{
    time_t start, end;
    int i;
    srand(time(NULL));

    int arr1[] = { 2, 10, 3,5 ,7,9,4,10 };//8
    int arr2[] = { 2, 1, 5,3 ,7,9,4,10 };//8
    int arr3[] = { 4, 13, 2,5 ,6,70,8,3 ,10,11,24,23,21,7,9,12}; //16개

  
    oddEvenSort(arr3, 16);

    init(testArr ,10000);
    start = clock() ;
    oddEvenSortNotPrint(testArr, 10000);
    end = clock() ;
    cout << "N=10000일때의 odd even sort 에 걸리는 시간 "<<endl; 
    cout << (float)(end -start)/CLOCKS_PER_SEC <<endl; 


    init(testArr ,50000);
    start = clock() ;
    oddEvenSortNotPrint(testArr, 50000);
    end = clock() ;
    cout << "N=50000일때의 odd even sort 에 걸리는 시간 "<<endl; 
    cout << (float)(end -start)/CLOCKS_PER_SEC <<endl; 

    init(testArr ,100000);
    start = clock() ;
    oddEvenSortNotPrint(testArr, 100000);
    end = clock() ;
    cout << "N=100000일때의 odd even sort 에 걸리는 시간 "<<endl; 
    cout << (float)(end -start)/CLOCKS_PER_SEC <<endl; 
}