#include <stdio.h>  
#include <stdlib.h>


FILE* input; // 입력  
FILE* output; // 출력  
char maze[101][101] = {0,};
int count = 0; 
int mazeRows = 0; 
int mazeCols = 0;
typedef struct
{
	int r;
	int c;
} Node;
typedef struct StackNode
{
	struct StackNode* ptr;
	Node node; 
} StackNode;
typedef struct
{
	StackNode* top;
	int count;
} PathStack;

Node entrance; 
Node exitDoor; 
PathStack stack; 


void push(PathStack* stack, int r, int c)
{
	if(maze[r][c] == '1') return;
	if(maze[r][c] == '.') return; // 현재 위치에서 이미 방문하거나 벽인경우 해당 위치는 더 이상 건들이지 않습니다.
	if(0 < r && r < mazeRows && 0 < c && c < mazeCols ){

		PathStack * tempPtr =NULL;
		StackNode* temp = (StackNode*)malloc(10001);

		temp->node.c = c;
		temp->node.r = r;

		if (stack->top != NULL)
		{
			
			tempPtr = stack->top;
			temp->ptr = tempPtr;
			stack->top = temp;
		}
		else
		{
			stack->top = temp;
			stack->top->ptr = NULL;
		}
	}

	
}
int isEmpty(PathStack* stack) // 현재 node가 비어있는지 확인합니다.
{
	if(stack->top != NULL)
	{
		return 0;
	}
	else{
		return 1;
	}
}

Node stackTopNode(PathStack* stack) // 현재 가장 stack의 노드를 꺼냅니다.
{
	if(!isEmpty(stack)){ // stack이 비어 있지 않다면 return 합니다. 
		StackNode* ss = stack->top;
		Node node = ss->node;
		return node;
	}
	else{
		printf("stack이 비어 있습니다.");
	}
	
}

Node pop(PathStack* stack) // stack의 최상단을 return하며 그 과정에서 삭제하고 새롭게 연결합니다.
{
		Node node = stackTopNode(stack); // return 할 최상단노드 입니다. 
		stack->top = stack->top->ptr; // 현재 저장된 top을 현재 최상단 top 이 바라보던 바로 전 stack의 꼭대기로 바꾸어줍니다.
		return node;
}


void checkMazeSize (){
	char temp[10001]; // 읽은 파일을 임시로 저장할 저장소 입니다. 일종의 buffer의 역할을 수행합니다.

	input = fopen("input.txt", "r"); 

			while (1)
			{	
				if(EOF == fscanf(input, "%s", temp) ) break; // End of File 에 도달한 경우 종료합니다. 
				count++; // 파일의 문자의 수를 셉니다.
			}
			input = fopen("input.txt", "r"); 

			while (1) 
			{
				if(NULL == fgets(temp, sizeof(temp), input)) break; // 한줄씩 출력합니다. 더 이상 출력할 수 없다면 종료합니다.
				mazeRows++; // 파일의 행을 셉니다.
			}

				mazeCols = count / mazeRows; //총 문자들을 행으로 나누면 열을 알 수 있습니다. 

}

void makeMaze(){
	char tmp[10001]; //임시로 저장할 buffer의 역할을 수행합니다. 

	input = fopen("input.txt", "r"); 
	Node current; // 현재 노드를 출력합니다. 
	for (int row = 0; row < mazeRows; row++)
	{
		for (int col = 0; col < mazeCols; col++) // 앞서 구한 미로의 행과 열만큼 반복하며 확인하며 미로를 그립니다.
		{
			fscanf(input, "%s", tmp); // 한글자씩 미로를 셉니다.
			current.r =row;
			current.c = col; // 현재의 미로의 행과 열입니다.
			if (tmp[0] == 'E') //
			{
				entrance=current; // 이 경우 node로 저장한 entrance 에 current 위치를 저장합니다.
			}
			else if(tmp[0]== 'X')
			{

				exitDoor = current; // 이 경우 node로 저장한 exitDoor의 위치를 저장합니다. 

			}
			maze[row][col] = tmp[0]; // 현재 저장된 temp 를 미로에 더합니다. 

		}
	}
	fclose(input); 
}

void drawMaze(){
	output = fopen("output.txt", "w"); 

	for (int row = 0; row < mazeRows; row++)
	{
		for (int col = 0; col < mazeCols; col++) // 앞서 구한 미로의 행과 열만큼 돌며 확인합니다.
		{
			if (maze[row][col] == 'E') // E라면 output에 그립니다. 마찬가지로 x거나 벽(1) 인 경우도 확인합니다.
			{
				if(col == 0)
				fprintf(output, "E ");
				else{
				fprintf(output, " E");
				}
			}
		
			else if(maze[row][col] == 'X')
			{
					if(col == 0)
					fprintf(output, "X ");
					else{
					fprintf(output, " X");

					}
			}
			else if (maze[row][col] == '1')
			{
				fprintf(output, "@@");
			}
			else 
			{
				fprintf(output, "  ");
			}

		}
		fprintf(output, "\n");
	}
	fprintf(output, "\n");
	fclose(output); 

}

void pathMaze(){
	
	output = fopen("output.txt", "a+"); //파일을 읽고 사용합니다.

	Node current; // 현재의 위치
	for (int row = 0; row < mazeRows; row++)
	{
		for (int col = 0; col < mazeCols; col++) // 미로의 크기만큼 반복합니다. 
		{
			current.c = col; // 현재의 위치를 저장합니다. 
			current.r = row;
			
			if(maze[row][col] == '0')
			{
					fprintf(output, "  ");
			}
			else if(maze[row][col] == 'E')
			{
					fprintf(output, "E ");
			}
			else if (current.r  == exitDoor.r && current.c == exitDoor.c) // 현재의 위치와 비교하여 끝 위치에 도달했다면 종료합니다.
			{
				if(col == 0)
				fprintf(output, "X ");
				else
				{
					fprintf(output, " X");
				}
			}
			else if (maze[row][col] == '1') // 벽을 만났다면 벽을 그립니다.
			{
				fprintf(output, "@@");
			}

			
			else if(maze[row][col] == '.') // 경로 에 해당하는 부분을 채웁니다. 
			{
				
					fprintf(output, ". ");

			}
		}
		fprintf(output, "\n");
	}

	fclose(output); 
}

void makeStack(PathStack* stack){

	stack->top = NULL; // 현재 스택을 초기화 합니다. 

	Node currentIndex = entrance; //첫 시작은 E 부터 입ㄴ다.

	int r = currentIndex.r; // 현재의 노드의 위치를 저장합니다.
	int c = currentIndex.c;

	printf("start"); 
	printf(" (%d,%d) -> ", r, c); // 노드가 출발합니다. 
	if(maze[currentIndex.r][currentIndex.c] != 'E' && maze[currentIndex.r][currentIndex.c] !='1') 
	{// E와 벽을 만나지 않은 모든 경우에 경로를 잡아줍니다.
		 	maze[r][c] = '.'; 
	}
	while (1) //무한히 while문을 반복합니다.
	{	
		if(maze[currentIndex.r][currentIndex.c] == 'X') //노드가 x 를 만난경우에 종료시킵니다.
		{
			printf("(%d,%d) -> end\n", currentIndex.r, currentIndex.c); 
			printf("success\n"); 
			break;
		}
		
		if(maze[currentIndex.r][currentIndex.c] != 'E' && maze[currentIndex.r][currentIndex.c] !='1') 
		{// E와 벽을 만나지 않은 모든 경우에 경로를 잡아줍니다.
		 	maze[r][c] = '.'; 
		}
		push(&stack, r, c + 1);  // -> 으로 이동
		push(&stack, r + 1, c);  // 아래로 이동
		push(&stack, r, c - 1); // <- 으로 이동
		push(&stack, r - 1, c);  //  위로 이동


		if (!isEmpty(&stack)) // stack이 비어 있지 않다면 pop해 주면서 현재의 stack의 위치에 따라 current를 이동합니다.
		{
			currentIndex = pop(&stack); // pop 시켜줍니다. 
			r = currentIndex.r; 
			c = currentIndex.c;
			printf("(%d, %d) -> ", r, c); //이동한 직후 출력합니다.  
		}
		else
		{
			printf("fail\n"); //여기 수정하렴~~
			break;
						
		}
	}
	
}
void main()
{
	checkMazeSize(); // Maze를 읽어서 행 과 열을 전역변수에 저장합니다. 
	makeMaze(); // 미로를 만듭니다. 이때 입구와 출구를 만들고 
	drawMaze(); // 미로를 output 파일에 저장합니다.

	makeStack(&stack); // stack을 받아서 stack을 통해 경로를 채워갑니다.
	pathMaze(); // 경로를 output에 그립니다. 

	return;
	
}
