#include <stdio.h>  
#include <stdlib.h>

typedef struct
{
	int r;
	int c;
} Node;

// LinkedStack에 쌓이는 Node
typedef struct StackNode
{
	Node node; 
	struct StackNode* ptr;
} StackNode;

// LinkedStack 
typedef struct
{
	StackNode* top;
} PathStack;


FILE* input; // 입력  
FILE* output; // 출력  
char maze[101][101];
int total = 0; // 총 미로의 점의 수
int mazeRows = 0; // 미로의 행 수
int mazeCols = 0;
Node entry; 
Node exitDoor; 
PathStack s; 

// Stack을 초기화 하는 함수 : 처음 Stack은 비었으므로 s->top = NULL
void init(PathStack* s)
{
	s->top = NULL;
}

// Stack에 새로운 Node를 추가하는 함수
void push(PathStack* s, int r, int c)
{
	if (r < 0 || c < 0 || r > mazeRows || c > mazeCols) return;
	if (maze[r][c] != '1' && maze[r][c] != '.')
	{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));

	temp->node.c = c;
	temp->node.r = r;

	if (s->top == NULL)
	{
		s->top = temp;
		s->top->ptr = NULL;
	}
	else
	{
		temp->ptr = s->top;
		s->top = temp;
	}
	}

	
}

int isEmpty(PathStack* s)
{
	if(s->top != NULL)
	{
		return 0;
	}
	else{
		return 1;
	}
}

Node stackTopNode(PathStack* s) // 현재 가장 stack의 노드를 꺼냅니다.
{
	if(!isEmpty(s)){
		StackNode* temp = s->top;
		Node node = temp->node;
		return node;
	}
	else{
		printf("stack이 비어 있습니다.");
	}
	
}

Node pop(PathStack* s)
{
		Node node = stackTopNode(s);
		s->top = s->top->ptr;

		return node;

}





void checkMazeSize (){
	char temp[10001]; // 스트림으로부터 받을 문자열 

	input = fopen("input.txt", "r"); // 입력 파일 열기

	// 입력 파일을 못 열었을 시
	if (input != NULL)
	{
			while (EOF != fscanf(input, "%s", temp))
				{	
					total++;
				}

				input = fopen("input.txt", "r"); // 입력 파일 열기

	// 입력 파일을 한 줄씩 문자열로 받아들여 총 행의 수를 측정
				while (NULL != fgets(temp, sizeof(temp), input)) 
				{
						mazeRows++;
				}

				mazeCols = total / mazeRows; // 열의 수 * 행의 수 = 전체 점의 수 임을 이용해 열의 수 측정
									 // 행과 열의 수가 최대 사이즈를 초과할 시 오류 출력
				if (mazeCols > 101 || mazeRows > 101)
				{
					printf("미로 크기 한도 초과");
				}

	}
	else{
		printf("파일을 열 수 없습니다.");
	}
}

void makeMaze(){
	char str[10001]; 

	input = fopen("input.txt", "r"); // 입력 파일 열기
	for (int row = 0; row < mazeRows; row++)
	{
		for (int col = 0; col < mazeCols; col++)
		{
			fscanf(input, "%s", str);
			printf("%s", str);
			printf(" ");
			
			maze[row][col] = str[0];
			if (maze[row][col] == 'E') 
			{
				entry.r = row;
				entry.c = col;
			}
			else
			{
				if (maze[row][col] == 'X')
				{
					exitDoor.r = row;
					exitDoor.c = col;
				}
			}

		}
		printf("\n");
	}
	fclose(input); 
}

void drawMaze(){


	output = fopen("output.txt", "w"); 

	if (output == NULL)
	{
		printf("출력 파일을 열 수 없습니다.");
	}

	for (int row = 0; row < mazeRows; row++)
	{
		for (int col = 0; col < mazeCols; col++)
		{
			if (maze[row][col] == '1')
				fprintf(output, "@@");

			else
			{
				if (maze[row][col] == '0')
					fprintf(output, "  ");
			}
			if (maze[row][col] == 'E')
				fprintf(output, "E ");
			else
			{
				if (maze[row][col] == 'X')
					fprintf(output, "X ");
			}
		}
		fprintf(output, "\n");
	}
	fprintf(output, "\n");
	fclose(output); 

}

void pathMaze(){
	
	output = fopen("output.txt", "a+"); 

	if (output == NULL)
	{
		printf("출력 파일 불러오기에 실패했습니다."); 
	}

	fprintf(output, "탐색 경로\n"); 

	for (int row = 0; row < mazeRows; row++)
	{
		for (int col = 0; col < mazeCols; col++)
		{
			if (maze[row][col] == '1')
				fprintf(output, "@@");

			else
			{
				if (maze[row][col] == '0')
					fprintf(output, "  ");
			}
			
			if (row == exitDoor.r && col == exitDoor.c)
			{
				fprintf(output, "X");
			}
			else
			{
				if (maze[row][col] == '.')
				{
					fprintf(output, ". ");
				}
			}
		}
		fprintf(output, "\n");
	}

	fclose(output); 
}

void makeStack(){

	int r, c; 

	init(&s); 

	Node currentIndex = entry; 

	r = currentIndex.r; 
	c = currentIndex.c;

	printf("start "); 
	printf("(%d, %d) -> ", r, c);
	while (maze[currentIndex.r][currentIndex.c] != 'X') 
	{	
		
		maze[r][c] = '.'; 
		push(&s, r - 1, c);
		push(&s, r + 1, c);
		push(&s, r, c - 1);
		push(&s, r, c + 1);

		if (isEmpty(&s))
		{
			printf("fail\n"); // 여기
			break;
		}
		else
		{
			currentIndex = pop(&s);
			r = currentIndex.r; 
			c = currentIndex.c;
			printf("(%d, %d) -> ", r, c);
		}
	}
	if (maze[currentIndex.r][currentIndex.c] == 'X')
	{
		printf("(%d, %d) -> end\n", currentIndex.r, currentIndex.c); 
		printf("success\n"); 
	}
	
}
void main()
{


	checkMazeSize(); // Maze를 읽어서 행 과 열을 전역변수에 저장합니다. 
	makeMaze();
	drawMaze();
	makeStack();
	pathMaze();

	return;
	
}
