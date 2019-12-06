#include <stdio.h>
#include <stdlib.h>

# define TRUE 1;
# define FALSE 0;
# define QUE_LEN 100
typedef int Data;

typedef struct _cQueue
{
	int front;
	int rear;
	Data queArr[QUE_LEN];
}CQueue;

typedef CQueue Queue;

void QueueInit(Queue * pq);
int QIsEmpty(Queue * pq);

void Enqueue(Queue * pq, Data data);
Data Dequeue(Queue * pq);
Data QPeek(Queue * pq);

int NextPosIdx(int pos)
{
	if (pos == QUE_LEN - 1)
		return 0;
	else
		return pos + 1;
}

void QueueInit(Queue * pq)
{
	pq->front = 0;
	pq->rear = 0;
}

int QIsEmpty(Queue * pq)
{
	if (pq->front == pq->rear)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void Enqueue(Queue * pq, Data data)
{
	if (NextPosIdx(pq->rear) == pq->front)
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	pq->rear = NextPosIdx(pq->rear);
	pq->queArr[pq->rear] = data;

}

Data Dequeue(Queue * pq)
{
	if (QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	pq->front = NextPosIdx(pq->front);
	return pq->queArr[pq->front];
}

Data QPeek(Queue * pq)
{
	if (QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}
	
	return pq->queArr[pq->front];
}

void fillQueues(Queue* q0to9, Queue* q10to19, Queue* q20to29, Queue* qOver29)
{
	int category;
	int item;
	int* dataPtr;

	printf("Data to be categorized:\n");
	srand(79);

	for (int i = 1; i <= 25; i++)
	{
		if (!(dataPtr = (int*)malloc(sizeof(int))))
		{
			printf("Overflow in fillQueues\a\n"); // \a는 경고음 발생
			exit(100);
		}

		*dataPtr = item = rand() % 51;
		category = item / 10;
		printf("%3d", item);
		if (!(i % 11))
			printf("\n");

		switch (category)
		{
		case 0: Enqueue(q0to9, *dataPtr);
			break;
		case 1: Enqueue(q10to19, *dataPtr);
			break;
		case 2: Enqueue(q20to29, *dataPtr);
			break;
		default: Enqueue(qOver29, *dataPtr);
			break;
		}
	
	}
	printf("\nEnd of Data to be categorized\n\n");
}

void printOneQueue(Queue* pQueue)
{
	int lineCount;
	Data * dataPtr;

	dataPtr = (Data*)malloc(sizeof(Data));
	
	lineCount = 0;
	while (!QIsEmpty(pQueue))
	{
		*dataPtr = Dequeue(pQueue);
		printf("%3d", *dataPtr);

		if (lineCount++ >= 10)
		{
			lineCount = 1;
			printf("\n             ");
		}
	}
	printf("\n");

	return;
}

void printQueues(Queue* q0to9, Queue* q10to19, Queue* q20to29, Queue* qOver29)
{
	printf("Data    0~ 9:");
	printOneQueue(q0to9);

	printf("Data  10~ 19:");
	printOneQueue(q10to19);

	printf("Data  20~ 29:");
	printOneQueue(q20to29);

	printf("Data over 29:");
	printOneQueue(qOver29);

	return;
}



int main()
{
	
	Queue * q0to9;
	Queue * q10to19;
	Queue * q20to29;
	Queue * qOver29;

	q0to9 = (Queue*)malloc(sizeof(Queue));
	q10to19 = (Queue*)malloc(sizeof(Queue));
	q20to29 = (Queue*)malloc(sizeof(Queue));
	qOver29 = (Queue*)malloc(sizeof(Queue));

	printf("Start Categorizing...\n\n");

	QueueInit(q0to9);
	QueueInit(q10to19);
	QueueInit(q20to29);
	QueueInit(qOver29);

	fillQueues(q0to9, q10to19, q20to29, qOver29);
	
	printQueues(q0to9, q10to19, q20to29, qOver29);

	return 0;
}

