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
		printf("  Infix Expr ? ");
		gets_s(sInfix);
		if (*sInfix == NULL)
			return;
		printf("Postfix Expr = ");
		if (Infix2Postfix(sInfix) == false)
			printf("\nExpr Error, ...\n");
		putchar('\n');
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
		if (*sInfix >= 'A' && *sInfix <= 'N') 		// �ǿ�����
			putchar(*sInfix);						// ���
		else if (*sInfix == ')') {
			if (printStackOpr(&aStack, '(') == false)
				return false;
		}
		else {										// ������
			int nICP;
			if ((nICP = priority(*sInfix, ICP)) < 0)
				return false;
			while (priority(top(&aStack), ISP) >= nICP)
				putchar(pop(&aStack));
			if (push(&aStack, *sInfix) == false)
				return false;
		}
	}
	// ������ �������Ƿ� stack�� �����ڸ� ����Ѵ�.
	if (printStackOpr(&aStack, MinOpr) == false)
		return false;
	putchar('\n');
	return true;
}

int IsStackEmpty(StackPtr pStack)
{	// ������ ��������� return �Ѵ�.
	return pStack->nTop < 0;
}

int IsStackFull(StackPtr pStack)
{	// ������ ���� á������ return �Ѵ�.
	return pStack->nTop >= STACK_SIZE-1;
}

int push(StackPtr pStack, Item nValue)
{	// ���ÿ� nValue�� push�ϴµ�, true/false�� return �Ѵ�.
	if (IsStackFull(pStack))
		return false;
	return pStack->items[++pStack->nTop] = nValue;
}

Item pop(StackPtr pStack)
{	// ���ÿ��� pop�Ͽ� return�ϴµ�, ������ ������� EMPTY�� return �Ѵ�.
	return (IsStackEmpty(pStack)) ? EMPTY : pStack->items[pStack->nTop--];
}

Item top(StackPtr pStack)
{	// ������ ����� ���Ҹ� return�ϴµ�, ������ ������� EMPTY�� return �Ѵ�.
	return (IsStackEmpty(pStack)) ? EMPTY : pStack->items[pStack->nTop];
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
	//	!	<--		;; NOT
	//	*/	-->		;; Mul, Div
	//	+-	-->		;; Plus, Minus
	//	<>	-->		;; Less, Greater
	//	=~	-->		;; Equal, Not Equal
	//	&	-->		;; AND
	//	|	-->		;; OR
	char precedence[][3] = {	//  {������, ISP, ICP}
		{'!', 8, 9},
		{'/', 7, 7},
		{'*', 7, 7},
		{'-', 6, 6},
		{'+', 6, 6},
		{'>', 5, 5},
		{'<', 5, 5},
		{'~', 4, 4},
		{'=', 4, 4},
		{'&', 3, 3},
		{'|', 2, 2},
		{'(', 1, 9},
		{'?', 0, 0}};
	int i;
	int nSize = sizeof(precedence) / sizeof(precedence[0]);
	for (i = 0; i < nSize; i++)
		if (op == precedence[i][0])
			return precedence[i][mode];
	return -1;
}