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
	aStack.nTop = -1;								// 초기화
	push(&aStack, MinOpr);							// -무한대
	sInfix--;
	while (*++sInfix) {
		if (*sInfix >= 'A' && *sInfix <= 'N') 		// 피연산자
			putchar(*sInfix);						// 출력
		else if (*sInfix == ')') {
			if (printStackOpr(&aStack, '(') == false)
				return false;
		}
		else {										// 연산자
			int nICP;
			if ((nICP = priority(*sInfix, ICP)) < 0)
				return false;
			while (priority(top(&aStack), ISP) >= nICP)
				putchar(pop(&aStack));
			if (push(&aStack, *sInfix) == false)
				return false;
		}
	}
	// 수식이 끝났으므로 stack의 연산자를 출력한다.
	if (printStackOpr(&aStack, MinOpr) == false)
		return false;
	putchar('\n');
	return true;
}

int IsStackEmpty(StackPtr pStack)
{	// 스택이 비었는지를 return 한다.
	return pStack->nTop < 0;
}

int IsStackFull(StackPtr pStack)
{	// 스택이 가득 찼는지를 return 한다.
	return pStack->nTop >= STACK_SIZE-1;
}

int push(StackPtr pStack, Item nValue)
{	// 스택에 nValue를 push하는데, true/false를 return 한다.
	if (IsStackFull(pStack))
		return false;
	return pStack->items[++pStack->nTop] = nValue;
}

Item pop(StackPtr pStack)
{	// 스택에서 pop하여 return하는데, 스택이 비었으면 EMPTY을 return 한다.
	return (IsStackEmpty(pStack)) ? EMPTY : pStack->items[pStack->nTop--];
}

Item top(StackPtr pStack)
{	// 스택의 꼭대기 원소를 return하는데, 스택이 비었으면 EMPTY을 return 한다.
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
	char precedence[][3] = {	//  {연산자, ISP, ICP}
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