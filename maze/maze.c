#include <stdio.h>  
#include <stdlib.h>

typedef struct
{
	int r;
	int c;
} Node;

// LinkedStack�� ���̴� Node
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


FILE* input; // �Է�  
FILE* output; // ���  
char maze[101][101];
int total = 0; // �� �̷��� ���� ��
int mazeRows = 0; // �̷��� �� ��
int mazeCols = 0;
Node entry; 
Node exitDoor; 
PathStack s; 

// Stack�� �ʱ�ȭ �ϴ� �Լ� : ó�� Stack�� ������Ƿ� s->top = NULL
void init(PathStack* s)
{
	s->top = NULL;
}

// Stack�� ���ο� Node�� �߰��ϴ� �Լ�
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

Node stackTopNode(PathStack* s) // ���� ���� stack�� ��带 �����ϴ�.
{
	if(!isEmpty(s)){
		StackNode* temp = s->top;
		Node node = temp->node;
		return node;
	}
	else{
		printf("stack�� ��� �ֽ��ϴ�.");
	}
	
}

Node pop(PathStack* s)
{
		Node node = stackTopNode(s);
		s->top = s->top->ptr;

		return node;

}





void checkMazeSize (){
	char temp[10001]; // ��Ʈ�����κ��� ���� ���ڿ� 

	input = fopen("input.txt", "r"); // �Է� ���� ����

	// �Է� ������ �� ������ ��
	if (input != NULL)
	{
			while (EOF != fscanf(input, "%s", temp))
				{	
					total++;
				}

				input = fopen("input.txt", "r"); // �Է� ���� ����

	// �Է� ������ �� �پ� ���ڿ��� �޾Ƶ鿩 �� ���� ���� ����
				while (NULL != fgets(temp, sizeof(temp), input)) 
				{
						mazeRows++;
				}

				mazeCols = total / mazeRows; // ���� �� * ���� �� = ��ü ���� �� ���� �̿��� ���� �� ����
									 // ��� ���� ���� �ִ� ����� �ʰ��� �� ���� ���
				if (mazeCols > 101 || mazeRows > 101)
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

	input = fopen("input.txt", "r"); // �Է� ���� ����
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
	
	output = fopen("output.txt", "a+"); 

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
			printf("fail\n"); // ����
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


	checkMazeSize(); // Maze�� �о �� �� ���� ���������� �����մϴ�. 
	makeMaze();
	drawMaze();
	makeStack();
	pathMaze();

	return;
	
}
