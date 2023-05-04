#include <stdio.h>

#define STACK_SIZE 40
#define EXPR_SIZE  100
#define OPERANDS   5
#pragma warning(disable: 4326 4996 6031 6054)

typedef int Item;

typedef struct {
	int nTop;
	Item items[STACK_SIZE];
}	Stack, *StackPtr;

void main()
{
	void GetOperands(int nOprnd[]);
	int EvalPostfixExpr(char* sPostfixExpr, int* pnResult, int nOprnd[]);

	int nOprnd[] = {1, 2, 3, 4, 5};
	while (1) {
		char sPostfix[EXPR_SIZE];
		printf("\nPostfix Expr[?x] ? ");
		gets_s(sPostfix);
		int nResult;
		if (*sPostfix == 'x' || *sPostfix == NULL)
			return;
		else if (*sPostfix == '?')
			GetOperands(nOprnd);
		else {
			if (EvalPostfixExpr(sPostfix, &nResult, nOprnd - 'A'))
				printf("Result : %d\n", nResult);
			else
				printf("Error...\n");
		}
	}
}

void GetOperands(int nOprnd[])						// ���Ŀ� ����� �ǿ����� ���� �Է��Ѵ�.
{
	for (int i = 0; i < OPERANDS; i++) {			// �ǿ����� A���� E����
		int nVal;
		char values[20];
		printf("%c ? ", i + 'A');					// A���� E������ �ǿ�����
		gets_s(values);
		if (sscanf(values, "%d", &nVal) != 1)		// error�� ���� �����.
			return;
		nOprnd[i] = nVal;							// �Էµ� �ǿ����ڸ� �����Ѵ�.
	}
}

int EvalPostfixExpr(char *sPostfixExpr, int *pnResult, int nOprnd[])
{
	int push(StackPtr pStack, Item nValue);
	int pop(StackPtr pStack, Item *pnValue);

	Stack aStack;
	aStack.nTop = -1;
	char *pToken = sPostfixExpr - 1;
	while (*++pToken) {
		if (*pToken >= 'A' && *pToken <= 'E')
			push(&aStack, nOprnd[*pToken]);
		else {
			int nValueA, nValueB;
			pop(&aStack, &nValueB);
			pop(&aStack, &nValueA);
			switch (*pToken) {
			case '+':
				nValueA += nValueB;
				break;
			case '-':
				nValueA -= nValueB;
				break;
			case '*':
				nValueA *= nValueB;
				break;
			case '/':
				nValueA /= nValueB;
			}
			push(&aStack, nValueA);
		}
	}
	*pnResult = aStack.items[0];
	return aStack.nTop == 0;
}

int IsStackEmpty(StackPtr pStack)
{	// ������ ��������� return �Ѵ�
	return pStack->nTop < 0;
}

int IsStackFull(StackPtr pStack)
{	// ������ ���� á������ return �Ѵ�
	return pStack->nTop >= STACK_SIZE-1;
}

int push(StackPtr pStack, Item nValue)
{	// ���ÿ� nValue�� push�ϴµ�, true/false�� return �Ѵ�.
	if (IsStackFull(pStack))
		return false;
	pStack->items[++pStack->nTop] = nValue;
	return true;
}

int pop(StackPtr pStack, Item *pnValue)
{	// ���ÿ��� pop�Ͽ� pnValue�� �����ϴµ�, true/false�� return �Ѵ�.
	if (IsStackEmpty(pStack))
		return false;
	*pnValue = pStack->items[pStack->nTop--];
	return true;
}
