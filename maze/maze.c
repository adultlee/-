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
char maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE];

void error(char* message); // ������ ����ϴ� �Լ�

void init(LinkedStackType* s); // Stack�� �ʱ�ȭ�ϴ� �Լ�

void push(LinkedStackType* s, element item); // Stack�� ���ο� Node�� �߰��ϴ� �Լ�
int isEmpty(LinkedStackType* s); // Stack�� ������� Ȯ���ϴ� �Լ�
element pop(LinkedStackType* s); // Stack�� ���� ���� Node�� �����ؼ� ��ȯ�ϴ� �Լ� 
element peek(LinkedStackType* s); // Stack�� ���� ���� Node�� �������� �˷��ִ� �Լ�

void pushLoc(LinkedStackType* s, int r, int c, int max_r, int max_c); // �湮���� ���� �̷��� ��ǥ�� Stack�� �߰��ϴ� �Լ�

void main()
{
	FILE* input; // �Է� ���� ��Ʈ��
	FILE* output; // ��� ���� ��Ʈ��

	char str[2 * MAX_MAZE_SIZE + 3]; // ��Ʈ�����κ��� ���� ���ڿ� 
	int total = 0; // �� �̷��� ���� ��
	int rows = 0; // �̷��� �� ��

	element entry; // �Ա� 
	element exit; // �ⱸ

	input = fopen(INPUT_DIR, "r"); // �Է� ���� ����

	// �Է� ������ �� ������ ��
	if (input == NULL)
	{
		error("�Է� ������ �� �� �����ϴ�.");
	}

	// �Է� ������ ����� �ٹٲ��� �������� �ܾ �޾Ƶ鿩 �� ���� ���� ����
	while (EOF != fscanf(input, "%s", str))
	{	
		// printf("%s",str); 
		total++;
	}
	fclose(input); // �Է� ���� �ݱ�

	input = fopen(INPUT_DIR, "r"); // �Է� ���� ����

	// �Է� ������ �� ������ ��
	if (input == NULL)
	{
		error("�Է� ������ �� �� �����ϴ�.");
	}

	// �Է� ������ �� �پ� ���ڿ��� �޾Ƶ鿩 �� ���� ���� ����
	while (NULL != fgets(str, sizeof(str), input)) 
	{
		rows++;
	}
	
	fclose(input); // �Է� ���� �ݱ�

	int cols = total / rows; // ���� �� * ���� �� = ��ü ���� �� ���� �̿��� ���� �� ����
	// ��� ���� ���� �ִ� ����� �ʰ��� �� ���� ���
	if (cols > MAX_MAZE_SIZE || rows > MAX_MAZE_SIZE)
	{
		error("�̷� ũ�� �ѵ� �ʰ�");
	}

	input = fopen(INPUT_DIR, "r"); // �Է� ���� ����

	// �Է� ������ �� ������ ��
	if (input == NULL)
	{
		error("�Է� ������ �� �� �����ϴ�.");
	}

	// ����� �ٹٲ��� �������� �ܾ �о� �� ���ڸ� maze�� ��´�.
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			fscanf(input, "%s", str);
			maze[row][col] = str[0];
			// �Ա� ��ǥ ����
			if (maze[row][col] == 'E') 
			{
				entry.r = row;
				entry.c = col;
			}
			else
			{
				// �ⱸ ��ǥ ����
				if (maze[row][col] == 'X')
				{
					exit.r = row;
					exit.c = col;
				}
			}
		}
	}
	fclose(input); // �Է� ���� �ݱ�

	output = fopen(OUTPUT_DIR, "w"); // ��� ���� ����

	// ��� ������ �� ������ ��
	if (input == NULL)
	{
		error("��� ������ �� �� �����ϴ�.");
	}

	// ��� ���� ���Ŀ� �°� ���� �ۼ��ϱ� [] : �̷��� �� / ���� : ��� / E : �Ա� / X : �ⱸ
	
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
	fclose(output); // ��� ���� �ݱ�

	int r, c; 
	LinkedStackType s; // Stack ����
	init(&s); // Stack �ʱ�ȭ

	element here = entry; // ������� �Ա���
	printf("start "); 

	while (maze[here.r][here.c] != 'X') // �������� ������ ������ �ݺ�
	{
		r = here.r; 
		c = here.c;
		printf("(%d, %d) -> ", r, c);
		maze[r][c] = '.'; // �湮�� ��ǥ�� . ���� ǥ�� 
		// ���� ������ �� �Ʒ� �� �湮���� ���� ��θ� ã�Ƽ� ���ÿ� �ױ�
		pushLoc(&s, r - 1, c, rows-1, cols-1);
		pushLoc(&s, r + 1, c, rows-1, cols-1);
		pushLoc(&s, r, c - 1, rows-1, cols-1);
		pushLoc(&s, r, c + 1, rows-1, cols-1);

		// �湮�� �� �ִ� ��� ���� �湮�Ͽ����� �ⱸ�� �������� �� �Ͽ��� ���� ����
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

	// �ⱸ�� ������ ���� ����
	if (maze[here.r][here.c] == 'X')
	{
		printf("(%d, %d) -> end\n", here.r, here.c); // ����
		printf("success\n"); // ����
	}

	output = fopen(OUTPUT_DIR, "a+"); // ��� ���� �� �ٿ� ���� ���� ����

	if (output == NULL)
	{
		error("��� ���� �ҷ����⿡ �����߽��ϴ�."); // ��� ���� ���� ���н�
	}

	// ��� ���� ���Ŀ� �°� ����
	fprintf(output, "Ž�� ���\n"); 

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			// �� : [] / �湮���� ���� ��� : ����
			if (maze[row][col] == '1')
				fprintf(output, "@@");

			else
			{
				if (maze[row][col] == '0')
					fprintf(output, "  ");
			}
			
			// �ⱸ : X / �ⱸ �� �湮�� ��� : .
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

	fclose(output); // ��� ���� �ݱ�

	return;
	
}

// ������ ����ϴ� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

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
		error("�޸��Ҵ翡��\n");
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
		exit(1);
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


// Stack�� ���� ���� Node�� �������� �˷��ִ� �Լ�
element peek(LinkedStackType* s)
{
	// ������ ����� ��� ���� ���
	if (isEmpty)
	{
		fprintf(stderr, "������ �������\n");
		exit(1);
	}
	// ������ ������� ���� ��� ���� �� ����� ��ǥ�� ��ȯ
	else
	{
		return s->top->item;
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