#include "queue.h"
#include "stdio.h"
#include "stdlib.h"




PtrToQueue CreateQueue()
{
	PtrToQueue Q = (PtrToQueue)malloc(sizeof(Queue));
	if(Q == NULL)
	{
		while(1){}
	}
	else
	{
		Q->front = Q->rear = NULL;
		Q->NumOfData = 0;
	}
	return Q;
	
}


int QueueEmpty(PtrToQueue Q)
{
	if( Q == NULL)
		while(1){}
			
	return (Q->rear == NULL);
}



void ClearQueue(PtrToQueue Q)
{
	if(Q == NULL)
		while(1){}
	if(!QueueEmpty(Q))
	{
		while(Q->rear) 
		{
			DeQueue(Q);
		}

	}
	
}


void EnQueue(PtrToQueue Q,GPS X)
{
	PtrToQNode s = (PtrToQNode)malloc(sizeof(QNode));
	if(s == NULL)
	{
		while(1){}
	}
	else
	{
		if(Q->front == NULL && Q->rear == NULL)
		{
			s->data = X;
			s->next = NULL;
			Q->front = Q->rear = s;
			Q->NumOfData += 1;
		}
		else
		{
			s->data = X;
			s->next = NULL;
			Q->rear->next = s;
			Q->rear = s;
			Q->NumOfData += 1;
		}
		
	}
}


void DeQueue(PtrToQueue Q)
{
	if(QueueEmpty(Q))
	{
		printf("Empty Queue!");
		
	}
	else
	{
		PtrToQNode t = Q->front;
		if(Q->front == Q->rear)
		{
			Q->front = Q->rear = NULL;
		}
		else
		{
			Q->front = Q->front->next;
		}
		if(t != NULL)
		{
			free(t);
			Q->NumOfData -= 1;
		}

	}
}


GPS ReadQueue(PtrToQueue Q)
{
	GPS x = {0};
	if(!QueueEmpty(Q))
	{
		printf("%s\n", "Empty Queue!");
		return x;
	}
	else
	{
		return (Q->front->data);
	}

}


int Length(PtrToQueue Q)
{
	return (Q->NumOfData);
}


void ListQueue(PtrToQueue Q)
{
	int i;
	PtrToQNode t = Q->front;
	for(i = 0;i<Q->NumOfData;i++)
	{
		//printf("%d",t->data);
		t = t->next;
	}
}


void DisposeQueue(PtrToQueue Q)
{
	if(Q != NULL)
		free(Q);
}

