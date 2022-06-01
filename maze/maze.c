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
} element;

// LinkedStack�� ���̴� Node
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

// �̷θ� 2���� �迭�� ���� 
FILE* input; // �Է� ���� ��Ʈ�� 
FILE* output; // ��� ���� ��Ʈ�� 
char maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE];
int total = 0; // �� �̷��� ���� ��
int rows = 0; // �̷��� �� ��
int cols = 0;
element entry; 
element exitDoor; 

// Stack�� �ʱ�ȭ �ϴ� �Լ� : ó�� Stack�� ������Ƿ� s->top = NULL
void init(LinkedStackType* s)
{
	s->top = NULL;
}

// Stack�� ���ο� Node�� �߰��ϴ� �Լ�
void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL)
	{
		printf("�޸��Ҵ翡��\n");
		return;
	}
	temp->item = item;

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

// Stack�� ���� ���� Node�� �����ؼ� ��ȯ�ϴ� �Լ� 
element pop(LinkedStackType* s)
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
		element item = temp->item;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}

// �湮���� ���� �̷��� ��ǥ�� Stack�� �߰��ϴ� �Լ�
void pushLoc(LinkedStackType* s, int r, int c, int max_r, int max_c)
{
	// ��ǥ�� �̷� ���� ���� ��� return
	if (r < 0 || c < 0 || r > max_r || c > max_c) return;
	// �湮���� �ʾҰ� ����� ��ǥ�� ��� Stack�� �߰�
	if (maze[r][c] != '1' && maze[r][c] != '.')
	{
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
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
						rows++;
				}

				cols = total / rows; // ���� �� * ���� �� = ��ü ���� �� ���� �̿��� ���� �� ����
									 // ��� ���� ���� �ִ� ����� �ʰ��� �� ���� ���
				if (cols > MAX_MAZE_SIZE || rows > MAX_MAZE_SIZE)
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
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
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
	fclose(output); 

}

void pathMaze(){
	
	output = fopen(OUTPUT_DIR, "a+"); 

	if (output == NULL)
	{
		printf("��� ���� �ҷ����⿡ �����߽��ϴ�."); 
	}

	fprintf(output, "Ž�� ���\n"); 

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
	LinkedStackType s; 
	init(&s); 

	element here = entry; 
	printf("start "); 

	while (maze[here.r][here.c] != 'X') 
	{
		r = here.r; 
		c = here.c;
		printf("(%d, %d) -> ", r, c);
		maze[r][c] = '.'; 
		pushLoc(&s, r - 1, c, rows-1, cols-1);
		pushLoc(&s, r + 1, c, rows-1, cols-1);
		pushLoc(&s, r, c - 1, rows-1, cols-1);
		pushLoc(&s, r, c + 1, rows-1, cols-1);

		if (isEmpty(&s))
		{
			printf("fail\n"); // ����
			break;
		}
		else
		{
			here = pop(&s);
		}
	}

	if (maze[here.r][here.c] == 'X')
	{
		printf("(%d, %d) -> end\n", here.r, here.c); 
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
