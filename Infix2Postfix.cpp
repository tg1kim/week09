#include <stdio.h>

#define STACK_SIZE	40
#define EXPR_SIZE	100
#define ISP			1
#define ICP			2
#define MinOpr		'?'
#define	EMPTY		0x20
#pragma warning(disable: 4326 4996 6031)

/** Create Stack **/
typedef char Item;

typedef struct {
	int  nTop;
	Item items[STACK_SIZE];
}	Stack, *StackPtr;


void main()
{
	int Infix2Postfix(char *sInfix);

	while (1) {
		char sInfix[EXPR_SIZE];
		printf("\n  Infix Expr ? ");
		gets_s(sInfix);
		if (*sInfix == NULL)
			return;
		printf("Postfix Expr : ");
		Infix2Postfix(sInfix);
	}
}

int Infix2Postfix(char *sInfix)
{
	int push(StackPtr pStack, Item op);
	Item pop(StackPtr pStack);
	Item top(StackPtr pStack);
	int priority(char op, int mode);
	int printStackOpr(StackPtr pStack, Item nLastOpr);

	Stack aStack;
	aStack.nTop = -1;								// �ʱ�ȭ
	push(&aStack, MinOpr);							// -���Ѵ�
	sInfix--;
	while (*++sInfix) {
		;
	}
	// ������ �������Ƿ� stack�� �����ڸ� ����Ѵ�.
	printStackOpr(&aStack, MinOpr);
	putchar('\n');
	return true;
}

int IsStackEmpty(StackPtr pStack)
{	// ������ ��������� return �Ѵ�.
	return true;
}

int IsStackFull(StackPtr pStack)
{	// ������ ���� á������ return �Ѵ�.
	return true;
}

int push(StackPtr pStack, Item nValue)
{	// ���ÿ� nValue�� push�ϴµ�, true/false�� return �Ѵ�.
	return true;
}

Item pop(StackPtr pStack)
{	// ���ÿ��� pop�Ͽ� return�ϴµ�, ������ ������� EMPTY�� return �Ѵ�.
	return true;
}

Item top(StackPtr pStack)
{	// ������ ����� ���Ҹ� return�ϴµ�, ������ ������� EMPTY�� return �Ѵ�.
	return true;
}

int printStackOpr(StackPtr pStack, Item nLastOpr)
{
	Item nOpr;
	while ((nOpr = pop(pStack)) != nLastOpr) {
		if (nOpr == EMPTY)
			return false;
		putchar(nOpr);
	}
	return true;
}

int priority(char op, int mode)
{
	char precedence[][3] = { 
		{'^', 4, 5},		// {������, ISP, ICP}
		{'*', 3, 3},
		{'/', 3, 2},
		{'+', 2, 2},
		{'-', 2, 2},
		{'(', 1, 5},
		{'?', -1, 0}};
	int i;
	int nSize = sizeof(precedence) / sizeof(precedence[0]);
	for (i = 0; i < nSize; i++)
		if (op == precedence[i][0])
			return precedence[i][mode];
	return -1;
}