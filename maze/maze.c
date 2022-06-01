#define _CRT_SECURE_NO_WARNINGS // 경고 오류 방지
#define MAX_MAZE_SIZE 100 // 미로 한 변의 최대 크기
#define INPUT_DIR "input.txt" // 입력 파일의 주소 input.txt / input2.txt / input3.txt / input4.txt
#define OUTPUT_DIR "output.txt" // 출력 파일의 주소 output.txt / output2.txt / output3.txt / output4.txt

#include <stdio.h>  
#include <stdlib.h>

// 미로의 한 점 
typedef struct
{
	int r;
	int c;
} Node;

// LinkedStack에 쌓이는 Node
typedef struct StackNode
{
	Node node; 
	struct StackNode* link;
} StackNode;

// LinkedStack 
typedef struct
{
	StackNode* top;
} LinkedStackType;

// 미로를 2차원 배열로 선언 
FILE* input; // 입력 파일 스트림 
FILE* output; // 출력 파일 스트림 
char maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE];
int total = 0; // 총 미로의 점의 수
int mazeRows = 0; // 미로의 행 수
int mazeCols = 0;
Node entry; 
Node exitDoor; 
LinkedStackType s; 

// Stack을 초기화 하는 함수 : 처음 Stack은 비었으므로 s->top = NULL
void init(LinkedStackType* s)
{
	s->top = NULL;
}

// Stack에 새로운 Node를 추가하는 함수
void push(LinkedStackType* s, Node node)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL)
	{
		printf("메모리할당에러\n");
		return;
	}
	temp->node = node;

	// Stack이 비어있는 경우 top 노드를 받아들인 node로 선언하고 해당 node의 link는 NULL
	if (s->top == NULL)
	{
		s->top = temp;
		s->top->link = NULL;
	}
	// Stack이 비어있지 않은 경우 top 노드를 받아들인 node로 선언하고 해당 node의 link는 원래 top이었던 node
	else
	{
		temp->link = s->top;
		s->top = temp;
	}
	
}

// Stack이 비었는지 확인하는 함수
int isEmpty(LinkedStackType* s)
{
	return (s->top == NULL);
}

Node stackTopNode(LinkedStackType* s)
{
	StackNode* temp = s->top;
	Node node = temp->node;
	return node;
}

Node pop(LinkedStackType* s)
{
	// Stack이 비어 있는 경우 오류 출력
	if (isEmpty(s))
	{
		fprintf(stderr, "스택이 비어있음\n");
	}
	// Stack이 비어 있지 않은 경우 top 노드를 위에서 바로 아래 노드로 바꾸고 원래 있던 top 노드의 좌표를 반환
	else
	{

		StackNode* temp = s->top;
		Node node = temp->node;
		s->top = s->top->link;

		return node;
	}
}


void pushLoc( int r, int c)
{

	if (r < 0 || c < 0 || r > mazeRows || c > mazeCols) return;

	if (maze[r][c] != '1' && maze[r][c] != '.')
	{
		Node tmp;
		tmp.r = r;
		tmp.c = c;
		push(&s, tmp);
	}
}


void checkMazeSize (){
	char temp[10001]; // 스트림으로부터 받을 문자열 

	input = fopen(INPUT_DIR, "r"); // 입력 파일 열기

	// 입력 파일을 못 열었을 시
	if (input != NULL)
	{
			while (EOF != fscanf(input, "%s", temp))
				{	
					total++;
				}

				input = fopen(INPUT_DIR, "r"); // 입력 파일 열기

	// 입력 파일을 한 줄씩 문자열로 받아들여 총 행의 수를 측정
				while (NULL != fgets(temp, sizeof(temp), input)) 
				{
						mazeRows++;
				}

				mazeCols = total / mazeRows; // 열의 수 * 행의 수 = 전체 점의 수 임을 이용해 열의 수 측정
									 // 행과 열의 수가 최대 사이즈를 초과할 시 오류 출력
				if (mazeCols > MAX_MAZE_SIZE || mazeRows > MAX_MAZE_SIZE)
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

	input = fopen(INPUT_DIR, "r"); // 입력 파일 열기
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


	output = fopen(OUTPUT_DIR, "w"); 

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
	
	output = fopen(OUTPUT_DIR, "a+"); 

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

	while (maze[currentIndex.r][currentIndex.c] != 'X') 
	{

		printf("(%d, %d) -> ", r, c);
		maze[r][c] = '.'; 
		pushLoc( r - 1, c);
		pushLoc( r + 1, c);
		pushLoc( r, c - 1);
		pushLoc( r, c + 1);

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
