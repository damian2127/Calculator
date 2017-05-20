#pragma once

#ifndef _DSTACK_INCLUDE_
#define _DSTACK_INCLUDE_

typedef struct dtagStackItem
{
	double dcKey;
	dtagStackItem* pNext;
}dStackItem;

void dPush(dStackItem** pHead, double x); //wklada na stos
double dPop(dStackItem** pHead); //zdejmuje ze stosu i go zwraca
double dTop(dStackItem* pHead); //zwraca szczyt bez usuwania
void dDel(dStackItem** pHead); //usuwa szczyt
int dIsEmpty(dStackItem* pHead);//1-> gdy stos jest pusty
void dInitStack(dStackItem** pHead); //Zainicjowanie stosu ((NULL))
void dFreeStack(dStackItem** pHead); //zwolnienie pamiêci zajmowaniem przez stos

#endif