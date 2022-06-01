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
} element;

// LinkedStack에 쌓이는 Node
typedef struct StackNode
{
	element item; 
	struct StackNode* link;
} StackNode;

// LinkedStack 
typedef struct
{
	StackNode* top;
} LinkedStackType;

// 미로를 2차원 배열로 선언 
char maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE];

void error(char* message); // 오류를 출력하는 함수

void init(LinkedStackType* s); // Stack을 초기화하는 함수

void push(LinkedStackType* s, element item); // Stack에 새로운 Node를 추가하는 함수
int isEmpty(LinkedStackType* s); // Stack이 비었는지 확인하는 함수
element pop(LinkedStackType* s); // Stack의 가장 위의 Node를 제거해서 반환하는 함수 
element peek(LinkedStackType* s); // Stack의 가장 위의 Node가 무엇인지 알려주는 함수

void pushLoc(LinkedStackType* s, int r, int c, int max_r, int max_c); // 방문하지 않은 미로의 좌표를 Stack에 추가하는 함수

void main()
{
	FILE* input; // 입력 파일 스트림
	FILE* output; // 출력 파일 스트림

	char str[2 * MAX_MAZE_SIZE + 3]; // 스트림으로부터 받을 문자열 
	int total = 0; // 총 미로의 점의 수
	int rows = 0; // 미로의 행 수

	element entry; // 입구 
	element exit; // 출구

	input = fopen(INPUT_DIR, "r"); // 입력 파일 열기

	// 입력 파일을 못 열었을 시
	if (input == NULL)
	{
		error("입력 파일을 열 수 없습니다.");
	}

	// 입력 파일의 공백과 줄바꿈을 기준으로 단어를 받아들여 총 점의 수를 측정
	while (EOF != fscanf(input, "%s", str))
	{	
		// printf("%s",str); 
		total++;
	}
	fclose(input); // 입력 파일 닫기

	input = fopen(INPUT_DIR, "r"); // 입력 파일 열기

	// 입력 파일을 못 열었을 시
	if (input == NULL)
	{
		error("입력 파일을 열 수 없습니다.");
	}

	// 입력 파일을 한 줄씩 문자열로 받아들여 총 행의 수를 측정
	while (NULL != fgets(str, sizeof(str), input)) 
	{
		rows++;
	}
	
	fclose(input); // 입력 파일 닫기

	int cols = total / rows; // 열의 수 * 행의 수 = 전체 점의 수 임을 이용해 열의 수 측정
	// 행과 열의 수가 최대 사이즈를 초과할 시 오류 출력
	if (cols > MAX_MAZE_SIZE || rows > MAX_MAZE_SIZE)
	{
		error("미로 크기 한도 초과");
	}

	input = fopen(INPUT_DIR, "r"); // 입력 파일 열기

	// 입력 파일을 못 열었을 시
	if (input == NULL)
	{
		error("입력 파일을 열 수 없습니다.");
	}

	// 공백과 줄바꿈을 기준으로 단어를 읽어 각 문자를 maze에 담는다.
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			fscanf(input, "%s", str);
			maze[row][col] = str[0];
			// 입구 좌표 저장
			if (maze[row][col] == 'E') 
			{
				entry.r = row;
				entry.c = col;
			}
			else
			{
				// 출구 좌표 저장
				if (maze[row][col] == 'X')
				{
					exit.r = row;
					exit.c = col;
				}
			}
		}
	}
	fclose(input); // 입력 파일 닫기

	output = fopen(OUTPUT_DIR, "w"); // 출력 파일 열기

	// 출력 파일을 못 열었을 시
	if (input == NULL)
	{
		error("출력 파일을 열 수 없습니다.");
	}

	// 출력 파일 형식에 맞게 지도 작성하기 [] : 미로의 벽 / 공백 : 통로 / E : 입구 / X : 출구
	
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
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
	fclose(output); // 출력 파일 닫기

	int r, c; 
	LinkedStackType s; // Stack 선언
	init(&s); // Stack 초기화

	element here = entry; // 출발지를 입구로
	printf("start "); 

	while (maze[here.r][here.c] != 'X') // 도착지에 도달할 때까지 반복
	{
		r = here.r; 
		c = here.c;
		printf("(%d, %d) -> ", r, c);
		maze[r][c] = '.'; // 방문한 좌표를 . 으로 표시 
		// 왼쪽 오른쪽 위 아래 중 방문하지 않은 통로를 찾아서 스택에 쌓기
		pushLoc(&s, r - 1, c, rows-1, cols-1);
		pushLoc(&s, r + 1, c, rows-1, cols-1);
		pushLoc(&s, r, c - 1, rows-1, cols-1);
		pushLoc(&s, r, c + 1, rows-1, cols-1);

		// 방문할 수 있는 모든 점을 방문하였지만 출구에 도달하지 못 하였을 때는 실패
		if (isEmpty(&s))
		{
			printf("fail\n"); // 여기
			break;
		}
		else
		{
			here = pop(&s);
		}
	}

	// 출구에 도착할 경우는 성공
	if (maze[here.r][here.c] == 'X')
	{
		printf("(%d, %d) -> end\n", here.r, here.c); // 여기
		printf("success\n"); // 여기
	}

	output = fopen(OUTPUT_DIR, "a+"); // 출력 파일 덧 붙여 쓰기 전용 개방

	if (output == NULL)
	{
		error("출력 파일 불러오기에 실패했습니다."); // 출력 파일 열기 실패시
	}

	// 출력 파일 형식에 맞게 쓰기
	fprintf(output, "탐색 경로\n"); 

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			// 벽 : [] / 방문하지 않은 통로 : 공백
			if (maze[row][col] == '1')
				fprintf(output, "@@");

			else
			{
				if (maze[row][col] == '0')
					fprintf(output, "  ");
			}
			
			// 출구 : X / 출구 외 방문한 통로 : .
			if (row == exit.r && col == exit.c)
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

	fclose(output); // 출력 파일 닫기

	return;
	
}

// 오류를 출력하는 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// Stack을 초기화 하는 함수 : 처음 Stack은 비었으므로 s->top = NULL
void init(LinkedStackType* s)
{
	s->top = NULL;
}

// Stack에 새로운 Node를 추가하는 함수
void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL)
	{
		error("메모리할당에러\n");
		return;
	}
	temp->item = item;

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

// Stack의 가장 위의 Node를 제거해서 반환하는 함수 
element pop(LinkedStackType* s)
{
	// Stack이 비어 있는 경우 오류 출력
	if (isEmpty(s))
	{
		fprintf(stderr, "스택이 비어있음\n");
		exit(1);
	}
	// Stack이 비어 있지 않은 경우 top 노드를 위에서 바로 아래 노드로 바꾸고 원래 있던 top 노드의 좌표를 반환
	else
	{
		StackNode* temp = s->top;
		element item = temp->item;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}


// Stack의 가장 위의 Node가 무엇인지 알려주는 함수
element peek(LinkedStackType* s)
{
	// 스택이 비었을 경우 오류 출력
	if (isEmpty)
	{
		fprintf(stderr, "스택이 비어있음\n");
		exit(1);
	}
	// 스택이 비어있지 않은 경우 가장 위 노드의 좌표를 반환
	else
	{
		return s->top->item;
	}
}

// 방문하지 않은 미로의 좌표를 Stack에 추가하는 함수
void pushLoc(LinkedStackType* s, int r, int c, int max_r, int max_c)
{
	// 좌표가 미로 내에 없을 경우 return
	if (r < 0 || c < 0 || r > max_r || c > max_c) return;
	// 방문하지 않았고 통로인 좌표인 경우 Stack에 추가
	if (maze[r][c] != '1' && maze[r][c] != '.')
	{
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}