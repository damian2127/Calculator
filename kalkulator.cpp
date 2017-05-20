#include <iostream>
#include <math.h>

#include "Stack.h"
#include "dStack.h"


using namespace std;

double Calculator();
double  GetNum();//zwraca wartosc liczby zmienno-przecinkowej
char GetOper();// wczytuje kolejny znak, który mo¿e byæ operatorem(pomijam spacje)
void SkipSpaces();//pomijam spacje
int  Prior(char cOper);// okreslam priorytet operatorow
int  isDigit(char c);//sprawdza czy jest liczb¹
int  isOper(char cOper); //sprawdzam czy moj znak jest operatorem
double Eval(char cOper, double fArg1, double fArg2); //pobiera dwa argumenty, operator i zwraca wynik dzialania
int CheckC(char c);//sprawdza czy znak jest liczba, operatorem, kropk¹, nawiasami,


int main(int argc, char* argv[])
{

	cout << "\n\nWynik = " << Calculator() << "\n\n";

	system("pause");
	return 0;
}

double Calculator()
{
	double digit; //zmienna przechowujaca liczba
	char c;      //zmienna pomocnicza przechowujaca znak pobierany znak	

				 //============zainicjowanie stosow===================

	StackItem* pStack; InitStack(&pStack);
	dStackItem* dpStack; dInitStack(&dpStack);

	//=================Calculator===========================

	while (CheckC(c = GetOper()))  //wczytuje kolejny znak, ktory bedzie liczb¹, kropk¹, operatorem b¹dz nawiasami
	{
		if (isDigit(c) || c == '.') // jesli jest c liczb¹
		{
			ungetc(c, stdin);
			dPush(&dpStack, GetNum());
		}
		else if (isOper(c))
		{
			while (Prior(c) <= Prior(Top(pStack)))
			{
				digit = dPop(&dpStack);
				dPush(&dpStack, Eval(Pop(&pStack), dPop(&dpStack), digit));   //wkladam na stos liczbowy wynik dzialania Eval()
			}

			Push(&pStack, c);     //jesli prior operatora byl mniejszy od prior szczytu stosu znakowego, to nie wykonala sie petla z liczeniem

		}
		else if (c == '(')
		{
			Push(&pStack, c);    //wrzuc na stos i wczytuj kolejne znaki
		}
		else if (c == ')')
		{
			while ((c = Pop(&pStack)) != '(')
			{
				digit = dPop(&dpStack);
				dPush(&dpStack, Eval(c, dPop(&dpStack), digit));
			}
		}
	}

	while (!IsEmpty(pStack))
	{
		digit = dPop(&dpStack);
		dPush(&dpStack, Eval(Pop(&pStack), dPop(&dpStack), digit));
	}

	return dPop(&dpStack);
}

double  GetNum() //obliczam wartosc liczby zmiennoprzecinkowej
{
	char c;
	double res = 0;

	SkipSpaces();

	while (isDigit(c = getchar()))
	{
		res = res * 10 + (c - '0');   //schemat Hornera, zapis liczby w systemie dziesietnym
	}

	if (c == '.')
	{
		double y = 0.1;

		while (isDigit(c = getchar()))
		{
			res += (c - '0')*y;
			y *= 0.1;
		}
	}

	ungetc(c, stdin); //umieszczam znak c z powrotem w strumieniu wejsciowym

	return res;
}

char GetOper() //wczytuje kolejny znak pomijajac spacje, bedacy potencjalnym operatorem
{
	SkipSpaces();
	return getchar();
}

void SkipSpaces() //pomijam spacje
{
	char c;

	while ((c = getchar()) == ' ');
	ungetc(c, stdin);   //umieszczam znak c z powrotem w strumieniu wejsciowym
}

int  Prior(char cOper) //okreslam priorytet operatorow
{
	switch (cOper)
	{
	case '+':
	case '-': return 2;
	case '*':
	case '/': return 3;
	case '^': return 4;
	}

	return 0;
}

int  isDigit(char c) //sprawdzam czy liczba jest z przedzialu 0-9
{
	return (c >= '0') && (c <= '9');
}

int  isOper(char cOper) //sprawdzam czy znak jest operatorem, jesli tak to zwroc 1
{
	switch (cOper)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '^': return 1;
	}

	return 0;
}

double Eval(char cOper, double fArg1, double fArg2)
{

	switch (cOper)
	{
	case '+': return fArg1 + fArg2;
	case '-': return fArg1 - fArg2;
	case '*': return fArg1 * fArg2;
	case '/':	if (fabs(fArg2) >= 1e-15)
	{
		return fArg1 / fArg2;
	}
				else
				{
					cout << "Nie dzielimy przez zero!" << endl;
					return 0;
				}

	case '^': return pow(fArg1, fArg2);

	}
	return 0;
}

int CheckC(char c)
{

	return (isDigit(c) || isOper(c) || c == '(' || c == ')' || c == '.');

}