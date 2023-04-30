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
	aStack.nTop = -1;								// 초기화
	push(&aStack, MinOpr);							// -무한대
	sInfix--;
	while (*++sInfix) {
		;
	}
	// 수식이 끝났으므로 stack의 연산자를 출력한다.
	printStackOpr(&aStack, MinOpr);
	putchar('\n');
	return true;
}

int IsStackEmpty(StackPtr pStack)
{	// 스택이 비었는지를 return 한다.
	return true;
}

int IsStackFull(StackPtr pStack)
{	// 스택이 가득 찼는지를 return 한다.
	return true;
}

int push(StackPtr pStack, Item nValue)
{	// 스택에 nValue를 push하는데, true/false를 return 한다.
	return true;
}

Item pop(StackPtr pStack)
{	// 스택에서 pop하여 return하는데, 스택이 비었으면 EMPTY을 return 한다.
	return true;
}

Item top(StackPtr pStack)
{	// 스택의 꼭대기 원소를 return하는데, 스택이 비었으면 EMPTY을 return 한다.
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
		{'^', 4, 5},		// {연산자, ISP, ICP}
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