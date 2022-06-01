#include <stdio.h>  
#include <stdlib.h>


FILE* input; // �Է�  
FILE* output; // ���  
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
	if(maze[r][c] == '.') return; // ���� ��ġ���� �̹� �湮�ϰų� ���ΰ�� �ش� ��ġ�� �� �̻� �ǵ����� �ʽ��ϴ�.
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
int isEmpty(PathStack* stack) // ���� node�� ����ִ��� Ȯ���մϴ�.
{
	if(stack->top != NULL)
	{
		return 0;
	}
	else{
		return 1;
	}
}

Node stackTopNode(PathStack* stack) // ���� ���� stack�� ��带 �����ϴ�.
{
	if(!isEmpty(stack)){ // stack�� ��� ���� �ʴٸ� return �մϴ�. 
		StackNode* ss = stack->top;
		Node node = ss->node;
		return node;
	}
	else{
		printf("stack�� ��� �ֽ��ϴ�.");
	}
	
}

Node pop(PathStack* stack) // stack�� �ֻ���� return�ϸ� �� �������� �����ϰ� ���Ӱ� �����մϴ�.
{
		Node node = stackTopNode(stack); // return �� �ֻ�ܳ�� �Դϴ�. 
		stack->top = stack->top->ptr; // ���� ����� top�� ���� �ֻ�� top �� �ٶ󺸴� �ٷ� �� stack�� ������ �ٲپ��ݴϴ�.
		return node;
}


void checkMazeSize (){
	char temp[10001]; // ���� ������ �ӽ÷� ������ ����� �Դϴ�. ������ buffer�� ������ �����մϴ�.

	input = fopen("input.txt", "r"); 

			while (1)
			{	
				if(EOF == fscanf(input, "%s", temp) ) break; // End of File �� ������ ��� �����մϴ�. 
				count++; // ������ ������ ���� ���ϴ�.
			}
			input = fopen("input.txt", "r"); 

			while (1) 
			{
				if(NULL == fgets(temp, sizeof(temp), input)) break; // ���پ� ����մϴ�. �� �̻� ����� �� ���ٸ� �����մϴ�.
				mazeRows++; // ������ ���� ���ϴ�.
			}

				mazeCols = count / mazeRows; //�� ���ڵ��� ������ ������ ���� �� �� �ֽ��ϴ�. 

}

void makeMaze(){
	char tmp[10001]; //�ӽ÷� ������ buffer�� ������ �����մϴ�. 

	input = fopen("input.txt", "r"); 
	Node current; // ���� ��带 ����մϴ�. 
	for (int row = 0; row < mazeRows; row++)
	{
		for (int col = 0; col < mazeCols; col++) // �ռ� ���� �̷��� ��� ����ŭ �ݺ��ϸ� Ȯ���ϸ� �̷θ� �׸��ϴ�.
		{
			fscanf(input, "%s", tmp); // �ѱ��ھ� �̷θ� ���ϴ�.
			current.r =row;
			current.c = col; // ������ �̷��� ��� ���Դϴ�.
			if (tmp[0] == 'E') //
			{
				entrance=current; // �� ��� node�� ������ entrance �� current ��ġ�� �����մϴ�.
			}
			else if(tmp[0]== 'X')
			{

				exitDoor = current; // �� ��� node�� ������ exitDoor�� ��ġ�� �����մϴ�. 

			}
			maze[row][col] = tmp[0]; // ���� ����� temp �� �̷ο� ���մϴ�. 

		}
	}
	fclose(input); 
}

void drawMaze(){
	output = fopen("output.txt", "w"); 

	for (int row = 0; row < mazeRows; row++)
	{
		for (int col = 0; col < mazeCols; col++) // �ռ� ���� �̷��� ��� ����ŭ ���� Ȯ���մϴ�.
		{
			if (maze[row][col] == 'E') // E��� output�� �׸��ϴ�. ���������� x�ų� ��(1) �� ��쵵 Ȯ���մϴ�.
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
	
	output = fopen("output.txt", "a+"); //������ �а� ����մϴ�.

	Node current; // ������ ��ġ
	for (int row = 0; row < mazeRows; row++)
	{
		for (int col = 0; col < mazeCols; col++) // �̷��� ũ�⸸ŭ �ݺ��մϴ�. 
		{
			current.c = col; // ������ ��ġ�� �����մϴ�. 
			current.r = row;
			
			if(maze[row][col] == '0')
			{
					fprintf(output, "  ");
			}
			else if(maze[row][col] == 'E')
			{
					fprintf(output, "E ");
			}
			else if (current.r  == exitDoor.r && current.c == exitDoor.c) // ������ ��ġ�� ���Ͽ� �� ��ġ�� �����ߴٸ� �����մϴ�.
			{
				if(col == 0)
				fprintf(output, "X ");
				else
				{
					fprintf(output, " X");
				}
			}
			else if (maze[row][col] == '1') // ���� �����ٸ� ���� �׸��ϴ�.
			{
				fprintf(output, "@@");
			}

			
			else if(maze[row][col] == '.') // ��� �� �ش��ϴ� �κ��� ä��ϴ�. 
			{
				
					fprintf(output, ". ");

			}
		}
		fprintf(output, "\n");
	}

	fclose(output); 
}

void makeStack(PathStack* stack){

	stack->top = NULL; // ���� ������ �ʱ�ȭ �մϴ�. 

	Node currentIndex = entrance; //ù ������ E ���� �Ԥ���.

	int r = currentIndex.r; // ������ ����� ��ġ�� �����մϴ�.
	int c = currentIndex.c;

	printf("start"); 
	printf(" (%d,%d) -> ", r, c); // ��尡 ����մϴ�. 
	if(maze[currentIndex.r][currentIndex.c] != 'E' && maze[currentIndex.r][currentIndex.c] !='1') 
	{// E�� ���� ������ ���� ��� ��쿡 ��θ� ����ݴϴ�.
		 	maze[r][c] = '.'; 
	}
	while (1) //������ while���� �ݺ��մϴ�.
	{	
		if(maze[currentIndex.r][currentIndex.c] == 'X') //��尡 x �� ������쿡 �����ŵ�ϴ�.
		{
			printf("(%d,%d) -> end\n", currentIndex.r, currentIndex.c); 
			printf("success\n"); 
			break;
		}
		
		if(maze[currentIndex.r][currentIndex.c] != 'E' && maze[currentIndex.r][currentIndex.c] !='1') 
		{// E�� ���� ������ ���� ��� ��쿡 ��θ� ����ݴϴ�.
		 	maze[r][c] = '.'; 
		}
		push(&stack, r, c + 1);  // -> ���� �̵�
		push(&stack, r + 1, c);  // �Ʒ��� �̵�
		push(&stack, r, c - 1); // <- ���� �̵�
		push(&stack, r - 1, c);  //  ���� �̵�


		if (!isEmpty(&stack)) // stack�� ��� ���� �ʴٸ� pop�� �ָ鼭 ������ stack�� ��ġ�� ���� current�� �̵��մϴ�.
		{
			currentIndex = pop(&stack); // pop �����ݴϴ�. 
			r = currentIndex.r; 
			c = currentIndex.c;
			printf("(%d, %d) -> ", r, c); //�̵��� ���� ����մϴ�.  
		}
		else
		{
			printf("fail\n"); //���� �����Ϸ�~~
			break;
						
		}
	}
	
}
void main()
{
	checkMazeSize(); // Maze�� �о �� �� ���� ���������� �����մϴ�. 
	makeMaze(); // �̷θ� ����ϴ�. �̶� �Ա��� �ⱸ�� ����� 
	drawMaze(); // �̷θ� output ���Ͽ� �����մϴ�.

	makeStack(&stack); // stack�� �޾Ƽ� stack�� ���� ��θ� ä�����ϴ�.
	pathMaze(); // ��θ� output�� �׸��ϴ�. 

	return;
	
}
