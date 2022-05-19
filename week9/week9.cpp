#include <iostream>
#include <queue>
#include <string>

using namespace std;
struct nodetype{
   string symbol;
   int frequency;
   nodetype *left;
   nodetype *right;
   string inCoding;
};

struct compare {
	bool operator()(const nodetype& m1, const nodetype& m2) {
		return m1.frequency > m2.frequency;
	}
};
priority_queue<nodetype, vector<nodetype>, compare> pq;
priority_queue<nodetype, vector<nodetype>, compare> answer;

int main()
{
   nodetype temp;
   temp.symbol = "A";
   temp.frequency = 15;
   pq.push(temp);
   temp.symbol = "B";
   temp.frequency = 12;
   pq.push(temp);
   temp.symbol = "C";
   temp.frequency = 9;
   pq.push(temp);
   temp.symbol = "D";
   temp.frequency = 5;
   pq.push(temp);
   temp.symbol = "E";
   temp.frequency = 10;
   pq.push(temp);
   temp.symbol = "F";
   temp.frequency = 11;
   pq.push(temp);
   temp.symbol = "r";
   temp.frequency = 27;
   pq.push(temp);

   
   for(int i=0 ; i < 7; i++)
   {

      if(i==0)
      {
         nodetype temp;
         nodetype temp1 = pq.top();
         answer.push(temp1);
         temp.left = &temp1;
         pq.pop();
         nodetype temp2= pq.top();
         answer.push(temp2);

         temp.right = &temp2;
         pq.pop();
         temp.symbol = "";
         temp.frequency = temp1.frequency + temp2.frequency;
         
         answer.push(temp);
      }
      nodetype tmp;
      nodetype tempRight= pq.top(); // 더 작은값이 top 에 있다.
      answer.push(tempRight);
      pq.pop();
      nodetype tempLeft = pq.top(); //더 큰 값이 top의 바로 뒤에 있다.
      answer.push(tempLeft);
      pq.pop();
      tmp.symbol = "";
      tmp.frequency = tempRight.frequency + tempLeft.frequency;
      tmp.left = &tempLeft;
      tmp.right = &tempRight;
      answer.push(tmp);

   }
   cout << pq.top().symbol;
}