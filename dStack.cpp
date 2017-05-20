#include "Stack.h"
#include "dStack.h"
#include <iostream>

using namespace std;

void dPush(dStackItem** pHead, double x)
{
	dStackItem* v = (dStackItem*)malloc(sizeof(dStackItem));

	if (v) // v != NULL
	{
		memset(v, 0, sizeof(dStackItem));
		v->dcKey = x;
		v->pNext = *pHead;  // 
		*pHead = v;        // bo pHead musi zawierac caly nowy element
	}
}

double dPop(dStackItem** pHead)
{
	double x = 0;

	if (!dIsEmpty(*pHead)) //jesli stos znakowy nie jest pusty
	{
		x = dTop(*pHead);
		dDel(pHead);
	}
	else
	{
		cout << "dERROR STACK UNDERFLOW!" << endl;
	}

	return x;
}

double dTop(dStackItem* pHead)
{
	if (!dIsEmpty(pHead))
	{
		return pHead->dcKey;
	}

	return 0;
}

void dDel(dStackItem** pHead)
{
	if (!dIsEmpty(*pHead))
	{
		dStackItem* v = *pHead;
		*pHead = v->pNext;

		free(v);
	}
	else
	{
		cout << "dERROR STACK IS EMPTY!" << endl;
	}
}

int dIsEmpty(dStackItem* pHead)
{
	return !pHead;
}

void dInitStack(dStackItem** pHead)
{
	*pHead = NULL;
}

void dFreeStack(dStackItem** pHead)
{
	while (!dIsEmpty(*pHead))
	{
		dDel(pHead);
	}
}