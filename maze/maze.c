#define _CRT_SECURE_NO_WARNINGS // ��� ���� ����
#define MAX_MAZE_SIZE 100 // �̷� �� ���� �ִ� ũ��
#define INPUT_DIR "input.txt" // �Է� ������ �ּ� input.txt / input2.txt / input3.txt / input4.txt
#define OUTPUT_DIR "output.txt" // ��� ������ �ּ� output.txt / output2.txt / output3.txt / output4.txt

#include <stdio.h>  
#include <stdlib.h>

// �̷��� �� �� 
typedef struct
{
	int r;
	int c;
} Node;

// LinkedStack�� ���̴� Node
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

// �̷θ� 2���� �迭�� ���� 
FILE* input; // �Է� ���� ��Ʈ�� 
FILE* output; // ��� ���� ��Ʈ�� 
char maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE];
int total = 0; // �� �̷��� ���� ��
int mazeRows = 0; // �̷��� �� ��
int mazeCols = 0;
Node entry; 
Node exitDoor; 
LinkedStackType s; 

// Stack�� �ʱ�ȭ �ϴ� �Լ� : ó�� Stack�� ������Ƿ� s->top = NULL
void init(LinkedStackType* s)
{
	s->top = NULL;
}

// Stack�� ���ο� Node�� �߰��ϴ� �Լ�
void push(LinkedStackType* s, Node node)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL)
	{
		printf("�޸��Ҵ翡��\n");
		return;
	}
	temp->node = node;

	// Stack�� ����ִ� ��� top ��带 �޾Ƶ��� node�� �����ϰ� �ش� node�� link�� NULL
	if (s->top == NULL)
	{
		s->top = temp;
		s->top->link = NULL;
	}
	// Stack�� ������� ���� ��� top ��带 �޾Ƶ��� node�� �����ϰ� �ش� node�� link�� ���� top�̾��� node
	else
	{
		temp->link = s->top;
		s->top = temp;
	}
	
}

// Stack�� ������� Ȯ���ϴ� �Լ�
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
	// Stack�� ��� �ִ� ��� ���� ���
	if (isEmpty(s))
	{
		fprintf(stderr, "������ �������\n");
	}
	// Stack�� ��� ���� ���� ��� top ��带 ������ �ٷ� �Ʒ� ���� �ٲٰ� ���� �ִ� top ����� ��ǥ�� ��ȯ
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
	char temp[10001]; // ��Ʈ�����κ��� ���� ���ڿ� 

	input = fopen(INPUT_DIR, "r"); // �Է� ���� ����

	// �Է� ������ �� ������ ��
	if (input != NULL)
	{
			while (EOF != fscanf(input, "%s", temp))
				{	
					total++;
				}

				input = fopen(INPUT_DIR, "r"); // �Է� ���� ����

	// �Է� ������ �� �پ� ���ڿ��� �޾Ƶ鿩 �� ���� ���� ����
				while (NULL != fgets(temp, sizeof(temp), input)) 
				{
						mazeRows++;
				}

				mazeCols = total / mazeRows; // ���� �� * ���� �� = ��ü ���� �� ���� �̿��� ���� �� ����
									 // ��� ���� ���� �ִ� ����� �ʰ��� �� ���� ���
				if (mazeCols > MAX_MAZE_SIZE || mazeRows > MAX_MAZE_SIZE)
				{
					printf("�̷� ũ�� �ѵ� �ʰ�");
				}

	}
	else{
		printf("������ �� �� �����ϴ�.");
	}
}

void makeMaze(){
	char str[10001]; 

	input = fopen(INPUT_DIR, "r"); // �Է� ���� ����
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
		printf("��� ������ �� �� �����ϴ�.");
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
		printf("��� ���� �ҷ����⿡ �����߽��ϴ�."); 
	}

	fprintf(output, "Ž�� ���\n"); 

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
			printf("fail\n"); // ����
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


	checkMazeSize(); // Maze�� �о �� �� ���� ���������� �����մϴ�. 
	makeMaze();
	drawMaze();
	makeStack();
	pathMaze();

	return;
	
}
