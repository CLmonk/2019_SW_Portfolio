# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

//Stack ADT Type Definitions
typedef struct node
	{
	void* dataptr;
	struct node* link;

	} STACK_NODE;
// node를 만든다.

typedef struct
	{
	int count;
	STACK_NODE* top;

	}STACK;
// Define meta-structure

/* createStack
This algorithm creates an empty stack.
	Pre Nothing
	Post Returns pointer to a null stack
		 -or- NULL if overflow
*/

STACK* createStack(void)
{
	//Local Definitions
	STACK* stack;

	//Statements
	stack = (STACK*)malloc(sizeof(STACK));
	if (stack)
	{
		stack->count = 0;
		stack->top = NULL;

	} // if
	return stack;
} // createStack ; Create meta-structure. Initialize count=0, top=NULL.

/* pushStack
This function pushes an item onto the stack.
Pre	stack is a pointer to the stack
	dataPtr pointer to data to be inserted
Post Data inserted into stack
Return true if successful
	   false if underflow
*/

bool pushStack(STACK* stack, void* dataInPtr) // Input is the meta-structure. Type transformation is need to input data!
{
	//Local Definitions
	STACK_NODE* newPtr;

	//Statements
	newPtr = (STACK_NODE*)malloc(sizeof(STACK_NODE));
	if (!newPtr)
		return false;

	newPtr->dataptr = dataInPtr;
	newPtr->link = stack->top;
	stack->top = newPtr;
	// 메타 구조의 top 주소에 새 stack top의 주소를 대입한다. Assign an address of a new stack top to a top address of a meta-structure
	(stack->count)++;
	return true;

}//pushStack

/*popStack
This function pops item on the top of the stack.
Pre	stack is pointer to a stack*/

void* popStack(STACK* stack) // Input an address of dataOutPtr.
{
	//Local Definitions
	void* dataOutPtr;
	STACK_NODE* temp;

	//Statements
	if (stack->count == 0)
		dataOutPtr = NULL;
	else
	{
		temp = stack->top;
		dataOutPtr = stack->top->dataptr;
		stack->top = stack->top->link;
		free(temp);
		(stack->count)--;
	}//else
	return dataOutPtr;

}// popStack

/*stackTop
Retrieves data from the top of stack without changing the stack.
Pre stack is a pointer to the stack
Post Returns data pointer if successful
			 null pointer if stack empty
*/

void* stackTop(STACK* stack)
{
	//Statements
	if (stack->count == 0)
		return NULL;
	else
		return stack->top->dataptr;

}// stackTop

/*emptyStack
This function determinnnes if a stack is empty.
Pre stack is pointer to a stack
Post returns 1 if empty; 0 if data in stack
*/

bool emptystack(STACK* stack)
{
	//Statements
	return(stack->count == 0);

}// emptyStack

 /*fullStack
 This function determine if a stack is full.
 Pre stack is pointer to a stack head node
 Return true if heap full
		false if heap has room
*/

bool fullStack(STACK* stack)
{
	//Local Definitions
	STACK_NODE* temp;

	//Statements
	if ((temp = (STACK_NODE*)malloc(sizeof(*(stack->top)))))
	{
		free(temp);
		return false;

	}// if

	//malloc failed
	return true;

}//fullStack

/*stackCount
Returns number of elements in stack.
Pre stack is a pointer to the stack
Post count returned
*/

int stackCount(STACK* stack)
{
	//Statements
	return stack->count;

}//stackCount

/*destroyStack
This function releases all nodes to the heap.
Pre A stack
Post returns null pointer
*/

STACK* destroyStack(STACK* stack)
{
	//Local Definitions
	STACK_NODE* temp;

	//Statements
	if (stack)
	{
		//Delete all nodes in stack
		while (stack->top != NULL)
		{
			//Delete data entry
			free(stack->top->dataptr);
			temp = stack->top;
			stack->top = stack->top->link;
			free(temp);
		} //while
		//Stack now empty. Destroy stack head node.
		free(stack);

	}// if stack
	return NULL;
}//destroyStack

void insertData(STACK* stack)
{
	char charIn;
	
	printf("입력 문자 : ");
	
	if (fullStack(stack))
	{
		printf("Error 100: Out of Memory\n");
		exit(100);
	}

	for (int nodeCount = 0; nodeCount < 10; nodeCount++)
	{
		charIn = rand() % 26 + 'A';
		pushStack(stack, (char*)charIn);
		printf("%c", charIn);
	}
	printf("\n");

}

void print (STACK* stack)
{
	char* charOut;

	printf("출력 문자 : ");

	while(!emptystack(stack))
	{
		charOut = (char*)popStack(stack);
		printf("%c", charOut);
	}

	printf("\n");
}

int main(void)
{
	STACK* stack;

	stack = createStack();

	printf("ADT 기반의 스택을 이용한 10개 문자 역순 출력\n\n");

	insertData(stack);
	print(stack);

	return 0;
}